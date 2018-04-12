// tcp.cpp

#include "tcp.h"
#include "user.h"
#include "jobs.h"
#include "client.h"
#include "common.h"
#include <string>
#include <sstream>

#include <QString>

using namespace v8;


/*
	TCP
*/
//---------- CONSTRUCTION -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
v8::Persistent<v8::Function> TCP::constructor;

TCP::TCP(const char *machineName) : rrTCP(machineName) {}

TCP::~TCP(void) {}

void TCP::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	std::string machineName;
	if (args[0]->IsString()) {
		v8::String::Utf8Value arg0(args[0]->ToString());
		std::string arg0String(*arg0);
		machineName = arg0String;
	}

	TCP* obj = new TCP(machineName.c_str());
	Handle<Object> self = args.This();
	obj->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "jobs", v8::String::kInternalizedString), getJobs);
	self->SetAccessor(String::NewFromUtf8(isolate, "clients", v8::String::kInternalizedString), getClients);
	self->SetAccessor(String::NewFromUtf8(isolate, "users", v8::String::kInternalizedString), getUsers);

	args.GetReturnValue().Set(args.This());
}

void TCP::newInst(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TCP::errorMessage(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	const QString msg = ObjectWrap::Unwrap<TCP>(args.This())->rrTCP.errorMessage();
	if (msg.isEmpty()) {
		args.GetReturnValue().Set(Undefined(isolate));
		return;
	}

	v8::Local<v8::String> msgString = v8::String::NewFromUtf8(isolate, msg.toUtf8().data(), v8::String::kInternalizedString);
	args.GetReturnValue().Set(msgString);
}

void TCP::getGlobalInfo(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());
	tcp->rrTCP.infoGetGlobalInfo();

	const _infoGlobal &ig = tcp->rrTCP.infoGlobal;
	Local<Object> global = Object::New(isolate);

	// time
	global->Set(v8::String::NewFromUtf8(isolate, "time", v8::String::kInternalizedString), v8::String::NewFromUtf8(isolate, ig.SendServerTime.asString().toLatin1().data(), v8::String::kInternalizedString));

	// infoWOL
	{
		Local<Object> infoWOL = Object::New(isolate);
		infoWOL->Set(v8::String::NewFromUtf8(isolate, "WOlAble", v8::String::kInternalizedString), Int32::New(isolate, ig.infoWOL.WOlAble));
		infoWOL->Set(v8::String::NewFromUtf8(isolate, "totalClientNeed", v8::String::kInternalizedString), Number::New(isolate, ig.infoWOL.totalClientNeed));
		infoWOL->Set(v8::String::NewFromUtf8(isolate, "LastWOLExecute", v8::String::kInternalizedString), v8::String::NewFromUtf8(isolate, ig.infoWOL.LastWOLExecute.asString().toLatin1().data(), v8::String::kInternalizedString));
		global->Set(v8::String::NewFromUtf8(isolate, "infoWOL", v8::String::kInternalizedString), infoWOL);
	}

	// infoClientSegment, RenderSegmentsDone, RenderSegmentsTime
	{
		Local<Object> infoClientSegment = Object::New(isolate);
		infoClientSegment->Set(v8::String::NewFromUtf8(isolate, "RenderSegmentsDone", v8::String::kInternalizedString), Int32::New(isolate, ig.infoClientSegment.RenderSegmentsDone));
		infoClientSegment->Set(v8::String::NewFromUtf8(isolate, "RenderSegmentsTime", v8::String::kInternalizedString), Int32::New(isolate, ig.infoClientSegment.RenderSegmentsTime));
		global->Set(v8::String::NewFromUtf8(isolate, "infoClientSegment", v8::String::kInternalizedString), infoClientSegment);
	}

	// licUsage; licNames
	// TODO: the rest!!

	args.GetReturnValue().Set(global);
}

void TCP::getMemUsage(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());

	args.GetReturnValue().Set(v8::Int32::New(isolate, tcp->rrTCP.getMemUsage()));
}

