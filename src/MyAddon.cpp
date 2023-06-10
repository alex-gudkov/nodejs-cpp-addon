#include <node.h>

void GetHello(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    v8::Isolate *isolate = args.GetIsolate();

    args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "Hello").ToLocalChecked());
}

void Sum(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    v8::Isolate *isolate = args.GetIsolate();

    if (args.Length() != 2)
    {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));

        return;
    }

    if (!args[0]->IsNumber() || !args[1]->IsNumber())
    {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Wrong arguments type").ToLocalChecked()));

        return;
    }

    double arg0 = args[0].As<v8::Number>()->Value();
    double arg1 = args[1].As<v8::Number>()->Value();
    double value = arg0 + arg1;

    args.GetReturnValue().Set(value);
}

void Initialize(v8::Local<v8::Object> exports)
{
    NODE_SET_METHOD(exports, "getHello", GetHello);
    NODE_SET_METHOD(exports, "sum", Sum);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
