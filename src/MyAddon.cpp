#include <node.h>

void GetString(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    v8::Isolate *isolate = args.GetIsolate();

    v8::Local<v8::String> value = v8::String::NewFromUtf8(isolate, "String").ToLocalChecked();

    args.GetReturnValue().Set(value);
}

void SumNumbers(const v8::FunctionCallbackInfo<v8::Value> &args)
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

void GetObject(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    v8::Isolate *isolate = args.GetIsolate();

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

    args.GetReturnValue().Set(object);
}

void GetArray(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    v8::Isolate *isolate = args.GetIsolate();

    unsigned int length = 5;

    v8::Local<v8::Array> array = v8::Array::New(isolate, length);

    for (unsigned int i = 0; i < length; ++i)
    {
        v8::Local<v8::Number> value = v8::Number::New(isolate, i + 1);

        v8::Maybe<bool> result = array->Set(isolate->GetCurrentContext(), i, value);
    }

    args.GetReturnValue().Set(array);
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
