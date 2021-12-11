#define EXPORT_FUNCTION(function_name) exports[#function_name] = Function::New<Callback>(env, function_name);
#define EXPORT_FUNCTION_VOID(function_name) exports[#function_name] = Function::New<VoidCallback>(env, function_name);
#define EXPORT_OBJECT(name) exports[#name] = name;



#include <cstdint>
#include <cstring>
#include <thread>

#include "napi.h"

#include "xgk-opengl/src/opengl.h"



// // #include <iostream>
// // using std::cout;
// // using std::endl;



using namespace Napi;



extern void initOpengl (void);



extern XGK::OPENGL::RendererOffscreen* _renderer;



void rendernig_thread (void)
{
	initOpengl();
}

std::thread* rendernig_thread_handle {};

Value testRenderingThread (const CallbackInfo& info)
{
	return Boolean::New(info.Env(), rendernig_thread_handle != nullptr);
}

void runRenderingThread (const CallbackInfo& info)
{
	rendernig_thread_handle = new std::thread { rendernig_thread };
}

void stopRenderingThread (const CallbackInfo& info)
{
	delete rendernig_thread_handle;
}

Value getPixelDataStorageIsAllocated (const CallbackInfo& info)
{
	return Boolean::New(info.Env(), _renderer->pixel_data != nullptr);
}

Value getPixelDataStorage (const CallbackInfo& info)
{
	ArrayBuffer arraybuffer
	{
		ArrayBuffer::New
		(
			info.Env(),
			_renderer->pixel_data,
			_renderer->wrapper->width * _renderer->wrapper->height * 4
		),
	};

	TypedArrayOf<uint8_t> uint8_clamped_array
	{
		TypedArrayOf<uint8_t>::New
		(
			info.Env(),
			arraybuffer.ByteLength(),
			arraybuffer,
			0,
			napi_uint8_clamped_array
		),
	};

	return uint8_clamped_array;
}

// void rotateOrbitJs (const CallbackInfo& info)
// {
// 	rotateOrbit(info[0].As<Number>(), info[1].As<Number>());
// }

Object Init (Env env, Object exports)
{
	using Callback = Value (*) (const CallbackInfo&);
	using VoidCallback = void (*) (const CallbackInfo&);

	EXPORT_FUNCTION(testRenderingThread);
	EXPORT_FUNCTION_VOID(runRenderingThread);
	EXPORT_FUNCTION_VOID(stopRenderingThread);
	EXPORT_FUNCTION(getPixelDataStorageIsAllocated);
	EXPORT_FUNCTION(getPixelDataStorage);
	// EXPORT_FUNCTION_VOID(rotateOrbitJs);

	return exports;
}

NODE_API_MODULE(node_api_test, Init)
