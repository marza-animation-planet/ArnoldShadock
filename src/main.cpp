#include <ai.h>
#include <cstring>
#include <cstdlib>

// ---

#ifndef SHADERS_PREFIX
#  define SHADERS_PREFIX ""
#endif

static int gsShaderCount = 0;

#define DECLARE_SHADER(name)\
   extern AtNodeMethods* name##Mtd;\
   static int name = gsShaderCount++

#define DECLARE_FLOAT_SHADER(name) DECLARE_SHADER(name##Float)

#define DECLARE_COLOR_SHADER(name) DECLARE_SHADER(name##Color)

#define DECLARE_VECTOR_SHADER(name) DECLARE_SHADER(name##Vector)

#define DECLARE_FCV_SHADER(name)\
   DECLARE_FLOAT_SHADER(name);\
   DECLARE_COLOR_SHADER(name);\
   DECLARE_VECTOR_SHADER(name)

#define REGISTER_SHADER(s_name, a_name, a_type)\
   if (i == s_name)\
   {\
      node->name = SHADERS_PREFIX #a_name;\
      node->node_type = AI_NODE_SHADER;\
      node->output_type = a_type;\
      node->methods = s_name##Mtd;\
      strcpy(node->version, AI_VERSION);\
      return true;\
   }

#define REGISTER_FLOAT_SHADER(s_name, a_name) REGISTER_SHADER(s_name##Float, a_name##_float, AI_TYPE_FLOAT)

#define REGISTER_COLOR_SHADER(s_name, a_name) REGISTER_SHADER(s_name##Color, a_name##_color, AI_TYPE_RGB)

#define REGISTER_VECTOR_SHADER(s_name, a_name) REGISTER_SHADER(s_name##Vector, a_name##_vector, AI_TYPE_VECTOR)

#define REGISTER_FCV_SHADER(s_name, a_name)\
   REGISTER_FLOAT_SHADER(s_name, a_name)\
   REGISTER_COLOR_SHADER(s_name, a_name)\
   REGISTER_VECTOR_SHADER(s_name, a_name)

// ---

