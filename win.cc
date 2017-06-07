#include <node.h>
#include <windows.h>

namespace win {
	using v8::Exception;
	using v8::FunctionCallbackInfo;
	using v8::Isolate;
	using v8::Local;
	using v8::Object;
	using v8::String;
	using v8::Value;

	void _keybd_event(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		// Check the number of arguments passed.
		if (args.Length() < 4) {
			// Throw an Error that is passed back to JavaScript
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "Wrong number of arguments. Should be 4.")));
			return;
		}

		// Check the argument types
		if (!args[0]->IsUint32() || !args[1]->IsUint32() || !args[2]->IsUint32() || !args[3]->IsUint32()) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "Wrong arguments")));
			return;
		}
		//A virtual - key code.The code must be a value in the range 1 to 254. For a complete list, see Virtual Key Codes.
		BYTE bVk = args[0]->Uint32Value();
		//A hardware scan code for the key.
		BYTE bScan = args[1]->Uint32Value();
		//Controls various aspects of function operation.This parameter can be one or more of the following values.
		DWORD dwFlags = args[2]->Uint32Value();
		//An additional value associated with the key stroke. 
		ULONG_PTR dwExtraInfo = args[2]->Uint32Value();

		keybd_event(bVk, bScan, dwFlags, dwExtraInfo);
	}

	void init(Local<Object> exports) {
		NODE_SET_METHOD(exports, "keybd_event", _keybd_event);
	}

	NODE_MODULE(addon, init)

}  // namespace win