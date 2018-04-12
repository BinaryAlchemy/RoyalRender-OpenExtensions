#include "common.h"
#include <string>


bool rrUintArrayToQList(const v8::Local<v8::Array> &fromArray, QList<quint64> &toList)
{
	const int len = fromArray->Length();
	for (int i = 0; i < len; ++i)
	{
		/*v8::Local<v8::Value> ob = fromArray->Get(i);
		if (!rrUint64::objectIs(ob)) {
			return false;
		}

		uint64_t wrapUint = node::ObjectWrap::Unwrap<rrUint64>(ob)->toUint64();
		toList.push_back(wrapUint);*/
	}
	return true;
}

/****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
	rrUint64
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************/

//---------- CONSTRUCTION --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
v8::Persistent<v8::Function> rrUint64::constructor;

rrUint64::rrUint64(void)
{}

rrUint64::~rrUint64(void)
{}

void rrUint64::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	v8::Handle<v8::Object> self = args.This();

	self->SetAccessor(v8::String::NewFromUtf8(isolate, "lower", v8::String::kInternalizedString), getLower, setLower);
	self->SetAccessor(v8::String::NewFromUtf8(isolate, "upper", v8::String::kInternalizedString), getUpper, setUpper);

	self->SetHiddenValue(v8::String::NewFromUtf8(isolate, "__rruint64__", v8::String::kInternalizedString), v8::Null(isolate));
}

v8::Handle<v8::Value> rrUint64::fromUint(uint64_t val) {
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Function> cons = v8::Local<v8::Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	rrUint64* uintOb = node::ObjectWrap::Unwrap<rrUint64>(instance);

	uintOb->lower = (uint32_t)val;
	uintOb->upper = (uint32_t)(val >> 32);

	return instance;
}

bool rrUint64::objectIs(v8::Handle<v8::Object> obj)
{
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(v8::String::NewFromUtf8(isolate,
		"__rruint64__",
		v8::String::kInternalizedString)
		);

	return !val->IsUndefined();
}

// MISC
uint64_t rrUint64::toUint64()
{
	return ((uint64_t)upper << 32) | lower;
}

void rrUint64::toUint64Str(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	rrUint64* self = node::ObjectWrap::Unwrap<rrUint64>(args.This());
	std::string uiString = std::to_string(self->toUint64());

	args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate,
		uiString.c_str(),
		v8::String::kInternalizedString));
}

//---------- ACCESSORS --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void rrUint64::getLower(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	uint32_t low = node::ObjectWrap::Unwrap<rrUint64>(info.Holder())->lower;

	info.GetReturnValue().Set( v8::Number::New(isolate, low) );
}

void rrUint64::setLower(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info)
{
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	CHECKVAL(lower, Number, "Lower part of unsigned int 64")

	node::ObjectWrap::Unwrap<rrUint64>(info.Holder())->lower = value->ToUint32()->Value();
}

void rrUint64::getUpper(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	uint32_t up = node::ObjectWrap::Unwrap<rrUint64>(info.Holder())->upper;

	info.GetReturnValue().Set(v8::Number::New(isolate, up));
}

void rrUint64::setUpper(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info)
{
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	CHECKVAL(lower, Number, "Upper part of unsigned int 64")

	node::ObjectWrap::Unwrap<rrUint64>(info.Holder())->upper = value->ToUint32()->Value();
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(rrUint64, NODE_SET_PROTOTYPE_METHOD(tpl, "toUint64Str", toUint64Str), )
