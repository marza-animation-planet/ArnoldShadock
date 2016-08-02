#include "common.h"

AI_SHADER_NODE_EXPORT_METHODS(NodeAttrIMtd);

enum NodeAttrIParams
{
   p_target_node = 0,
   p_attribute,
   p_user_defined,
   p_default
};

node_parameters
{
   AiParameterNode(SSTR::target_node, NULL);
   AiParameterStr(SSTR::attribute, "");
   AiParameterBool(SSTR::user_defined, true);
   AiParameterInt(SSTR::_default, 0);
   
   AiMetaDataSetBool(mds, SSTR::attribute, SSTR::linkable, false);
   AiMetaDataSetBool(mds, SSTR::user_defined, SSTR::linkable, false);
}

struct NodeData
{
   AtString attribute;
   bool user_defined;
   bool linked;
};

node_initialize
{
   AiNodeSetLocalData(node, new NodeData());
   AddMemUsage<NodeData>();
}

node_update
{
   NodeData *data = (NodeData*) AiNodeGetLocalData(node);
   data->attribute = AiNodeGetStr(node, SSTR::attribute);
   data->user_defined = AiNodeGetBool(node, SSTR::user_defined);
   data->linked = AiNodeIsLinked(node, SSTR::target_node);
}

node_finish
{
   NodeData *data = (NodeData*) AiNodeGetLocalData(node);
   delete data;
   SubMemUsage<NodeData>();
}

shader_evaluate
{
   NodeData *data = (NodeData*) AiNodeGetLocalData(node);
   
   sg->out.INT = 0.0f;
   
   if (!data->linked)
   {
      sg->out.INT = AiShaderEvalParamInt(p_default);
   }
   else
   {
      AtNode *src = (AtNode*) AiShaderEvalParamPtr(p_target_node);
      
      if (!src)
      {
         sg->out.INT = AiShaderEvalParamInt(p_default);
      }
      else
      {
         int type = AI_TYPE_UNDEFINED;
         
         if (data->user_defined)
         {
            const AtUserParamEntry *pe = AiNodeLookUpUserParameter(src, data->attribute);
            
            if (pe && AiUserParamGetCategory(pe) == AI_USERDEF_CONSTANT)
            {
               type = AiUserParamGetType(pe);
            }
         }
         else
         {
            const AtParamEntry *pe = AiNodeEntryLookUpParameter(AiNodeGetNodeEntry(src), data->attribute);
            
            if (pe)
            {
               type = AiParamGetType(pe);
            }
         }
         
         switch (type)
         {
         case AI_TYPE_INT:
            sg->out.INT = AiNodeGetInt(src, data->attribute);
            break;
         case AI_TYPE_BYTE:
            sg->out.INT = (int) AiNodeGetByte(src, data->attribute);
            break;
         case AI_TYPE_UINT:
            sg->out.INT = (int) AiNodeGetUInt(src, data->attribute);
            break;
         default:
            sg->out.INT = AiShaderEvalParamInt(p_default);
         }
      }
   }
}
