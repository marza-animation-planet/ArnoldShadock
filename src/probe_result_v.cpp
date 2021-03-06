/*
MIT License
Copyright (c) 2014~ Gaetan Guidet
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "common.h"

AI_SHADER_NODE_EXPORT_METHODS(ProbeResultVMtd);

enum ProbeResultVParams
{
   p_state = 0,
   p_trace,
   p_default
};

enum ProbeState
{
   PS_position = 0,
   PS_normal
};

static const char* ProbeStateNames[] =
{
   "position",
   "normal",
   NULL
};

node_parameters
{
   AiParameterEnum(SSTR::state, PS_position, ProbeStateNames);
   AiParameterBool("trace", false);
   AiParameterVec("default", 0.0f, 0.0f, 0.0f);
}

node_initialize
{
   AiNodeSetLocalData(node, AiMalloc(sizeof(int)));
   AddMemUsage<int>();
}

node_update
{
   int *data = (int*) AiNodeGetLocalData(node);
   *data = AiNodeGetInt(node, SSTR::state);
}

node_finish
{
   AiFree(AiNodeGetLocalData(node));
   SubMemUsage<int>();
}

shader_evaluate
{
   AtShaderGlobals *hitsg = 0;
   HitData *hit = 0;
   
   if (!AiShaderEvalParamBool(p_trace) ||
       !AiStateGetMsgPtr(SSTR::agsb_trace_hit, (void**)&hit) ||
       !hit ||
       !hit->isSG)
   {
      if (hit && !hit->isSG)
      {
         AiMsgWarning("[probe_result_v] Trying to access result from a 'standard' or 'background' trace: Use 'trace_result_v' instead");
      }
      sg->out.VEC = AiShaderEvalParamVec(p_default);
   }
   else
   {
      ProbeState state = (ProbeState) *((int*) AiNodeGetLocalData(node));
      
      hitsg = (AtShaderGlobals*) hit->ptr;
      
      switch (state)
      {
      case PS_position:
         sg->out.VEC = hitsg->P;
         break;
      case PS_normal:
         sg->out.VEC = hitsg->N;
         break;
      default:
         sg->out.VEC = AiShaderEvalParamVec(p_default);
         break;
      }
   }
}
