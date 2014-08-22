import sys
import glob
import re
import os
import excons
import shutil
from excons.tools import arnold

env = excons.MakeBaseEnv()

withState = (int(ARGUMENTS.get("with-state", "1")) != 0)
withNoises = (int(ARGUMENTS.get("with-noises", "1")) != 0)
withSeExpr = (int(ARGUMENTS.get("with-seexpr", "1")) != 0)
withAnimCurve = (int(ARGUMENTS.get("with-animcurve", "1")) != 0)
withUserDataRamp = (int(ARGUMENTS.get("with-userdataramp", "1")) != 0)
shdprefix = ARGUMENTS.get("shaders-prefix", "gas_")

def check_symbols(*args, **kwargs):
  import subprocess
  
  try:
    
    _, arnilib = excons.GetDirs("arnold", libdirname=("bin" if sys.platform != "win32" else "lib"))
    
    envvar = ("PATH" if sys.platform == "win32" else ("DYLD_LIBRARY_PATH" if sys.platform == "darwin" else "LD_LIBRARY_PATH"))
    
    if not arnilib in os.environ.get(envvar, ""):
      os.environ[envvar] = os.environ.get(envvar, "") + os.pathsep + arnilib
    
    cmd = "python -c \"import ctypes; ctypes.cdll.LoadLibrary('%s')\"" % kwargs["target"][0]
    
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = p.communicate()
    
    if p.returncode != 0:
      raise Exception(err)
    
  except Exception, e:
    msg = str(e)
    
    if "undefined symbol" in msg:
      print("\n!!! MISSING SYMBOLS FOUND !!!")
    else:
      print("\n!!! FAILED TO CHECK SYMBOLS !!!")
    
    print(msg)
    
    sys.exit(1)

def make_mtd():
  nodeexp = re.compile(r"^(\s*\[\s*node\s+)([^]]+)(\s*\]\s*)$")
  df = open("agShadingBlocks.mtd", "w")
  
  def append_file_content(path, remap={}):
    if not os.path.isfile(path):
      return
    sf = open(path, "r")
    for line in sf.readlines():
      m = nodeexp.match(line)
      if m:
        df.write("%s%s%s%s" % (m.group(1), shdprefix, remap.get(m.group(2), m.group(2)), m.group(3)))
      else:
        df.write(line)
    sf.close()
  
  append_file_content("src/agShadingBlocks.mtd")
  
  if withState:
    df.write("\n")
    append_file_content("agState/src/agState.mtd", remap={"vector_state": "globals_v",
                                                          "float_state": "globals_f",
                                                          "color_state": "globals_c3",
                                                          "integer_state": "globals_i",
                                                          "matrix_state": "globals_m",
                                                          "node_state": "globals_n"})
  
  if withNoises:
    df.write("\n")
    append_file_content("agNoises/src/agNoises.mtd", remap={"ln_factal": "fractal_noise",
                                                            "ln_voronoi": "voronoi_noise",
                                                            "ln_distort_point": "distort_point"})
  
  if withSeExpr:
    df.write("\n")
    append_file_content("agSeExpr/src/agSeExpr.mtd")
  
  if withAnimCurve:
    df.write("\n")
    append_file_content("agAnimCurve/src/agAnimCurve.mtd", remap={"anim_curve": "curve"})
  
  if withUserDataRamp:
    df.write("\n")
    append_file_content("agUserDataRamp/src/agUserDataRamp.mtd", remap={"userDataFloatRamp": "shape_attr_ramp_f",
                                                                        "userDataColorRamp": "shape_attr_ramp_c3",
                                                                        "userDataVectorRamp": "shape_attr_ramp_v"})
  
  df.write("\n")
  df.close()


defs = []
incs = []
libs = []
extra_srcs = []

if withState:
  defs.append("USE_AGSTATE")
  incs.append("agState")
  extra_srcs += glob.glob("agState/src/ag?*State.cpp")

if withNoises:
  defs.append("USE_AGNOISES")
  incs.append("agNoises/src")
  extra_srcs += glob.glob("agNoises/src/ln_*.cpp") + \
                glob.glob("agNoises/src/libnoise/*.cpp") + \
                glob.glob("agNoises/src/stegu/*.cpp")

if withSeExpr:
  ARGUMENTS["static"] = "1"
  SConscript("agSeExpr/SeExpr/SConstruct")
  defs.append("USE_AGSEEXPR")
  incs.append("agSeExpr")
  libs.append("SeExpr")
  extra_srcs += ["agSeExpr/src/agSeExpr.cpp"]

if withAnimCurve:
  defs.extend(["USE_AGANIMCURVE", "GMATH_STATIC"])
  incs.append("agAnimCurve/gmath/include")
  extra_srcs += ["agAnimCurve/src/agAnimCurve.cpp",
                 "agAnimCurve/gmath/src/lib/curve.cpp",
                 "agAnimCurve/gmath/src/lib/polynomial.cpp",
                 "agAnimCurve/gmath/src/lib/vector.cpp"]
  
if withUserDataRamp:
  defs.append("USE_AGUSERDATARAMP")
  incs.append("agUserDataRamp/src")
  extra_srcs += glob.glob("agUserDataRamp/src/agUserData*.cpp")

make_mtd()

prjs = [
  {"name": "agShadingBlocks",
   "type": "dynamicmodule",
   "defs": defs,
   "incdirs": incs,
   "ext": arnold.PluginExt(),
   "libs": libs,
   "srcs": glob.glob("src/*.cpp") + extra_srcs,
   "install": {"": "agShadingBlocks.mtd"},
   "custom": [arnold.Require],
   "post": [check_symbols]
  }
]

env.Append(CPPFLAGS=" -DSHADERS_PREFIX=\"\\\"%s\\\"\"" % shdprefix)
if sys.platform != "win32":
  env.Append(CPPFLAGS=" -Wno-unused-parameter")

excons.DeclareTargets(env, prjs)

Default("agShadingBlocks")
