// user.cpp

#include <string>
#include <map>
#include <stddef.h>

#include "user.h"
#include "common.h"


typedef std::map<std::string, short> boolMapOffset;		// mapping the array index of a variable if _rrgUserSettings was an bool array!
static boolMapOffset boolOffsets;

//---------- CONSTRUCTION -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	v8::Persistent<v8::Function> UserSettings::constructor;

	void UserSettings::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		Handle<Object> self = args.This();
		UserSettings *user = new UserSettings();
		user->Wrap(self);

		for (boolMapOffset::const_iterator beg = boolOffsets.begin(), end = boolOffsets.end(); beg != end; ++beg)
			self->SetAccessor(String::NewFromUtf8(isolate, beg->first.c_str(), v8::String::kInternalizedString), getBooleans, setBooleans);

		self->SetAccessor(String::NewFromUtf8(isolate, "name", v8::String::kInternalizedString), getName, setName);
		self->SetAccessor(String::NewFromUtf8(isolate, "uniqueID", v8::String::kInternalizedString), getUniqueID);
		self->SetAccessor(String::NewFromUtf8(isolate, "loginUser", v8::String::kInternalizedString), getLoginUser, setLoginUser);
		self->SetAccessor(String::NewFromUtf8(isolate, "emailAddress", v8::String::kInternalizedString), getEmail, setEmail);
		self->SetAccessor(String::NewFromUtf8(isolate, "mapUNC", v8::String::kInternalizedString), getMapUNC, setMapUNC);
		self->SetAccessor(String::NewFromUtf8(isolate, "mapLocal", v8::String::kInternalizedString), getMapLocal, setMapLocal);
		self->SetAccessor(String::NewFromUtf8(isolate, "userGroup", v8::String::kInternalizedString), getUserGroup, setUserGroup);
		self->SetAccessor(String::NewFromUtf8(isolate, "userAdded", v8::String::kInternalizedString), getUserAdded, setUserAdded);
		self->SetAccessor(String::NewFromUtf8(isolate, "lastUsed", v8::String::kInternalizedString), getLastUsed, setLastUsed);

		self->SetHiddenValue(String::NewFromUtf8(isolate, "__usr_set__", v8::String::kInternalizedString), v8::Null(isolate));
		
		args.GetReturnValue().Set(self);
	}

	void UserSettings::newInst(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		const unsigned argc = 1;
		Handle<Value> argv[argc] = { args[0] };

		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

		UserSettings* settings = ObjectWrap::Unwrap<UserSettings>(instance);
		settings->user = new _rrgUserSettings80();

		args.GetReturnValue().Set(instance);
	}

    Local<v8::Object> UserSettings::fromUserSettings(Isolate* isolate, _rrgUserSettings80* _user)
	{
		// no scope because this is called from other C++ code!
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance();

		UserSettings* settings = ObjectWrap::Unwrap<UserSettings>(instance);

		settings->delInternalPointer = false;
		ObjectWrap::Unwrap<UserSettings>(instance)->user = _user;

		return instance;
	}

    Local<v8::Object> UserSettings::fromUserSettings(Isolate* isolate, const _rrgUserSettings80& _user)
	{
		// no scope because this is called from other C++ code!
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance();

		UserSettings* settings = ObjectWrap::Unwrap<UserSettings>(instance);

		ObjectWrap::Unwrap<UserSettings>(instance)->user = new _rrgUserSettings80(_user);

		return instance;
	}

	UserSettings::UserSettings(void)
	{}

	UserSettings::~UserSettings(void)
	{
		if (delInternalPointer)
		{
			delete user;
		}
	}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	bool UserSettings::objectIs(v8::Handle<v8::Object> obj)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
			"__usr_set__",
			String::kInternalizedString)
			);

		return !val->IsUndefined();
	}

