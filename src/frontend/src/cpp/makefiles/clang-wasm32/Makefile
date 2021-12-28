ENV=clang-wasm32
SRC=/home/denis/reps/denis-belov/electron-app/src/frontend/src/cpp/src
BUILD=/home/denis/reps/denis-belov/electron-app/src/frontend/src/cpp/build/$(ENV)
NO_LINK=-c
VERBOSE:=-Wall -Wextra -Wabi -Wpedantic -v
NO_STD=--no-standard-libraries
OPT_SLOW=-O1
OPT_MEDIUM=-O2
OPT_FAST=-O3
OPT_SIZE=-Os
OPT_FASTX=-Ofast -funroll-loops
STD_20=-std=c++20
SSE=-msimd128
FLAGS_ADD=-matomics -mbulk-memory
LIBS=/home/denis/libs
REPS=/home/denis/reps
MAKE_H=mkdir -p $(BUILD)/h
MAKE_SPV=mkdir -p $(BUILD)/spv
ASM_EXT=dcmp
LIB_EXT=a

$(BUILD)/output/wasm/main.wasm : $(BUILD)/external/o/$(REPS)/denis-belov/xgk-test/src/main.cpp.o $(REPS)/denis-belov/xgk-math/build/$(ENV)/output/$(LIB_EXT)/xgk-math.$(LIB_EXT) $(REPS)/denis-belov/xgk-api/build/$(ENV)/output/$(LIB_EXT)/xgk-api.$(LIB_EXT) $(REPS)/denis-belov/xgk-aux/build/$(ENV)/output/$(LIB_EXT)/xgk-aux.$(LIB_EXT)
	mkdir -p $(BUILD)/output/wasm && mkdir -p $(BUILD)/output/dcmp && /home/denis/lib/wasi-sdk-14.0/bin/wasm-ld $(BUILD)/external/o/$(REPS)/denis-belov/xgk-test/src/main.cpp.o $(REPS)/denis-belov/xgk-math/build/$(ENV)/output/$(LIB_EXT)/xgk-math.$(LIB_EXT) $(REPS)/denis-belov/xgk-api/build/$(ENV)/output/$(LIB_EXT)/xgk-api.$(LIB_EXT) $(REPS)/denis-belov/xgk-aux/build/$(ENV)/output/$(LIB_EXT)/xgk-aux.$(LIB_EXT) -mwasm32 -error-limit=0 --export-all --no-entry --allow-undefined --no-check-features --import-memory --shared-memory --max-memory=131072 -L /home/denis/lib/wasi-sdk-14.0/share/wasi-sysroot/lib/wasm32-wasi -lc -lc++ -lc++abi -o $(BUILD)/output/wasm/main.wasm

$(BUILD)/external/o/$(REPS)/denis-belov/xgk-test/src/main.cpp.o : $(REPS)/denis-belov/xgk-test/src/main.cpp $(BUILD)/h/spirv_code_vertex.h $(BUILD)/h/spirv_code_fragment.h 
	mkdir -p $(BUILD)/external/o/$(REPS)/denis-belov/xgk-test/src && mkdir -p $(BUILD)/external/dcmp/$(REPS)/denis-belov/xgk-test/src && /home/denis/lib/wasi-sdk-14.0/bin/clang++ $(REPS)/denis-belov/xgk-test/src/main.cpp --target=wasm32-unknown-wasi-unknown -error-limit=0 -fno-exceptions -mthread-model single --sysroot=/home/denis/lib/wasi-sdk-14.0/share/wasi-sysroot $(STD_20) $(NO_LINK) $(VERBOSE) $(OPT_FASTX) $(SSE) $(FLAGS_ADD) -I $(BUILD)/h -I $(REPS)/denis-belov -o $(BUILD)/external/o/$(REPS)/denis-belov/xgk-test/src/main.cpp.o

$(BUILD)/h/spirv_code_vertex.h : $(REPS)/denis-belov/xgk-test/src/code.vert 
	$(MAKE_SPV) && $(MAKE_H) && glslangValidator $(REPS)/denis-belov/xgk-test/src/code.vert -V -t -o $(BUILD)/spv/vertex.spv && spv2uint32 $(BUILD)/spv/vertex.spv $(BUILD)/h/spirv_code_vertex.h spirv_code_vertex

$(BUILD)/h/spirv_code_fragment.h : $(REPS)/denis-belov/xgk-test/src/code.frag 
	$(MAKE_SPV) && $(MAKE_H) && glslangValidator $(REPS)/denis-belov/xgk-test/src/code.frag -V -t -o $(BUILD)/spv/fragment.spv && spv2uint32 $(BUILD)/spv/fragment.spv $(BUILD)/h/spirv_code_fragment.h spirv_code_fragment

