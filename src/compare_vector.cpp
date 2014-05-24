#include "common.h"

AI_SHADER_NODE_EXPORT_METHODS(CompareVectorMtd);

enum CompareVectorParams
{
   p_operator = 0,
   p_invert,
   p_input1,
   p_input2,
   p_precision
};

node_parameters
{
   AiParameterEnum("operator", 0, CompareOperatorNames);
   AiParameterBool("invert", false);
   AiParameterVec("input1", 0.0f, 0.0f, 0.0f);
   AiParameterVec("input2", 0.0f, 0.0f, 0.0f);
   AiParameterFlt("precision", AI_EPSILON);
}

node_initialize
{
}

node_update
{
}

node_finish
{
}

shader_evaluate
{
   bool rv = false;
   
   CompareOperator op = (CompareOperator) AiShaderEvalParamInt(p_operator);
   
   float precision = AiShaderEvalParamFlt(p_precision);
   
   AtVector input1 = AiShaderEvalParamVec(p_input1);
   AtVector input2 = AiShaderEvalParamVec(p_input2);
   float tmp;
   
   switch (op)
   {
   case CO_EQ:
      rv = true;
      tmp = input1.x - input2.x;
      rv = rv && (tmp < 0.0f ? (tmp > -precision) : (tmp < precision));
      tmp = input1.y - input2.y;
      rv = rv && (tmp < 0.0f ? (tmp > -precision) : (tmp < precision));
      tmp = input1.z - input2.z;
      rv = rv && (tmp < 0.0f ? (tmp > -precision) : (tmp < precision));
      break;
   case CO_NEQ:
      rv = true;
      tmp = input1.x - input2.x;
      rv = rv && (tmp < 0.0f ? (tmp <= -precision) : (tmp >= precision));
      tmp = input1.y - input2.y;
      rv = rv && (tmp < 0.0f ? (tmp <= -precision) : (tmp >= precision));
      tmp = input1.z - input2.z;
      rv = rv && (tmp < 0.0f ? (tmp <= -precision) : (tmp >= precision));
      break;
   case CO_LT:
      rv = (input1.x < input2.x && input1.y < input2.y && input1.z < input2.z);
      break;
   case CO_LTE:
      rv = (input1.x <= input2.x && input1.y <= input2.y && input1.z <= input2.z);
      break;
   case CO_GT:
      rv = (input1.x > input2.x && input1.y > input2.y && input1.z > input2.z);
      break;
   case CO_GTE:
      rv = (input1.x >= input2.x && input1.y >= input2.y && input1.z >= input2.z);
      break;
   default:
      break;
   }
   
   sg->out.BOOL = (AiShaderEvalParamBool(p_invert) ? !rv : rv);
}