#include "common.h"

AI_SHADER_NODE_EXPORT_METHODS(SqrtFMtd);

enum SqrtFParams
{
   p_input = 0
};

node_parameters
{
   AiParameterFlt("input", 0.0f);
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
   float input = AiShaderEvalParamFlt(p_input);
   
   sg->out.FLT = sqrtf(input);
}