$(REPS)/denis-belov/xgk-math/build/$(ENV)/output/$(LIB_EXT)/xgk-math.$(LIB_EXT) : $(REPS)/denis-belov/xgk-math/src/_intrin.h $(REPS)/denis-belov/xgk-math/src/const.cpp $(REPS)/denis-belov/xgk-math/src/mat4/_/mat4-128_.cpp $(REPS)/denis-belov/xgk-math/src/mat4/_/mat4-32_.cpp $(REPS)/denis-belov/xgk-math/src/mat4/_/mat4_.cpp $(REPS)/denis-belov/xgk-math/src/mat4/mat4-128.cpp $(REPS)/denis-belov/xgk-math/src/mat4/mat4-32.cpp $(REPS)/denis-belov/xgk-math/src/mat4/mat4.cpp $(REPS)/denis-belov/xgk-math/src/mat4/mat4.h $(REPS)/denis-belov/xgk-math/src/object/object.cpp $(REPS)/denis-belov/xgk-math/src/object/object.h $(REPS)/denis-belov/xgk-math/src/orbit/orbit.cpp $(REPS)/denis-belov/xgk-math/src/orbit/orbit.h $(REPS)/denis-belov/xgk-math/src/quat/_/quat-128.cpp $(REPS)/denis-belov/xgk-math/src/quat/_/quat-32.cpp $(REPS)/denis-belov/xgk-math/src/quat/_/quat.cpp $(REPS)/denis-belov/xgk-math/src/quat/quat-128.cpp $(REPS)/denis-belov/xgk-math/src/quat/quat-32.cpp $(REPS)/denis-belov/xgk-math/src/quat/quat.cpp $(REPS)/denis-belov/xgk-math/src/quat/quat.h $(REPS)/denis-belov/xgk-math/src/util/util-asm-x64.asm $(REPS)/denis-belov/xgk-math/src/util/util-asm-x64.s $(REPS)/denis-belov/xgk-math/src/util/util.cpp $(REPS)/denis-belov/xgk-math/src/util/util.h $(REPS)/denis-belov/xgk-math/src/vec4/_/vec4-128.cpp $(REPS)/denis-belov/xgk-math/src/vec4/_/vec4-32.cpp $(REPS)/denis-belov/xgk-math/src/vec4/_/vec4.cpp $(REPS)/denis-belov/xgk-math/src/vec4/vec4.cpp $(REPS)/denis-belov/xgk-math/src/vec4/vec4.h
	genmake $(ENV) $(REPS)/denis-belov/xgk-math/genmake.json

$(REPS)/denis-belov/xgk-api/build/$(ENV)/output/$(LIB_EXT)/xgk-api.$(LIB_EXT) : $(REPS)/denis-belov/xgk-api/src/base/base.cpp $(REPS)/denis-belov/xgk-api/src/base/base.h $(REPS)/denis-belov/xgk-api/src/descriptor-set/descriptor-set.cpp $(REPS)/denis-belov/xgk-api/src/descriptor-set/descriptor-set.h $(REPS)/denis-belov/xgk-api/src/material/material.cpp $(REPS)/denis-belov/xgk-api/src/material/material.h $(REPS)/denis-belov/xgk-api/src/object/object.cpp $(REPS)/denis-belov/xgk-api/src/object/object.h $(REPS)/denis-belov/xgk-api/src/renderer/renderer.cpp $(REPS)/denis-belov/xgk-api/src/renderer/renderer.h $(REPS)/denis-belov/xgk-api/src/scene/scene.cpp $(REPS)/denis-belov/xgk-api/src/scene/scene.h $(REPS)/denis-belov/xgk-api/src/uniform/uniform.cpp $(REPS)/denis-belov/xgk-api/src/uniform/uniform.h $(REPS)/denis-belov/xgk-api/src/uniform-block/uniform-block.cpp $(REPS)/denis-belov/xgk-api/src/uniform-block/uniform-block.h
	genmake $(ENV) $(REPS)/denis-belov/xgk-api/genmake.json

$(REPS)/denis-belov/xgk-aux/build/$(ENV)/output/$(LIB_EXT)/xgk-aux.$(LIB_EXT) : $(REPS)/denis-belov/xgk-aux/src/meas/meas.cpp $(REPS)/denis-belov/xgk-aux/src/meas/meas.h $(REPS)/denis-belov/xgk-aux/src/transition/transition.cpp $(REPS)/denis-belov/xgk-aux/src/transition/transition.h $(REPS)/denis-belov/xgk-aux/src/transition-stack/transition-stack.cpp $(REPS)/denis-belov/xgk-aux/src/transition-stack/transition-stack.h
	genmake $(ENV) $(REPS)/denis-belov/xgk-aux/genmake.json
