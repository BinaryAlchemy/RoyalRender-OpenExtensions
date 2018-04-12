#ifndef __COMMON_CODE__
#define __COMMON_CODE__

#include <node.h>
#include <v8.h>
#include <node_object_wrap.h>

#include <QList>

/*!
\def INIT_RR_WRAP(_CLASS_NAME_, _METHODS_, _PRE_INIT_)
Initialize a node wrapper object, with methods and pre initialize code (usually used for sub nodes or properties)
*/
#define INIT_RR_WRAP(_CLASS_NAME_, _METHODS_, _PRE_INIT_) void _CLASS_NAME_::init(void)\
{\
	_PRE_INIT_ \
	v8::Isolate *isolate = v8::Isolate::GetCurrent();\
	v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, construct);\
	_METHODS_;\
	tpl->SetClassName(v8::String::NewFromUtf8(isolate, #_CLASS_NAME_, v8::String::kInternalizedString));\
	tpl->InstanceTemplate()->SetInternalFieldCount(1);\
	constructor.Reset(isolate, tpl->GetFunction());\
}


/*!
\def ARGSDESCR(...)
Expand supplied descriptions to string (arg1, arg2, arg3)
*/
#define ARGSDESCR(...) "("#__VA_ARGS__")"


/*!
\def ARGSEXCEPT(_FUNC_NAME_, _ARGSDESCR_, ...)
Throw a node exception and exit _FUNC_NAME_, append the args description to the printout 
*/
#define ARGSEXCEPT(_FUNC_NAME_, _ARGSDESCR_, _CALLBACK_, ...) v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(\
	isolate, #_FUNC_NAME_" expects "#__VA_ARGS__" " _ARGSDESCR_, v8::String::kInternalizedString\
	);\
isolate->ThrowException(v8::Exception::Error(exceptionString));\
_CALLBACK_.GetReturnValue().Set(v8::Undefined(isolate));\
return;

/*!
\def CHECKVAL(_ATTR_NAME_, _TYPE_, _ATTRDESCR_)
Check if value submitted to _ATTR_NAME_ is valid, call exception if  it isn't
*/
#define CHECKVAL(_ATTR_NAME_, _TYPE_, _ATTRDESCR_) if ( !(value->Is ##_TYPE_()) ) {ARGSEXCEPT(_ATTR_NAME_, _ATTRDESCR_, info, _TYPE_)}


/*!
\def CHECKARGS_1(_FUNC_NAME_, _TYPE_0, _ARGSDESCR_)
Check if argument required by _FUNC_NAME_ is supplied, call exception if  it isn't
*/
#define CHECKARGS_1(_FUNC_NAME_, _TYPE_0, _ARGSDESCR_) if ( !(args[0]->Is ##_TYPE_0()) ) {ARGSEXCEPT(_FUNC_NAME_, _ARGSDESCR_, args, _TYPE_0)}

/*!
\def CHECKARGS_2(_FUNC_NAME_, _TYPE_0, _TYPE_1, _ARGSDESCR_)
Check if the two arguments required by _FUNC_NAME_ are supplied, call exception if  they aren't
*/
#define CHECKARGS_2(_FUNC_NAME_,_TYPE_0, _TYPE_1, _ARGSDESCR_) if (!( (args[0]->Is##_TYPE_0()) && (args[1]->Is##_TYPE_1()) )) {ARGSEXCEPT(_FUNC_NAME_, _ARGSDESCR_, args,  _TYPE_0, _TYPE_1)}

/*!
\def CHECKARGS_3(_FUNC_NAME_, _TYPE_0, _TYPE_1, _TYPE_2, _ARGSDESCR_)
Check if the three arguments required by _FUNC_NAME_ are supplied, call exception if  they aren't
*/
#define CHECKARGS_3(_FUNC_NAME_,_TYPE_0, _TYPE_1, _TYPE_2, _ARGSDESCR_) if (!( (args[0]->Is##_TYPE_0()) && (args[1]->Is##_TYPE_1()) && (args[2]->Is ##_TYPE_2()) )) {ARGSEXCEPT(_FUNC_NAME_, _ARGSDESCR_, args, _TYPE_0, _TYPE_1, _TYPE_2)}

/*!
\def CHECKARGS_4(_FUNC_NAME_, _TYPE_0, _TYPE_1, _TYPE_2, _ARGSDESCR_)
Check if the four arguments required by _FUNC_NAME_ are supplied, call exception if  they aren't
*/
#define CHECKARGS_4(_FUNC_NAME_,_TYPE_0, _TYPE_1, _TYPE_2, _TYPE_3, _ARGSDESCR_) if (!( (args[0]->Is ## _TYPE_0()) && (args[1]->Is##_TYPE_1()) && (args[2]->Is##_TYPE_2()) && (args[3]->Is##_TYPE_3()) )) {ARGSEXCEPT(_FUNC_NAME_, _ARGSDESCR_, args, _TYPE_0, _TYPE_1, _TYPE_2, _TYPE_3)}

/*!
\def CHECKARGS_4(_FUNC_NAME_, _TYPE_0, _TYPE_1, _TYPE_2, _ARGSDESCR_)
Check if the four arguments required by _FUNC_NAME_ are supplied, call exception if  they aren't
*/
#define CHECKARGS_5(_FUNC_NAME_,_TYPE_0, _TYPE_1, _TYPE_2, _TYPE_3, _TYPE_4, _ARGSDESCR_) if (!( (args[0]->Is ## _TYPE_0()) && (args[1]->Is##_TYPE_1()) && (args[2]->Is##_TYPE_2()) && (args[3]->Is##_TYPE_3()) && (args[4]->Is##_TYPE_4()) )) {ARGSEXCEPT(_FUNC_NAME_, _ARGSDESCR_, args, _TYPE_0, _TYPE_1, _TYPE_2, _TYPE_3)}

//!

bool rrUintArrayToQList(const v8::Local<v8::Array> &fromArray, QList<quint64> &toList);

template <typename TYPE_FROM>
static void arrayToQList(const v8::Local<TYPE_FROM> &fromArray, QList<quint64> &toList)
{
	const int len = fromArray->Length();
	for (int i = 0; i < len; ++i)
	{
		toList.push_back(fromArray->Get(i)->ToNumber()->Value());
	}
}

template <typename TYPE_FROM>
static void arrayToQList(const v8::Local<TYPE_FROM> &fromArray, QList<qint32> &toList)
{
	const int len = fromArray->Length();
	for (int i = 0; i < len; ++i)
	{
		toList.push_back(fromArray->Get(i)->ToInt32()->Value());
	}
}


class rrUint64 : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);

	rrUint64(void);
	virtual ~rrUint64(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getLower(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& args);
	static void setLower(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
	static void getUpper(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& args);
	static void setUpper(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);

	// ---- init
	static void init(void);
	static v8::Handle<v8::Value> fromUint(uint64_t);

	bool a;
	uint32_t upper;
	uint32_t lower;

	uint64_t toUint64();
	static void toUint64Str(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
	static v8::Persistent<v8::Function> constructor;
};

#endif