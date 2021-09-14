#define EXPORT_FUNCTION(function_name) exports[#function_name] = Function::New<Callback>(env, function_name);
#define EXPORT_FUNCTION_VOID(function_name) exports[#function_name] = Function::New<VoidCallback>(env, function_name);



// #include <iostream>
#include <cstring>
#include <thread>

#include "napi.h"



using namespace Napi;
// using std::cout;
// using std::endl;



void initOrbit (void);
void initGL2 (void);
void loop_function_GL2 (void);
void tran (void);



extern void* pixel_data;

size_t rendering_loop_flag { 1 };



void rendernig_thread (void)
{
	initOrbit();

	initGL2();

	rendering_loop_flag = 1;

	for (; rendering_loop_flag;)
	{
		tran();

		loop_function_GL2();
	}
}

std::thread* rendernig_thread_handle {};

void runRenderingThread (const CallbackInfo& info)
{
	rendernig_thread_handle = new std::thread { rendernig_thread };
}

void stopRenderingThread (const CallbackInfo& info)
{
	rendering_loop_flag = 0;

	delete rendernig_thread_handle;
}

Value testPixelData (const CallbackInfo& info)
{
	return Boolean::New(info.Env(), pixel_data != nullptr);
}

Value getPixelData (const CallbackInfo& info)
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

	TypedArrayOf<uint8_t> typedarray
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

	return typedarray;
}

Object Init (Env env, Object exports)
{
	using Callback = Value (*) (const CallbackInfo&);
	using VoidCallback = void (*) (const CallbackInfo&);

	EXPORT_FUNCTION_VOID(runRenderingThread);
	EXPORT_FUNCTION_VOID(stopRenderingThread);
	EXPORT_FUNCTION(testPixelData);
	EXPORT_FUNCTION(getPixelData);

	return exports;
}

NODE_API_MODULE(node_api_test, Init)