//---------- ACCESSORS --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TCP::getJobs(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrTCPjobList* joblist = &ObjectWrap::Unwrap<TCP>(args.This())->rrTCP.jobs;
	args.GetReturnValue().Set( JobList::fromJobList(joblist) );
}

void TCP::getClients(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrTCPclientList* clientList = &ObjectWrap::Unwrap<TCP>(args.This())->rrTCP.clients;
	args.GetReturnValue().Set(ClientList::fromClientList(clientList));
}

void TCP::getUsers(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrTCPuser* user = &ObjectWrap::Unwrap<TCP>(args.This())->rrTCP.users;
	args.GetReturnValue().Set(User::fromUser(user));
}

//---------- CONNECTION -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TCP::setServer(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	CHECKARGS_2(setServer, String, Int32, ARGSDESCR(IP address, port))

	Local<Value> hserv = args[0];
	Local<Value> hport = args[1];

	std::string hostString(*v8::String::Utf8Value(hserv->ToString()));
	const int32_t port = hport->ToInt32()->Value();
	const bool success = ObjectWrap::Unwrap<TCP>(args.This())->rrTCP.setServer(hostString.c_str(), port);

	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void TCP::setLogin(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	CHECKARGS_2(setLogin, String, String, ARGSDESCR(user, password))
	Local<Value> huser = args[0];
	Local<Value> hpass = args[1];
	
	std::string userString(*v8::String::Utf8Value(huser->ToString()));
	std::string passString(*v8::String::Utf8Value(hpass->ToString()));
	ObjectWrap::Unwrap<TCP>(args.This())->rrTCP.setLogin(userString.c_str(), passString.c_str());
}

void TCP::getRRServer(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());
	QString server = tcp->rrTCP.getRRServer();

	args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, server.toUtf8().data(),
		v8::String::kNormalString, server.length()));
}

//---------- JOBS -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TCP::jobSetFilter(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	CHECKARGS_1(jobSetFilter, String, ARGSDESCR(user, [project, renderApp, contains, filter]))

	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());
	QString user(*v8::String::Utf8Value(args[0]->ToString()));

	switch (args.Length())
	{
		case 2: {
					CHECKARGS_2(jobSetFilter, String, String, ARGSDESCR(user, project))
					tcp->rrTCP.jobSetFilter(user, *v8::String::Utf8Value(args[1]->ToString()));  // project
					break;
				}
		case 3: {
					CHECKARGS_3(jobSetFilter, String, String, String, ARGSDESCR(user, project, renderApp))
					tcp->rrTCP.jobSetFilter(user,
						*v8::String::Utf8Value(args[1]->ToString()),  // project
						*v8::String::Utf8Value(args[2]->ToString())   // renderApp
						);
					break;
				}
		case 4: {
					CHECKARGS_4(jobSetFilter, String, String, String, String, ARGSDESCR(user, project, renderApp, contains))
					
					tcp->rrTCP.jobSetFilter(user,
						*v8::String::Utf8Value(args[1]->ToString()),  // project
						*v8::String::Utf8Value(args[2]->ToString()),  // renderApp
						*v8::String::Utf8Value(args[3]->ToString())   // contains
						);
					break;
				}
		case 5: {
					CHECKARGS_5(jobSetFilter, String, String, String, String, Int32, ARGSDESCR(user, project, renderApp, contains, filter))
					tcp->rrTCP.jobSetFilter(user,
						*v8::String::Utf8Value(args[1]->ToString()),  // project
						*v8::String::Utf8Value(args[2]->ToString()),  // renderApp
						*v8::String::Utf8Value(args[3]->ToString())   // contains
						);
					break;
				}
		default: {
					tcp->rrTCP.jobSetFilter(user);
				 }
	}
}

