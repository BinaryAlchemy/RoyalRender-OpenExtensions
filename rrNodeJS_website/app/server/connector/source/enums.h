#ifndef __ENUM_CODE__
#define __ENUM_CODE__

#include <stdarg.h>


//! Assign an object with "name: prop_name" and "value: prop_val" to props
static void set_enum_prop(v8::Isolate* isolate, v8::Local<v8::Object>& props,
                                                v8::Local<v8::String>& prop_name,
										        v8::Local<v8::Integer>& prop_val)
{
	v8::Local<v8::Object> prop = v8::Object::New(isolate);
	prop->Set(v8::String::NewFromUtf8(isolate, "name", v8::String::kInternalizedString), prop_name);
	prop->Set(v8::String::NewFromUtf8(isolate, "value", v8::String::kInternalizedString), prop_val);

	props->Set(prop_val->Value(), prop);
}


//! Return a Names/Integers object with a values/names subobject for reversal search, i.e.
//!
//! { NAME_1: 1,
//!   NAME_2: 2,
//!   ...
//!   properties:
//!   { '1' : { name: 'NAME_1', value : 1 },
//!     '2' : { name: 'NAME_2', value : 2 },
//!     ...
//!   }
static v8::Local<v8::Object> enum_props(v8::Isolate* isolate, int step, int count, ...)
{
	va_list args;
	va_start(args, count);

	v8::Local<v8::Object> props = v8::Object::New(isolate);  // properties name and value
	v8::Local<v8::Object> enum_ob = v8::Object::New(isolate);  // node enum attribute

	for (int i = 0; i < count * step; i += step) {
		v8::Local<v8::String> prop_name = v8::String::NewFromUtf8(isolate, va_arg(args, char*), v8::String::kInternalizedString);
		v8::Local<v8::Integer> prop_val = v8::Int32::New(isolate, i);

		enum_ob->Set(prop_name, prop_val);
		set_enum_prop(isolate, props, prop_name, prop_val);
	}
	va_end(args);

	enum_ob->Set(v8::String::NewFromUtf8(isolate, "properties", v8::String::kInternalizedString), props);
	return enum_ob;
}


//! Return a Names/Bits object with a values/names subobject for reversal search, i.e.
//!
//! { NAME_1: 01,
//!   NAME_2: 10,
//!   ...
//!   properties:
//!   { '01' : { name: 'NAME_1', value : 01 },
//!     '10' : { name: 'NAME_2', value : 10 },
//!     ...
//!   }
static v8::Local<v8::Object> enum_props_binary(v8::Isolate* isolate, int step, int count, ...)
{
	va_list args;
	va_start(args, count);

	v8::Local<v8::Object> props = v8::Object::New(isolate);  // properties name and value
	v8::Local<v8::Object> enum_ob = v8::Object::New(isolate);  // node enum attribute

	int i = 1;
	int bitcount = 1 << count;
	while (i < bitcount) {
		v8::Local<v8::String> prop_name = v8::String::NewFromUtf8(isolate, va_arg(args, char*), v8::String::kInternalizedString);
		v8::Local<v8::Integer> prop_val = v8::Int32::New(isolate, i);

		enum_ob->Set(prop_name, prop_val);
		set_enum_prop(isolate, props, prop_name, prop_val);
		i <<= step;
	}

	va_end(args);

	enum_ob->Set(v8::String::NewFromUtf8(isolate, "properties", v8::String::kInternalizedString), props);
	return enum_ob;
}


//! Redefine ENUM_TYPE macros to convert included .enum files into javascript objects

#undef ENUM_TYPE
#define ENUM_TYPE(item,value,str) \
obname = v8::String::NewFromUtf8(isolate, #item, v8::String::kInternalizedString); \
obval = v8::Number::New(isolate, value); \
obj->Set(obname, obval); \
	\
v8::Local<v8::Object> obj##item = v8::Object::New(isolate); \
obj##item->Set(v8::String::NewFromUtf8(isolate, "name", v8::String::kInternalizedString), obname); \
obj##item->Set(v8::String::NewFromUtf8(isolate, "value", v8::String::kInternalizedString), obval); \
obj##item->Set(v8::String::NewFromUtf8(isolate, "description", v8::String::kInternalizedString), v8::String::NewFromUtf8(isolate, #str, v8::String::kInternalizedString)); \
	\
props->Set(value, obj##item); \
++count;


#undef ENUM_TOTAL
#define ENUM_TOTAL(item) obj->Set(v8::String::NewFromUtf8(isolate, #item, v8::String::kInternalizedString), v8::Number::New(isolate, count));


#undef ENUM_TYPE_RRParam
#define ENUM_TYPE_RRParam(ID, UIlocation, UItype, allowchangeDefault, allowchange_AfterSubmit, defaultValue, min,max, enumName, description, dtext1, dtext2, dtext3, dtext4, dtext5, dtext6) ENUM_TYPE(enumName, ID, description)
#undef ENUM_RRParam_TOTAL
#define ENUM_RRParam_TOTAL(item) ENUM_TOTAL(item)


#undef ENUM_TYPE_RRO
#define ENUM_TYPE_RRO(ID, name, submitterlocation, description, allowchangeDefault, checkedDefault,allowchange_AfterSubmit) ENUM_TYPE(name, ID, description)


//! Set scope variables for .enum inclusion
#define ENUM_PRE_INCLUDE \
int count = 0; \
v8::Local<v8::Number> obval; \
v8::Local<v8::String> obname; \
v8::Local<Object> obj = v8::Object::New(isolate); \
v8::Local<v8::Object> props = v8::Object::New(isolate);

#endif
