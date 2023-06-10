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

void RunCallback(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    v8::Isolate *isolate = args.GetIsolate();

    if (args.Length() != 1)
    {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));

        return;
    }

    if (!args[0]->IsFunction())
    {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Wrong arguments type").ToLocalChecked()));

        return;
    }

    v8::Local<v8::Function> callback = args[0].As<v8::Function>();
    
    const unsigned int argc = 1U;

    v8::Local<v8::Value> argv[argc] = {
        v8::Number::New(isolate, 1),
    };

    v8::MaybeLocal<v8::Value> result = callback->Call(isolate->GetCurrentContext(), v8::Null(isolate), argc, argv);
}

void Initialize(v8::Local<v8::Object> exports)
{
    NODE_SET_METHOD(exports, "getHello", GetHello);
    NODE_SET_METHOD(exports, "sum", Sum);
    NODE_SET_METHOD(exports, "runCallback", RunCallback);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