void TCP::jobGetInfoBasic(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());

	bool success;
	if (args.Length()) {
		CHECKARGS_1(getJobBasic, Object, ARGSDESCR(jobId))

		v8::Local<v8::Object> argob = args[0]->ToObject();

		if (!rrUint64::objectIs(argob)) {
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate,
				"argument is not a rrUint64!", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
			return;
		}

		uint64_t uintID = node::ObjectWrap::Unwrap<rrUint64>(argob)->toUint64();
		success = tcp->rrTCP.jobGetInfoBasic(uintID);
	}
	else {
		success = tcp->rrTCP.jobGetInfoBasic();
	}

	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void TCP::jobGetInfoSend(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	bool success;
	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());

	if (args.Length() > 0) {
		CHECKARGS_1(getJobBasic, Object, ARGSDESCR(jobId))

			v8::Local<v8::Object> argob = args[0]->ToObject();

		if (!rrUint64::objectIs(argob)) {
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate,
				"argument is not a rrUint64!", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
			return;
		}

		uint64_t uintID = node::ObjectWrap::Unwrap<rrUint64>(argob)->toUint64();
		success = tcp->rrTCP.jobGetInfoSend(uintID);
	}
	else {
		success = tcp->rrTCP.jobGetInfoSend();
	}

	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void TCP::jobSendCommand(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	CHECKARGS_3(jobSendCommand, Array, Int32, Int32, ARGSDESCR(clientArray, command ID, param))
	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());

	Local<Array> job_array = Local<Array>::Cast(args[0]);
	QListUInt64 ids;

	if (!rrUintArrayToQList(job_array, ids)) {
		v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate,
			"array contains object different from rrUint64",
			v8::String::kInternalizedString);

		isolate->ThrowException(Exception::TypeError(exceptionString));
		return;
	}

	const bool success = tcp->rrTCP.jobSendCommand(ids,
		(rrJ::_LogMessage)args[1]->ToUint32()->Value(),
		args[2]->ToUint32()->Value());

	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void TCP::jobModify(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	CHECKARGS_3( jobModify, Array, Object, Object, ARGSDESCR(job id, SettingsOnly(settings), SettingsOnly(changeFlags)) )

	if ( (SettingsOnly::objectIs(args[1]->ToObject())) && (SettingsOnly::objectIs(args[2]->ToObject())) )
	{
		TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());

		Local<Array> numArray = Local<Array>::Cast(args[0]);
		QListUInt64 qintList;
		arrayToQList(numArray, qintList);
		if (!rrUintArrayToQList(numArray, qintList)) {
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate,
				"array contains object different from rrUint64",
				v8::String::kInternalizedString);

			isolate->ThrowException(Exception::TypeError(exceptionString));
			return;
		}

		SettingsOnly *settings = ObjectWrap::Unwrap<SettingsOnly>(args[1]->ToObject());
		SettingsOnly *change = ObjectWrap::Unwrap<SettingsOnly>(args[2]->ToObject());

		bool success = tcp->rrTCP.jobModify(qintList, *settings->internalOb, *change->internalOb);
		args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
	}
	else
	{
		v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate,
			"jobModify expects a SettingsOnly (settings), and a SettingsOnly (changeFlags) as 2nd and 3d arguments",
			v8::String::kInternalizedString);

		isolate->ThrowException(Exception::TypeError(exceptionString));
		args.GetReturnValue().Set(Undefined(isolate));
	}
}

void TCP::jobSubmitNew(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	const v8::Local<v8::Object> job_obj = args[0]->ToObject();
	
	if ((args.Length() == 2) && (args[0]->IsObject()) && (args[1]->IsString()) && JobBasics::objectIs(job_obj))
	{
		TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());

		JobBasics *basics = ObjectWrap::Unwrap<JobBasics>(job_obj);

		bool success = tcp->rrTCP.jobSubmitNew(*(basics->internalOb), *v8::String::Utf8Value(args[1]->ToString()));
		args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
	}
	else
	{
		v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate,
			"jobSubmitNew expects a JobBasics (settings),"
			" and a string (overrideParameter) as arguments",
			v8::String::kInternalizedString);

		isolate->ThrowException(Exception::TypeError(exceptionString));
		args.GetReturnValue().Set(v8::False(isolate));
	}
}