DECLARE_FCV_SHADER(Abs);
DECLARE_FCV_SHADER(Add);
DECLARE_FCV_SHADER(Bias);
DECLARE_FCV_SHADER(BiasAndGain);
DECLARE_FCV_SHADER(Ceil);
DECLARE_FCV_SHADER(Clamp);
DECLARE_SHADER(CompareFloat);
DECLARE_SHADER(CompareColor);
DECLARE_SHADER(CompareVector);
DECLARE_SHADER(FloatToBool);
DECLARE_SHADER(FloatToInt);
DECLARE_SHADER(VectorToColor);
DECLARE_SHADER(ColorToVector);
DECLARE_SHADER(ColorToFloat);
DECLARE_SHADER(FloatToVector);
DECLARE_SHADER(FloatToColor);
DECLARE_SHADER(FloatToRGBA);
DECLARE_SHADER(BoolToInt);
DECLARE_SHADER(BoolToFloat);
DECLARE_SHADER(CrossProduct);
DECLARE_FCV_SHADER(Gain);
DECLARE_FCV_SHADER(Divide);
DECLARE_SHADER(DotProduct);
DECLARE_FCV_SHADER(Exp);
DECLARE_FCV_SHADER(Floor);
DECLARE_FCV_SHADER(Invert);
DECLARE_FCV_SHADER(Log);
DECLARE_FCV_SHADER(Max);
DECLARE_FCV_SHADER(Min);
DECLARE_FCV_SHADER(Mix);
DECLARE_FCV_SHADER(Modulo);
DECLARE_FCV_SHADER(MultiSelect);
DECLARE_FCV_SHADER(Multiply);
DECLARE_FCV_SHADER(Negate);
DECLARE_SHADER(NormalizeVector);
DECLARE_FCV_SHADER(Pow);
DECLARE_FCV_SHADER(Remap);
DECLARE_FCV_SHADER(Round);
DECLARE_FCV_SHADER(Select);
DECLARE_FCV_SHADER(Sign);
DECLARE_FCV_SHADER(SmoothStep);
DECLARE_FCV_SHADER(Sqrt);
DECLARE_FCV_SHADER(Subtract);
DECLARE_FLOAT_SHADER(Trigonometry);
DECLARE_VECTOR_SHADER(Trigonometry);
DECLARE_SHADER(VectorLength);
DECLARE_SHADER(ShapeAttrBool);
DECLARE_SHADER(ShapeAttrInt);
DECLARE_SHADER(ShapeAttrFloat);
DECLARE_SHADER(ShapeAttrPoint2);
DECLARE_SHADER(ShapeAttrVector);
DECLARE_SHADER(ShapeAttrColor);
DECLARE_SHADER(ShapeAttrRGBA);
DECLARE_SHADER(ShapeAttrString);
#ifdef USE_AGSTATE
DECLARE_SHADER(agIntState);
DECLARE_SHADER(agFloatState);
DECLARE_SHADER(agColorState);
DECLARE_SHADER(agVectorState);
DECLARE_SHADER(agMatrixState);
DECLARE_SHADER(agNodeState);
#endif
DECLARE_SHADER(TransformVector);
DECLARE_SHADER(MakeMatrix);
DECLARE_SHADER(MultiplyMatrix);
DECLARE_SHADER(SetTraceSet);
DECLARE_SHADER(Shade);
DECLARE_SHADER(Holdout);
DECLARE_SHADER(ShadingPoint);
DECLARE_SHADER(ShadingNormal);
DECLARE_SHADER(WriteAOVs);
DECLARE_SHADER(ReadAOVBool);
DECLARE_SHADER(ReadAOVInt);
DECLARE_SHADER(ReadAOVFlt);
DECLARE_SHADER(ReadAOVPnt2);
DECLARE_SHADER(ReadAOVPnt);
DECLARE_SHADER(ReadAOVVec);
DECLARE_SHADER(ReadAOVRGB);
DECLARE_SHADER(ReadAOVRGBA);
DECLARE_SHADER(InvertMatrix);
DECLARE_SHADER(TransposeMatrix);
DECLARE_SHADER(InterpolateMatrix);
DECLARE_FCV_SHADER(Ramp);
DECLARE_FCV_SHADER(SmoothSelect);
DECLARE_FCV_SHADER(RangeSelect);
DECLARE_FCV_SHADER(SmoothRangeSelect);
DECLARE_SHADER(MakePoint2);
DECLARE_SHADER(MakeVector);
DECLARE_SHADER(MakeColor);
DECLARE_SHADER(MakeRGBA);
DECLARE_FCV_SHADER(Gaussian);
#ifdef USE_AGNOISES
DECLARE_SHADER(Fractal);
DECLARE_SHADER(Voronoi);
DECLARE_SHADER(DistortPoint);
#endif
#ifdef USE_AGSEEXPR
DECLARE_SHADER(agSeExpr);
#endif
#ifdef USE_AGANIMCURVE
DECLARE_SHADER(agAnimCurve);
#endif
#ifdef USE_AGUSERDATARAMP
DECLARE_SHADER(agUserDataFloatRamp);
DECLARE_SHADER(agUserDataColorRamp);
DECLARE_SHADER(agUserDataVectorRamp);
#endif
DECLARE_SHADER(UVSwitch);
DECLARE_SHADER(UVProject);
DECLARE_SHADER(UVTransform);
DECLARE_SHADER(UVClip);
DECLARE_SHADER(MakeTx);
DECLARE_SHADER(CameraMatrix);
DECLARE_SHADER(ImageResolution);
DECLARE_SHADER(RenderResolution);
DECLARE_SHADER(TokenPath);
DECLARE_SHADER(Texture);
DECLARE_SHADER(WriteMsgs);
DECLARE_SHADER(ReadMsgBool);
DECLARE_SHADER(ReadMsgInt);
DECLARE_SHADER(ReadMsgFlt);
DECLARE_SHADER(ReadMsgPnt2);
DECLARE_SHADER(ReadMsgPnt);
DECLARE_SHADER(ReadMsgVec);
DECLARE_SHADER(ReadMsgRGB);
DECLARE_SHADER(ReadMsgRGBA);
DECLARE_SHADER(IlluminanceLoop);
DECLARE_SHADER(LightWeight);
DECLARE_SHADER(Reflect);
DECLARE_SHADER(Refract);
DECLARE_FLOAT_SHADER(FresnelWeight);
DECLARE_COLOR_SHADER(FresnelWeight);
DECLARE_SHADER(OrenNayarBrdf);
DECLARE_SHADER(CookTorranceBrdf);
DECLARE_SHADER(WardDuerBrdf);
DECLARE_SHADER(AshikhminShirleyBrdf);
DECLARE_SHADER(EvaluateLightSample);
DECLARE_SHADER(BrdfIntegrate);
DECLARE_SHADER(MakeFrame);
DECLARE_SHADER(RotateVector);
DECLARE_SHADER(ScaleVector);
DECLARE_SHADER(ShaderGlobalsTweak);
DECLARE_FCV_SHADER(Cache);
DECLARE_SHADER(CacheMatrix);
DECLARE_SHADER(CacheBrdf);
DECLARE_SHADER(Wireframe);
DECLARE_SHADER(ShadowMatte);
DECLARE_SHADER(MakeRay);
DECLARE_SHADER(ReflectRay);
DECLARE_SHADER(RefractRay);
DECLARE_SHADER(Trace);