//---------- ACCESSORS -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void UserSettings::getBooleans(Local<v8::String> name, const PropertyCallbackInfo<Value> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
		const UserSettings *user = ObjectWrap::Unwrap<UserSettings>(info.Holder());

		const short offset = boolOffsets.find(*v8::String::Utf8Value(name->ToString()))->second;
		const bool success = ( (const bool*)&(user->user) )[offset];

		info.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
	}

	void UserSettings::setBooleans(Local<String> name, Local<Value> value, const PropertyCallbackInfo<void> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
		UserSettings *user = ObjectWrap::Unwrap<UserSettings>(info.Holder());

		const short offset = boolOffsets.find(*v8::String::Utf8Value(name->ToString()))->second;
		( (bool*)&(user->user) )[offset] = value->ToBoolean()->Value();
	}

	void UserSettings::getUniqueID(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
		quint16 unID = ObjectWrap::Unwrap<UserSettings>(info.Holder())->user->uniqueID;
		info.GetReturnValue().Set(v8::Number::New(isolate, unID));
	}

	void UserSettings::getName(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
        _rrString100 &_name = ObjectWrap::Unwrap<UserSettings>(info.Holder())->user->name;
		info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, _name.toRRUTF8().value, v8::String::kInternalizedString));
	}

	void UserSettings::setName(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
		if (!value->IsString()) {
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate, "the user name needs to be a string", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
		}
		else
		{
			UserSettings *user = ObjectWrap::Unwrap<UserSettings>(info.Holder());
			user->user->name = *v8::String::Utf8Value(value->ToString());
		}
	}

	void UserSettings::getEmail(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
        _rrString8_100 &email = ObjectWrap::Unwrap<UserSettings>(info.Holder())->user->emailAddress;
		info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, std::string(email.value, email.length).c_str(), v8::String::kInternalizedString));
	}

	void UserSettings::setEmail(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
		if (!value->IsString()) {
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate, "the e-mail needs to be a string", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
		}
		else
		{
			UserSettings *user = ObjectWrap::Unwrap<UserSettings>(info.Holder());
			user->user->emailAddress = *v8::String::Utf8Value(value->ToString());
		}
	}

	void UserSettings::getUserAdded(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		_rrTime& userAdded = ObjectWrap::Unwrap<UserSettings>(info.Holder())->user->userAdded;
		info.GetReturnValue().Set(v8::Date::New(isolate, userAdded.toLocalTime() * 1000));
	}

	void UserSettings::setUserAdded(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		if (value->IsDate())
		{
			qint64 millisSinceEpoch = v8::Date::Cast(*value)->NumberValue();
			ObjectWrap::Unwrap<UserSettings>(info.Holder())->user->userAdded.value = millisSinceEpoch / 1000;
		}
		else
		{
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate, "userAdded needs to be a Date", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
		}
	}

	void UserSettings::getLastUsed(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		_rrTime& userAdded = ObjectWrap::Unwrap<UserSettings>(info.Holder())->user->lastUsed;
		info.GetReturnValue().Set(v8::Date::New(isolate, userAdded.toLocalTime() * 1000));
	}

	void UserSettings::setLastUsed(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		if (value->IsDate())
		{
			qint64 millisSinceEpoch = v8::Date::Cast(*value)->NumberValue();
			ObjectWrap::Unwrap<UserSettings>(info.Holder())->user->lastUsed.value = millisSinceEpoch / 1000;
		}
		else
		{
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate, "lastUsed needs to be a Date", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
		}
	}

	void UserSettings::getLoginUser(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		_rrString50 &userGrp = ObjectWrap::Unwrap<UserSettings>(info.Holder())->user->loginUser;
		info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, userGrp.toRRUTF8().value, v8::String::kInternalizedString));
	}

	void UserSettings::setLoginUser(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
		if (!value->IsString()) {
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate, "loginUser needs to be a string", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
		}
		else
		{
			UserSettings *user = ObjectWrap::Unwrap<UserSettings>(info.Holder());
			user->user->loginUser = *v8::String::Utf8Value(value->ToString());
		}
	}

	void UserSettings::getUserGroup(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		_rrString50 &userGrp = ObjectWrap::Unwrap<UserSettings>(info.Holder())->user->userGroup;
		info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, userGrp.toRRUTF8().value, v8::String::kInternalizedString));
	}

	void UserSettings::setUserGroup(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
		if (!value->IsString()) {
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate, "the userGroup needs to be a string", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
		}
		else
		{
			UserSettings *user = ObjectWrap::Unwrap<UserSettings>(info.Holder());
			user->user->userGroup = *v8::String::Utf8Value(value->ToString());
		}
	}

	void UserSettings::getMapUNC(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
        _rrString8_100 &MapUNC = ObjectWrap::Unwrap<UserSettings>(info.Holder())->user->mapUNC;
		info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, std::string(MapUNC.value, MapUNC.length).c_str(), v8::String::kInternalizedString));
	}

	void UserSettings::setMapUNC(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
		if (!value->IsString()) {
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate, "the MapUNC needs to be a string", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
		}
		else
		{
			UserSettings *user = ObjectWrap::Unwrap<UserSettings>(info.Holder());
			user->user->mapUNC = *v8::String::Utf8Value(value->ToString());
		}
	}

	void UserSettings::getMapLocal(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
        _rrString8_50 &MapLocal = ObjectWrap::Unwrap<UserSettings>(info.Holder())->user->mapLocal;
		info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, std::string(MapLocal.value, MapLocal.length).c_str(), v8::String::kInternalizedString));
	}

	void UserSettings::setMapLocal(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
		if (!value->IsString()) {
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate, "the MapLocal needs to be a string", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
		}
		else
		{
			UserSettings *user = ObjectWrap::Unwrap<UserSettings>(info.Holder());
			user->user->mapLocal = *v8::String::Utf8Value(value->ToString());
		}
	}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void UserSettings::init(void)
	{
		// init the bool offsets!
        boolOffsets["emailStatus"] = (short)offsetof(_rrgUserSettings80, emailStatus);
        boolOffsets["emailError"] = (short)offsetof(_rrgUserSettings80, emailError);
        boolOffsets["isAdmin"] = (short)offsetof(_rrgUserSettings80, isAdmin);
		//boolOffsets["emailSms"]    = (short)offsetof(_rrgUserSettings70, emailSms   ); // unused!

		Isolate* isolate = Isolate::GetCurrent();

		// Prepare constructor template
		v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, construct);
		tpl->SetClassName(v8::String::NewFromUtf8(isolate, "UserSettings", v8::String::kInternalizedString));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		constructor.Reset(isolate, tpl->GetFunction());
	}


