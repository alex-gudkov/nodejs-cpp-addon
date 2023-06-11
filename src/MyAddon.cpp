#include <node.h>

void GetString(const v8::FunctionCallbackInfo<v8::Value> &argv)
{
    v8::Isolate *isolate = argv.GetIsolate();

    v8::Local<v8::String> string = v8::String::NewFromUtf8(isolate, "Hello world!").ToLocalChecked();

    argv.GetReturnValue().Set(string);
}

void SumNumbers(const v8::FunctionCallbackInfo<v8::Value> &argv)
{
    v8::Isolate *isolate = argv.GetIsolate();

    if (argv.Length() != 2)
    {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));

        return;
    }

    if (!argv[0]->IsNumber() || !argv[1]->IsNumber())
    {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Wrong arguments type").ToLocalChecked()));

        return;
    }

    double arg0 = argv[0].As<v8::Number>()->Value();
    double arg1 = argv[1].As<v8::Number>()->Value();
    double sum = arg0 + arg1;

    argv.GetReturnValue().Set(sum);
}

void RunCallback(const v8::FunctionCallbackInfo<v8::Value> &argv)
{
    v8::Isolate *isolate = argv.GetIsolate();

    if (argv.Length() != 1)
    {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));

        return;
    }

    if (!argv[0]->IsFunction())
    {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Wrong arguments type").ToLocalChecked()));

        return;
    }

    v8::Local<v8::Function> callback = argv[0].As<v8::Function>();

    const size_t callbackArgc = 1;
    v8::Local<v8::Value> callbackArgv[callbackArgc];

    callbackArgv[0] = v8::Number::New(isolate, 12.34);

    v8::MaybeLocal<v8::Value> result = callback->Call(isolate->GetCurrentContext(), v8::Null(isolate), callbackArgc, callbackArgv);
}

void GetObject(const v8::FunctionCallbackInfo<v8::Value> &argv)
{
    v8::Isolate *isolate = argv.GetIsolate();

    v8::Local<v8::Object> object = v8::Object::New(isolate);

    v8::Maybe<bool> result = object->Set(
        isolate->GetCurrentContext(),
        v8::String::NewFromUtf8(isolate, "x").ToLocalChecked(),
        v8::Number::New(isolate, 1)
    );

    result = object->Set(
        isolate->GetCurrentContext(),
        v8::String::NewFromUtf8(isolate, "y").ToLocalChecked(),
        v8::Number::New(isolate, 2)
    );

    argv.GetReturnValue().Set(object);
}

void GetArray(const v8::FunctionCallbackInfo<v8::Value> &argv)
{
    v8::Isolate *isolate = argv.GetIsolate();

    const size_t length = 5;
    v8::Local<v8::Array> array = v8::Array::New(isolate, length);

    for (size_t i = 0; i < length; ++i)
    {
        v8::Local<v8::Number> element = v8::Number::New(isolate, i + 1);

        v8::Maybe<bool> result = array->Set(isolate->GetCurrentContext(), i, element);
    }

    argv.GetReturnValue().Set(array);
}

void Initialize(v8::Local<v8::Object> exports)
{
    NODE_SET_METHOD(exports, "getString", GetString);
    NODE_SET_METHOD(exports, "sumNumbers", SumNumbers);
    NODE_SET_METHOD(exports, "runCallback", RunCallback);
    NODE_SET_METHOD(exports, "getObject", GetObject);
    NODE_SET_METHOD(exports, "getArray", GetArray);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
