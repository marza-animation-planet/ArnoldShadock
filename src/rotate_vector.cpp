#include "common.h"

AI_SHADER_NODE_EXPORT_METHODS(RotateVectorMtd);

enum RotateVectorParams
{
   p_input = 0,
   p_rotation_order,
   p_angle_units,
   p_rotation_pivot,
   p_rotation
};

node_parameters
{
   AiParameterVec("input", 0.0f, 0.0f, 0.0f);
   AiParameterEnum("rotation_order", RO_XYZ, RotationOrderNames);
   AiParameterEnum("angle_units", AU_Degrees, AngleUnitsNames);
   AiParameterVec("rotation", 0.0f, 0.0f, 0.0f);
   AiParameterPnt("rotation_pivot", 0.0f, 0.0f, 0.0f);
   
   AiMetaDataSetBool(mds, "rotation_order", "linkable", false);
   AiMetaDataSetBool(mds, "angle_units", "linkable", false);
}

struct RotateVectorData
{
   AtMatrix Rx;
   AtMatrix Ry;
   AtMatrix Rz;
   AtMatrix Rp;
   AtMatrix iRp;
   AtMatrix R;  // composed rotate matrix -> Rz * Ry * Rx for ZYX rotation order
   AtMatrix Rf; // final rotate matrix -> iRp * R * Rp
   
   bool Rx_set;
   bool Ry_set;
   bool Rz_set;
   bool Rp_set;
   
   float angleScale;
   
   RotationOrder rotationOrder;
};

node_initialize
{
   RotateVectorData *data = (RotateVectorData*) AiMalloc(sizeof(RotateVectorData));

   data->Rx_set = false;
   data->Ry_set = false;
   data->Rz_set = false;
   data->Rp_set = false;
   data->angleScale = 1.0f;
   data->rotationOrder = RO_XYZ;

   AiNodeSetLocalData(node, data);
}

node_update
{
   RotateVectorData *data = (RotateVectorData*) AiNodeGetLocalData(node);
   
   data->rotationOrder = (RotationOrder) AiNodeGetInt(node, "rotation_order");
   data->angleScale = (AiNodeGetInt(node, "angle_units") == AU_Radians ? AI_RTOD : 1.0f);
   
   if (!AiNodeIsLinked(node, "rotation"))
   {
      AtVector R = AiNodeGetVec(node, "rotation");

      data->Rx_set = true;
      data->Ry_set = true;
      data->Rz_set = true;

      AiM4RotationX(data->Rx, data->angleScale * R.x);
      AiM4RotationY(data->Ry, data->angleScale * R.y);
      AiM4RotationZ(data->Rz, data->angleScale * R.z);
   }
   else
   {
      data->Rx_set = false;
      if (!AiNodeIsLinked(node, "rotation.x"))
      {
         data->Rx_set = true;
         AtVector R = AiNodeGetVec(node, "rotation");
         AiM4RotationX(data->Rx, data->angleScale * R.x);
      }

      data->Ry_set = false;
      if (!AiNodeIsLinked(node, "rotation.y"))
      {
         data->Ry_set = true;
         AtVector R = AiNodeGetVec(node, "rotation");
         AiM4RotationY(data->Ry, data->angleScale * R.y);
      }

      data->Rz_set = false;
      if (!AiNodeIsLinked(node, "rotation.z"))
      {
         data->Rz_set = true;
         AtVector R = AiNodeGetVec(node, "rotation");
         AiM4RotationZ(data->Rz, data->angleScale * R.z);
      }
   }

   data->Rp_set = false;
   if (!AiNodeIsLinked(node, "rotation_pivot"))
   {
      data->Rp_set = true;
      AtPoint P = AiNodeGetPnt(node, "rotation_pivot");
      AiM4Translation(data->Rp, &P);
      P = -P;
      AiM4Translation(data->iRp, &P);
   }

   if (data->Rx_set && data->Ry_set && data->Rz_set)
   {
      AtMatrix tmp;

      switch (data->rotationOrder)
      {
      case RO_XYZ:
         AiM4Mult(tmp, data->Ry, data->Rx);
         AiM4Mult(data->R, data->Rz, tmp);
         break;
      case RO_XZY:
         AiM4Mult(tmp, data->Rz, data->Rx);
         AiM4Mult(data->R, data->Ry, tmp);
         break;
      case RO_YXZ:
         AiM4Mult(tmp, data->Rx, data->Ry);
         AiM4Mult(data->R, data->Rz, tmp);
         break;
      case RO_YZX:
         AiM4Mult(tmp, data->Rz, data->Ry);
         AiM4Mult(data->R, data->Rx, tmp);
         break;
      case RO_ZXY:
         AiM4Mult(tmp, data->Rx, data->Rz);
         AiM4Mult(data->R, data->Ry, tmp);
         break;
      case RO_ZYX:
      default:
         AiM4Mult(tmp, data->Ry, data->Rz);
         AiM4Mult(data->R, data->Rx, tmp);
      }

      if (data->Rp_set)
      {
         AiM4Mult(tmp, data->R, data->iRp);
         AiM4Mult(data->Rf, data->Rp, tmp);
      }
   }
}

