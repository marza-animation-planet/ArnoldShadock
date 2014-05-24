#include "common.h"

AI_SHADER_NODE_EXPORT_METHODS(FloorFloatMtd);

enum FloorFloatParams
{
   p_input
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
   
   sg->out.FLT = FLOOR(input);
}