//---------- USERS -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TCP::userGet(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());
	bool success = false;
	if (args.Length() > 0)
	{
		Local<Value> uname = args[0];
		if (!uname->IsString())
		{
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate, "userGet expects a string username as parameter", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
			args.GetReturnValue().Set(Undefined(isolate));
			return;
		}
		success = tcp->rrTCP.userGet(*v8::String::Utf8Value(args[0]->ToString()));
	}
	else
		success = tcp->rrTCP.userGet();

	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void TCP::userNew(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	Local<Value> arg0;

	if (args.Length() == 0 || !(arg0 = args[0])->IsObject())    //IGNORE IFCHECK
	{
		v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate, "userNew expects a UserSettings!", v8::String::kInternalizedString);
		isolate->ThrowException(Exception::TypeError(exceptionString));
		args.GetReturnValue().Set(v8::False(isolate));
		return;
	}
	else if (!UserSettings::objectIs(arg0->ToObject()))
	{
		v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate, "argument is not a UserSettings!", v8::String::kInternalizedString);
		isolate->ThrowException(Exception::TypeError(exceptionString));
		args.GetReturnValue().Set(v8::False(isolate));
		return;
	}

	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());
	UserSettings* settings = ObjectWrap::Unwrap<UserSettings>(arg0->ToObject());

	const bool success = tcp->rrTCP.userNew(*settings->user, &tcp->user_p_wasPartialFail);

	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void TCP::userMod(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	Local<Value> arg0;

	if (args.Length() < 1 || !(arg0 = args[0])->IsObject())    //IGNORE IFCHECK
	{
		v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate, "userModify expects a UserSettings!", v8::String::kInternalizedString);
		isolate->ThrowException(Exception::TypeError(exceptionString));
		args.GetReturnValue().Set(Undefined(isolate));
	}
	else if (!UserSettings::objectIs(arg0->ToObject()))
	{
		v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate, "argument is not a User!", v8::String::kInternalizedString);
		isolate->ThrowException(Exception::TypeError(exceptionString));
		args.GetReturnValue().Set(Undefined(isolate));
	}

	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());
	const bool success = tcp->rrTCP.userModify(*ObjectWrap::Unwrap<UserSettings>(arg0->ToObject())->user, &(tcp->user_p_wasPartialFail));

	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void TCP::userWasPartialFail(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());
	args.GetReturnValue().Set(tcp->user_p_wasPartialFail ? v8::True(isolate) : v8::False(isolate));
}

//---------- CLIENTS -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TCP::listClients(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());
	if (!tcp->rrTCP.clientGetList()) {
		args.GetReturnValue().Set(Array::New(0));
		return;
	}

	_rrTCPclientList &cltList = tcp->rrTCP.clients;
	const int nbClients = cltList.count();
	Local<Array> arr = Array::New(isolate, nbClients);
	for (int i = 0; i < nbClients; ++i)
	{
		Local<Object> obj = Object::New(isolate);
		obj->Set(v8::String::NewFromUtf8(isolate, "list_index", v8::String::kInternalizedString), Number::New(isolate, i));	// useful for to send commands!
        rrC::_Client* clientArray = cltList.getClientArray();
        obj->Set(v8::String::NewFromUtf8(isolate, "name", v8::String::kInternalizedString), v8::String::NewFromUtf8(isolate, QString(clientArray[i].status.name).toLatin1().data(), v8::String::kInternalizedString));
		obj->Set(v8::String::NewFromUtf8(isolate, "status", v8::String::kInternalizedString), v8::String::NewFromUtf8(isolate, cltList.clientStatus(i).toLatin1().data(), v8::String::kInternalizedString));
		arr->Set(i, obj);
	}

	args.GetReturnValue().Set(arr);
}

