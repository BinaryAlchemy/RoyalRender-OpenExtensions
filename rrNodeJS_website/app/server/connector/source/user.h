// user.h
#ifndef __NODE_USR__
#define __NODE_USR__

#include <node.h>
#include <v8.h>
#include <node_object_wrap.h>

#include "../../../shared_SDK/RR_defines_SDK.h"
//#include "../../../shared_SDK/RR_version.h"
#include "../../../shared/RR_DataTypes_user.h"
#include "../../../shared/RR_TCP.h"


using namespace v8;

class UserSettings : public node::ObjectWrap
{
public:
	// Creators!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void newInst  (const v8::FunctionCallbackInfo<v8::Value>& info);
	static Local<v8::Object> fromUserSettings(Isolate* isolate, _rrgUserSettings80* _user);
    static Local<v8::Object> fromUserSettings(Isolate* isolate, const _rrgUserSettings80& _user);

	UserSettings(void);
	virtual ~UserSettings(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// Accessors
	static void getBooleans(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<Value>& info);
	static void setBooleans(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info);

	static void getUniqueID(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info);

	static void getName(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info);
	static void setName(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info);

	static void getEmail(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info);
	static void setEmail(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info);

	static void getUserGroup(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info);
	static void setUserGroup(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info);

	static void getLoginUser(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info);
	static void setLoginUser(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info);

	static void getUserAdded(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info);
	static void setUserAdded(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info);

	static void getLastUsed(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info);
	static void setLastUsed(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info);

	static void getMapUNC(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info);
	static void setMapUNC(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info);

	static void getMapLocal(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info);
	static void setMapLocal(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info);

	// ---- init
	static void init(void);

    _rrgUserSettings80* user = NULL;  // stays NULL, unless initialized with fromUserSettings or NewInst(), or manually set;
	bool delInternalPointer = true;

private:
	static v8::Persistent<v8::Function> constructor;
};


class User : public node::ObjectWrap
{
public:
	// Creators!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromUser(_rrTCPuser *user);

	User(void);
	virtual ~User(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// exposed methods
	static void at(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getNewUserPreset(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getAnonymous(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getOurUser(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void count(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

	_rrTCPuser *_user = NULL;  // stays NULL, unless initialized with fromUser method or manually set;

private:
	static v8::Persistent<v8::Function> constructor;
};
#endif
