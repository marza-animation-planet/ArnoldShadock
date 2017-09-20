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

AI_SHADER_NODE_EXPORT_METHODS(SetOpacityMtd);

enum SetOpacityParams
{
   p_color = 0,
   p_opacity
};

node_parameters
{
   AiParameterRGB("color", 0.0f, 0.0f, 0.0f);
   AiParameterRGB("opacity", 1.0f, 1.0f, 1.0f);
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
   AtRGB opacity = AiShaderEvalParamRGB(p_opacity);
   
   if (MaxComponent<3>(&(opacity.r)) <= AI_EPSILON)
   {
      sg->out.RGB() = AI_RGB_BLACK;
      sg->out_opacity = AI_RGB_BLACK;
   }
   else
   {
      sg->out.RGB() = AiShaderEvalParamRGB(p_color);
      sg->out_opacity = opacity;
   }
}