/*
	USER
*/

//---------- CONSTRUCTION-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	v8::Persistent<v8::Function> User::constructor;

	void User::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		Handle<Object> self = args.This();
		User *user = new User();
		user->Wrap(self);

		self->SetHiddenValue(String::NewFromUtf8(isolate, "__user__", v8::String::kInternalizedString), v8::Null(isolate));

		args.GetReturnValue().Set(args.This());
	}

	void User::newInst(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		const unsigned argc = 1;
		Handle<Value> argv[argc] = { args[0] };

		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

		args.GetReturnValue().Set(instance);
	}

	Handle<Value> User::fromUser(_rrTCPuser* _user)
	{
		// no scope because this is called from other C++ code!
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance();

		ObjectWrap::Unwrap<User>(instance)->_user = _user;

		return instance;
	}

	User::User(void)
	{}

	User::~User(void)
	{}

	INIT_RR_WRAP(User,
		NODE_SET_PROTOTYPE_METHOD(tpl, "at", at);
		NODE_SET_PROTOTYPE_METHOD(tpl, "getNewUserPreset", getNewUserPreset);
		NODE_SET_PROTOTYPE_METHOD(tpl, "getAnonymous", getAnonymous);
		NODE_SET_PROTOTYPE_METHOD(tpl, "getOurUser", getOurUser);
		NODE_SET_PROTOTYPE_METHOD(tpl, "count", count),

		UserSettings::init();)

//---------- NODE METHODS -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	void User::at(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_1(at, Int32, ARGSDESCR(id))
		
		_rrTCPuser* _user = ObjectWrap::Unwrap<User>(args.This())->_user;
		args.GetReturnValue().Set(UserSettings::fromUserSettings(isolate, _user->at(args[0]->ToInt32()->Value())));
	}

	void User::getNewUserPreset(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		_rrTCPuser* _user = ObjectWrap::Unwrap<User>(args.This())->_user;
		args.GetReturnValue().Set(UserSettings::fromUserSettings(isolate, _user->getNewUserPreset()));
	}

	void User::getAnonymous(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		_rrTCPuser* _user = ObjectWrap::Unwrap<User>(args.This())->_user;
		args.GetReturnValue().Set(UserSettings::fromUserSettings(isolate, _user->getAnonymous()));
	}

	void User::getOurUser(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		_rrTCPuser* _user = ObjectWrap::Unwrap<User>(args.This())->_user;
		args.GetReturnValue().Set(UserSettings::fromUserSettings(isolate, _user->getOurUser()));
	}

	void User::count(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		int _count = ObjectWrap::Unwrap<User>(args.This())->_user->count();

		args.GetReturnValue().Set(Number::New(isolate, _count));
	}