node_loader
{
   if (i >= gsShaderCount)
   {
      return false;
   }
   REGISTER_FCV_SHADER(Abs, absolute)
   REGISTER_FCV_SHADER(Add, add)
   REGISTER_FCV_SHADER(Bias, bias)
   REGISTER_FCV_SHADER(BiasAndGain, bias_and_gain)
   REGISTER_FCV_SHADER(Ceil, ceil)
   REGISTER_FCV_SHADER(Clamp, clamp)
   REGISTER_SHADER(CompareFloat, compare_float, AI_TYPE_BOOLEAN)
   REGISTER_SHADER(CompareColor, compare_color, AI_TYPE_BOOLEAN)
   REGISTER_SHADER(CompareVector, compare_vector, AI_TYPE_BOOLEAN)
   REGISTER_SHADER(FloatToBool, float_to_bool, AI_TYPE_BOOLEAN)
   REGISTER_SHADER(FloatToInt, float_to_int, AI_TYPE_INT)
   REGISTER_SHADER(VectorToColor, vector_to_color, AI_TYPE_RGB)
   REGISTER_SHADER(ColorToVector, color_to_vector, AI_TYPE_VECTOR)
   REGISTER_SHADER(ColorToFloat, color_to_float, AI_TYPE_FLOAT)
   REGISTER_SHADER(FloatToVector, float_to_vector, AI_TYPE_VECTOR)
   REGISTER_SHADER(FloatToColor, float_to_color, AI_TYPE_RGB)
   REGISTER_SHADER(FloatToRGBA, float_to_rgba, AI_TYPE_RGBA)
   REGISTER_SHADER(BoolToInt, bool_to_int, AI_TYPE_INT)
   REGISTER_SHADER(BoolToFloat, bool_to_float, AI_TYPE_FLOAT)
   REGISTER_SHADER(CrossProduct, cross_product, AI_TYPE_VECTOR)
   REGISTER_FCV_SHADER(Gain, gain)
   REGISTER_FCV_SHADER(Divide, divide)
   REGISTER_SHADER(DotProduct, dot_product, AI_TYPE_FLOAT)
   REGISTER_FCV_SHADER(Exp, exp)
   REGISTER_FCV_SHADER(Floor, floor)
   REGISTER_FCV_SHADER(Invert, invert)
   REGISTER_FCV_SHADER(Log, log)
   REGISTER_FCV_SHADER(Max, max)
   REGISTER_FCV_SHADER(Min, min)
   REGISTER_FCV_SHADER(Mix, mix)
   REGISTER_FCV_SHADER(Modulo, modulo)
   REGISTER_FCV_SHADER(MultiSelect, multi_select)
   REGISTER_FCV_SHADER(Multiply, multiply)
   REGISTER_FCV_SHADER(Negate, negate)
   REGISTER_SHADER(NormalizeVector, normalize_vector, AI_TYPE_VECTOR)
   REGISTER_FCV_SHADER(Pow, pow)
   REGISTER_FCV_SHADER(Remap, remap)
   REGISTER_FCV_SHADER(Round, round)
   REGISTER_FCV_SHADER(Select, select)
   REGISTER_FCV_SHADER(Sign, sign)
   REGISTER_FCV_SHADER(SmoothStep, smoothstep)
   REGISTER_FCV_SHADER(Sqrt, sqrt)
   REGISTER_FCV_SHADER(Subtract, subtract)
   REGISTER_FLOAT_SHADER(Trigonometry, trigonometry)
   REGISTER_VECTOR_SHADER(Trigonometry, trigonometry)
   REGISTER_SHADER(VectorLength, vector_length, AI_TYPE_FLOAT)
   REGISTER_SHADER(ShapeAttrBool, shape_attr_bool, AI_TYPE_BOOLEAN)
   REGISTER_SHADER(ShapeAttrInt, shape_attr_int, AI_TYPE_INT)
   REGISTER_SHADER(ShapeAttrFloat, shape_attr_float, AI_TYPE_FLOAT)
   REGISTER_SHADER(ShapeAttrPoint2, shape_attr_point2, AI_TYPE_POINT2)
   REGISTER_SHADER(ShapeAttrVector, shape_attr_vector, AI_TYPE_VECTOR)
   REGISTER_SHADER(ShapeAttrColor, shape_attr_color, AI_TYPE_RGB)
   REGISTER_SHADER(ShapeAttrRGBA, shape_attr_rgba, AI_TYPE_RGBA)
   REGISTER_SHADER(ShapeAttrString, shape_attr_string, AI_TYPE_STRING)
#ifdef USE_AGSTATE
   REGISTER_SHADER(agIntState, shader_globals_int, AI_TYPE_INT)
   REGISTER_SHADER(agFloatState, shader_globals_float, AI_TYPE_FLOAT)
   REGISTER_SHADER(agColorState, shader_globals_color, AI_TYPE_RGB)
   REGISTER_SHADER(agVectorState, shader_globals_vector, AI_TYPE_VECTOR)
   REGISTER_SHADER(agMatrixState, shader_globals_matrix, AI_TYPE_MATRIX)
   REGISTER_SHADER(agNodeState, shader_globals_node, AI_TYPE_NODE)
#endif
   REGISTER_SHADER(TransformVector, transform_vector, AI_TYPE_VECTOR)
   REGISTER_SHADER(MakeMatrix, make_matrix, AI_TYPE_MATRIX)
   REGISTER_SHADER(MultiplyMatrix, multiply_matrix, AI_TYPE_MATRIX)
   REGISTER_SHADER(SetTraceSet, set_trace_set, AI_TYPE_RGBA)
   REGISTER_SHADER(Shade, shade, AI_TYPE_RGB)
   REGISTER_SHADER(Holdout, holdout, AI_TYPE_RGBA)
   REGISTER_SHADER(ShadingPoint, shading_point, AI_TYPE_POINT)
   REGISTER_SHADER(ShadingNormal, shading_normal, AI_TYPE_VECTOR)
   REGISTER_SHADER(WriteAOVs, write_aovs, AI_TYPE_RGBA)
   REGISTER_SHADER(ReadAOVBool, read_aov_bool, AI_TYPE_BOOLEAN)
   REGISTER_SHADER(ReadAOVInt, read_aov_int, AI_TYPE_INT)
   REGISTER_SHADER(ReadAOVFlt, read_aov_float, AI_TYPE_FLOAT)
   REGISTER_SHADER(ReadAOVPnt2, read_aov_point2, AI_TYPE_POINT2)
   REGISTER_SHADER(ReadAOVPnt, read_aov_point, AI_TYPE_POINT)
   REGISTER_SHADER(ReadAOVVec, read_aov_vector, AI_TYPE_VECTOR)
   REGISTER_SHADER(ReadAOVRGB, read_aov_color, AI_TYPE_RGB)
   REGISTER_SHADER(ReadAOVRGBA, read_aov_rgba, AI_TYPE_RGBA)
   REGISTER_SHADER(InvertMatrix, invert_matrix, AI_TYPE_MATRIX)
   REGISTER_SHADER(TransposeMatrix, transpose_matrix, AI_TYPE_MATRIX)
   REGISTER_SHADER(InterpolateMatrix, interpolate_matrix, AI_TYPE_MATRIX)
   REGISTER_FCV_SHADER(Ramp, ramp)
   REGISTER_FCV_SHADER(SmoothSelect, smooth_select)
   REGISTER_FCV_SHADER(RangeSelect, range_select)
   REGISTER_FCV_SHADER(SmoothRangeSelect, smooth_range_select)
   REGISTER_SHADER(MakePoint2, make_point2, AI_TYPE_POINT2)
   REGISTER_SHADER(MakeVector, make_vector, AI_TYPE_VECTOR)
   REGISTER_SHADER(MakeColor, make_color, AI_TYPE_RGB)
   REGISTER_SHADER(MakeRGBA, make_rgba, AI_TYPE_RGBA)
   REGISTER_FCV_SHADER(Gaussian, gaussian)
#ifdef USE_AGNOISES
   REGISTER_SHADER(Fractal, fractal_noise, AI_TYPE_FLOAT);
   REGISTER_SHADER(Voronoi, voronoi_noise, AI_TYPE_FLOAT);
   REGISTER_SHADER(DistortPoint, distort_point, AI_TYPE_POINT);
#endif
#ifdef USE_AGSEEXPR
   REGISTER_SHADER(agSeExpr, seexpr, AI_TYPE_VECTOR)
#endif
#ifdef USE_AGANIMCURVE
   REGISTER_SHADER(agAnimCurve, curve, AI_TYPE_FLOAT)
#endif
#ifdef USE_AGUSERDATARAMP
   REGISTER_SHADER(agUserDataFloatRamp, shape_attr_ramp_float, AI_TYPE_FLOAT)
   REGISTER_SHADER(agUserDataColorRamp, shape_attr_ramp_color, AI_TYPE_RGB)
   REGISTER_SHADER(agUserDataVectorRamp, shape_attr_ramp_vector, AI_TYPE_VECTOR)
#endif
   REGISTER_SHADER(UVSwitch, uv_switch, AI_TYPE_RGBA)
   REGISTER_SHADER(UVProject, uv_project, AI_TYPE_RGBA)
   REGISTER_SHADER(UVTransform, uv_transform, AI_TYPE_RGBA)
   REGISTER_SHADER(UVClip, uv_clip, AI_TYPE_RGBA)
   REGISTER_SHADER(MakeTx, make_tx, AI_TYPE_STRING)
   REGISTER_SHADER(CameraMatrix, camera_matrix, AI_TYPE_MATRIX)
   REGISTER_SHADER(ImageResolution, image_resolution, AI_TYPE_VECTOR)
   REGISTER_SHADER(RenderResolution, render_resolution, AI_TYPE_VECTOR)
   REGISTER_SHADER(TokenPath, token_path, AI_TYPE_STRING)
   REGISTER_SHADER(Texture, texture, AI_TYPE_RGBA)
   REGISTER_SHADER(WriteMsgs, write_msgs, AI_TYPE_RGBA)
   REGISTER_SHADER(ReadMsgBool, read_msg_bool, AI_TYPE_BOOLEAN)
   REGISTER_SHADER(ReadMsgInt, read_msg_int, AI_TYPE_INT)
   REGISTER_SHADER(ReadMsgFlt, read_msg_float, AI_TYPE_FLOAT)
   REGISTER_SHADER(ReadMsgPnt2, read_msg_point2, AI_TYPE_POINT2)
   REGISTER_SHADER(ReadMsgPnt, read_msg_point, AI_TYPE_POINT)
   REGISTER_SHADER(ReadMsgVec, read_msg_vector, AI_TYPE_VECTOR)
   REGISTER_SHADER(ReadMsgRGB, read_msg_color, AI_TYPE_RGB)
   REGISTER_SHADER(ReadMsgRGBA, read_msg_rgba, AI_TYPE_RGBA)
   REGISTER_SHADER(IlluminanceLoop, illuminance_loop, AI_TYPE_RGB)
   REGISTER_SHADER(LightWeight, light_weight, AI_TYPE_FLOAT)
   REGISTER_SHADER(Reflect, reflect, AI_TYPE_VECTOR)
   REGISTER_SHADER(Refract, refract, AI_TYPE_VECTOR)
   REGISTER_FLOAT_SHADER(FresnelWeight, fresnel_weight)
   REGISTER_COLOR_SHADER(FresnelWeight, fresnel_weight)
   REGISTER_SHADER(OrenNayarBrdf, oren_nayar_brdf, AI_TYPE_RGB)
   REGISTER_SHADER(CookTorranceBrdf, cook_torrance_brdf, AI_TYPE_RGB)
   REGISTER_SHADER(WardDuerBrdf, ward_duer_brdf, AI_TYPE_RGB)
   REGISTER_SHADER(AshikhminShirleyBrdf, ashikhmin_shirley_brdf, AI_TYPE_RGB)
   REGISTER_SHADER(EvaluateLightSample, evaluate_light_sample, AI_TYPE_RGB)
   REGISTER_SHADER(BrdfIntegrate, brdf_integrate, AI_TYPE_RGB)
   REGISTER_SHADER(MakeFrame, make_frame, AI_TYPE_MATRIX)
   REGISTER_SHADER(RotateVector, rotate_vector, AI_TYPE_VECTOR)
   REGISTER_SHADER(ScaleVector, scale_vector, AI_TYPE_VECTOR)
   REGISTER_SHADER(ShaderGlobalsTweak, shader_globlals_tweak, AI_TYPE_RGB)
   REGISTER_FCV_SHADER(Cache, cache)
   REGISTER_SHADER(CacheMatrix, cache_matrix, AI_TYPE_MATRIX)
   REGISTER_SHADER(CacheBrdf, cache_brdf, AI_TYPE_RGB)
   REGISTER_SHADER(Wireframe, wireframe, AI_TYPE_FLOAT)
   REGISTER_SHADER(ShadowMatte, shadow_matte, AI_TYPE_RGB)
   REGISTER_SHADER(MakeRay, make_ray, AI_TYPE_VECTOR)
   REGISTER_SHADER(ReflectRay, reflect_ray, AI_TYPE_VECTOR)
   REGISTER_SHADER(RefractRay, refract_ray, AI_TYPE_VECTOR)
   REGISTER_SHADER(Trace, trace, AI_TYPE_BOOLEAN)
   
   return false;
}

