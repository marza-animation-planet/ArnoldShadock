#include "common.h"

AI_SHADER_NODE_EXPORT_METHODS(ShadowMatteMtd);

node_parameters
{
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
   sg->out.RGB = AiLightsGetShadowMatte(sg);
}