node_finish
{
   RotateVectorData *data = (RotateVectorData*) AiNodeGetLocalData(node);
   AiFree(data);
}

shader_evaluate
{
   RotateVectorData *data = (RotateVectorData*) AiNodeGetLocalData(node);
   
   AtVector p, ip, r;
   AtMatrix R, Rx, Ry, Rz, P, iP, tmp;
   bool computeR = true;
   
   if (!data->Rz_set || !data->Ry_set || !data->Rz_set)
   {
      r = AiShaderEvalParamVec(p_rotation);
      
      if (!data->Rx_set)
      {
         AiM4RotationX(Rx, data->angleScale * r.x);
      }
      else
      {
         AiM4Copy(Rx, data->Rx);
      }
      
      if (!data->Ry_set)
      {
         AiM4RotationY(Ry, data->angleScale * r.y);
      }
      else
      {
         AiM4Copy(Ry, data->Ry);
      }
      
      if (!data->Rz_set)
      {
         AiM4RotationZ(Rz, data->angleScale * r.z);
      }
      else
      {
         AiM4Copy(Rz, data->Rz);
      }
      
      switch (data->rotationOrder)
      {
      case RO_XYZ:
         AiM4Mult(tmp, Ry, Rx);
         AiM4Mult(R, Rz, tmp);
         break;
      case RO_XZY:
         AiM4Mult(tmp, Rz, Rx);
         AiM4Mult(R, Ry, tmp);
         break;
      case RO_YXZ:
         AiM4Mult(tmp, Rx, Ry);
         AiM4Mult(R, Rz, tmp);
         break;
      case RO_YZX:
         AiM4Mult(tmp, Rz, Ry);
         AiM4Mult(R, Rx, tmp);
         break;
      case RO_ZXY:
         AiM4Mult(tmp, Rx, Rz);
         AiM4Mult(R, Ry, tmp);
         break;
      case RO_ZYX:
      default:
         AiM4Mult(tmp, Ry, Rz);
         AiM4Mult(R, Rx, tmp);
      }
   }
   else
   {
      if (data->Rp_set)
      {
         AiM4Copy(R, data->Rf);
         computeR = false;
      }
      else
      {
         AiM4Copy(R, data->R);
      }
   }
   
   if (!data->Rp_set)
   {
      p = AiShaderEvalParamVec(p_rotation_pivot);
      ip = -p;
      
      AiM4Translation(P, &p);
      AiM4Translation(iP, &ip);
      
      AiM4Mult(tmp, R, iP);
      AiM4Mult(R, P, tmp);
   }
   else if (computeR)
   {
      AiM4Mult(tmp, R, data->iRp);
      AiM4Mult(R, data->Rp, tmp);
   }
   
   AtVector v = AiShaderEvalParamVec(p_input);
   
   AiM4VectorByMatrixMult(&(sg->out.VEC), R, &v);
}