void TCP::clientSendCommand(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	CHECKARGS_2(clientSendCommand, Array, Int32, ARGSDESCR(clientArray, command ID, [param]))
	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());

	Local<Array> cl_array = Local<Array>::Cast(args[0]);
	QListInt ids;
	QString param;

	arrayToQList(cl_array, ids);

	if ( (args.Length() == 3) && args[2]->IsString() )
	{
		param = *v8::String::Utf8Value(args[2]->ToString());
	}
	else
	{
		param = QString();
	}

	const bool success = tcp->rrTCP.clientSendCommand(ids,
		(rrC::_ClientCommand)args[1]->ToInt32()->Value(),
		param);

	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void TCP::connectionStats(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());

	const QString& stats = tcp->rrTCP.connectionStats();
	args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, stats.toUtf8().data(),
		v8::String::kNormalString, stats.length()));
}

void TCP::lastUpdateJobs_ServerTime(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());
	_rrTime lastChanged = tcp->rrTCP.jobs.lastUpdateJobs_ServerTime();

	args.GetReturnValue().Set(v8::Date::New(isolate, lastChanged.toLocalTime() * 1000));
}

void TCP::lastUpdateJobs_OurTime(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());
	_rrTime lastChanged = tcp->rrTCP.jobs.lastUpdateJobs_OurTime();

	args.GetReturnValue().Set(v8::Date::New(isolate, lastChanged.toLocalTime() * 1000));
}

void TCP::clientGetList(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	TCP *tcp = ObjectWrap::Unwrap<TCP>(args.This());

	const bool success = tcp->rrTCP.clientGetList();
	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(TCP,
				NODE_SET_PROTOTYPE_METHOD(tpl, "errorMessage", errorMessage);
				NODE_SET_PROTOTYPE_METHOD(tpl, "getGlobalInfo", getGlobalInfo);
				NODE_SET_PROTOTYPE_METHOD(tpl, "getMemUsage", getMemUsage);
				NODE_SET_PROTOTYPE_METHOD(tpl, "setServer", setServer);
				NODE_SET_PROTOTYPE_METHOD(tpl, "setLogin", setLogin);
				NODE_SET_PROTOTYPE_METHOD(tpl, "getRRServer", getRRServer);
				NODE_SET_PROTOTYPE_METHOD(tpl, "jobSetFilter", jobSetFilter);
				NODE_SET_PROTOTYPE_METHOD(tpl, "jobGetInfoBasic", jobGetInfoBasic);
				NODE_SET_PROTOTYPE_METHOD(tpl, "jobGetInfoSend", jobGetInfoSend);
				NODE_SET_PROTOTYPE_METHOD(tpl, "jobSendCommand", jobSendCommand);
				NODE_SET_PROTOTYPE_METHOD(tpl, "jobModify", jobModify);
				NODE_SET_PROTOTYPE_METHOD(tpl, "jobSubmitNew", jobSubmitNew);
				NODE_SET_PROTOTYPE_METHOD(tpl, "userGet", userGet);
				NODE_SET_PROTOTYPE_METHOD(tpl, "userNew", userNew);
				NODE_SET_PROTOTYPE_METHOD(tpl, "userModify", userMod);
				NODE_SET_PROTOTYPE_METHOD(tpl, "listClients", listClients);
				NODE_SET_PROTOTYPE_METHOD(tpl, "clientSendCommand", clientSendCommand);
				NODE_SET_PROTOTYPE_METHOD(tpl, "connectionStats", connectionStats);
				NODE_SET_PROTOTYPE_METHOD(tpl, "lastUpdateJobs_ServerTime", lastUpdateJobs_ServerTime);
				NODE_SET_PROTOTYPE_METHOD(tpl, "lastUpdateJobs_OurTime", lastUpdateJobs_OurTime);
                NODE_SET_PROTOTYPE_METHOD(tpl, "clientGetList", clientGetList);
                ,	)
