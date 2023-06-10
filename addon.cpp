#include <node.h>

void GetHello(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    v8::Isolate *isolate = args.GetIsolate();

    args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "Hello").ToLocalChecked());
}

void Initialize(v8::Local<v8::Object> exports)
{
    NODE_SET_METHOD(exports, "getHello", GetHello);
}

NODE_MODULE(addon, Initialize);
