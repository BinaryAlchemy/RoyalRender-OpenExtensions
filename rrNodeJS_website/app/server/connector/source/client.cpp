// client.cpp

#include "client.h"
#include "common.h"
#include "Accessors/client_access.hpp"

using namespace v8;
/*
Client ALL
*/

//---------- CONSTRUCTION -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
v8::Persistent<v8::Function> ClientStatus::constructor;

void ClientStatus::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	ClientStatus *clientStatus = new ClientStatus();
	clientStatus->Wrap(self);

	CLIENTSTATUS_ACCESS

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__clientstatus__", v8::String::kInternalizedString), v8::Null(isolate));

	args.GetReturnValue().Set(args.This());
}

void ClientStatus::newInst(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

Handle<Value> ClientStatus::fromClientStatus(rrC::_ClientStatus_ALL* _clientALL)
{
	// no scope because this is called from other C++ code!
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	ObjectWrap::Unwrap<ClientStatus>(instance)->_clientStatus = _clientALL;

	return instance;
}

void ClientStatus::jobThread(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	CHECKARGS_1(jobThread, Int32, ARGSDESCR(id))
	rrC::_ClientStatus_ALL* cl_status = ObjectWrap::Unwrap<ClientStatus>(args.This())->_clientStatus;
	args.GetReturnValue().Set(ClientStatusThread::fromClientStatusThread(&cl_status->jThread(args[0]->ToInt32()->Value())));
}

ClientStatus::ClientStatus(void)
{}

ClientStatus::~ClientStatus(void)
{}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(ClientStatus, NODE_SET_PROTOTYPE_METHOD(tpl, "jobThread", jobThread); , ClientStatusThread::init();)


/*
Client Status Thread
*/

//---------- CONSTRUCTION -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
v8::Persistent<v8::Function> ClientStatusThread::constructor;

void ClientStatusThread::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	ClientStatusThread *clientStatus = new ClientStatusThread();
	clientStatus->Wrap(self);

	CLIENTSTATUSTHREAD_ACCESS

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__clientstatusthread__", v8::String::kInternalizedString), v8::Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void ClientStatusThread::newInst(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

Handle<Value> ClientStatusThread::fromClientStatusThread(rrC::_ClientStatusThread* _clientThread)
{
	// no scope because this is called from other C++ code!
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	ObjectWrap::Unwrap<ClientStatusThread>(instance)->_clientStatusThread = _clientThread;

	return instance;
}

ClientStatusThread::ClientStatusThread(void)
{}

ClientStatusThread::~ClientStatusThread(void)
{}

//---------- NODE METHODS

void ClientStatusThread::clientStatusAsStringSingle(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);
	rrC::_ClientStatusThread* _clStatusThread = ObjectWrap::Unwrap<ClientStatusThread>(args.This())->_clientStatusThread;

	args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate,
		_clStatusThread->clientStatusAsStringSingle().toUtf8().data(),
		v8::String::kInternalizedString));
}

void ClientStatusThread::hasKSOLoaded(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);
	rrC::_ClientStatusThread* _clStatusThread = ObjectWrap::Unwrap<ClientStatusThread>(args.This())->_clientStatusThread;

	args.GetReturnValue().Set(_clStatusThread->hasKSOLoaded() ? v8::True(isolate) : v8::False(isolate));
}

void ClientStatusThread::isRendering(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);
	rrC::_ClientStatusThread* _clStatusThread = ObjectWrap::Unwrap<ClientStatusThread>(args.This())->_clientStatusThread;

	args.GetReturnValue().Set(_clStatusThread->isRendering() ? v8::True(isolate) : v8::False(isolate));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(ClientStatusThread,
	NODE_SET_PROTOTYPE_METHOD(tpl, "hasKSOLoaded", hasKSOLoaded);
	NODE_SET_PROTOTYPE_METHOD(tpl, "isRendering", isRendering);
	NODE_SET_PROTOTYPE_METHOD(tpl, "clientStatusAsStringSingle", clientStatusAsStringSingle);
    ,	)


/*
Client LIST
*/

//---------- CONSTRUCTION -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
v8::Persistent<v8::Function> ClientList::constructor;

void ClientList::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	ClientList *clientList = new ClientList();
	clientList->Wrap(self);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__clientlist__", v8::String::kInternalizedString), v8::Null(isolate));

	args.GetReturnValue().Set(args.This());
}

void ClientList::newInst(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

Handle<Value> ClientList::fromClientList(_rrTCPclientList* _clientList)
{
	// no scope because this is called from other C++ code!
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	ObjectWrap::Unwrap<ClientList>(instance)->_clientList = _clientList;

	return instance;
}

ClientList::ClientList(void)
{}

ClientList::~ClientList(void)
{}

//---------- NODE METHODS -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ClientList::clientStatus(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	CHECKARGS_1(clientStatus, Int32, ARGSDESCR(id))
	_rrTCPclientList* clientList = ObjectWrap::Unwrap<ClientList>(args.This())->_clientList;

	args.GetReturnValue().Set(String::NewFromUtf8(isolate,
		clientList->clientStatus(args[0]->ToInt32()->Value()).toUtf8().data(),
		v8::String::kInternalizedString));
}

void ClientList::count(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	int _count = ObjectWrap::Unwrap<ClientList>(args.This())->_clientList->count();

	args.GetReturnValue().Set(Number::New(isolate, _count));
}

void ClientList::at(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	CHECKARGS_1(at, Int32, ARGSDESCR(id))
	_rrTCPclientList* clientList = ObjectWrap::Unwrap<ClientList>(args.This())->_clientList;
	args.GetReturnValue().Set( ClientStatus::fromClientStatus(&clientList->at(args[0]->ToInt32()->Value())->status) );
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(ClientList,
	NODE_SET_PROTOTYPE_METHOD(tpl, "count", count);
	NODE_SET_PROTOTYPE_METHOD(tpl, "clientStatus", clientStatus);
    NODE_SET_PROTOTYPE_METHOD(tpl, "at", at);
    , ClientStatus::init(); )
