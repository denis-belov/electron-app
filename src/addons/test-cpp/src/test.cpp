#define EXPORT_FUNCTION(function_name) exports[#function_name] = Function::New<Callback>(env, function_name);
#define EXPORT_FUNCTION_VOID(function_name) exports[#function_name] = Function::New<VoidCallback>(env, function_name);
#define EXPORT_OBJECT(name) exports[#name] = name;



// #include <iostream>
#include <cstring>
#include <thread>
// #include <vector>

#include "napi.h"



using namespace Napi;
// using std::cout;
// using std::endl;



void initOrbit (void);
void initGL2 (const size_t&, const size_t&);
void loop_function_GL2 (void);
void rotateOrbit (const float&, const float&);



extern void* pixel_data;

size_t rendering_loop_flag { 1 };

size_t window_xy [2];



void rendernig_thread (void)
{
	initGL2(window_xy[0], window_xy[1]);

	rendering_loop_flag = 1;

	for (; rendering_loop_flag;)
	{
		loop_function_GL2();
	}
}

std::thread* rendernig_thread_handle {};

Value testRenderingThread (const CallbackInfo& info)
{
	return Boolean::New(info.Env(), rendernig_thread_handle != nullptr);
}

void runRenderingThread (const CallbackInfo& info)
{
	initOrbit();

	window_xy[0] = info[0].As<Number>().Uint32Value();
	window_xy[1] = info[1].As<Number>().Uint32Value();

	rendernig_thread_handle = new std::thread { rendernig_thread };
}

void stopRenderingThread (const CallbackInfo& info)
{
	rendering_loop_flag = 0;

	delete rendernig_thread_handle;
}

Value getPixelDataStorageIsAllocated (const CallbackInfo& info)
{
	return Boolean::New(info.Env(), pixel_data != nullptr);
}

Value getPixelDataStorage (const CallbackInfo& info)
{
	ArrayBuffer arraybuffer
	{
		ArrayBuffer::New
		(
			info.Env(),
			pixel_data,
			800 * 600 * 4
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

void rotateOrbitJs (const CallbackInfo& info)
{
	rotateOrbit(info[0].As<Number>(), info[1].As<Number>());
}

Object Init (Env env, Object exports)
{
	using Callback = Value (*) (const CallbackInfo&);
	using VoidCallback = void (*) (const CallbackInfo&);

	EXPORT_FUNCTION(testRenderingThread);
	EXPORT_FUNCTION_VOID(runRenderingThread);
	EXPORT_FUNCTION_VOID(stopRenderingThread);
	EXPORT_FUNCTION(getPixelDataStorageIsAllocated);
	EXPORT_FUNCTION(getPixelDataStorage);
	EXPORT_FUNCTION_VOID(rotateOrbitJs);

	return exports;
}

NODE_API_MODULE(node_api_test, Init)
