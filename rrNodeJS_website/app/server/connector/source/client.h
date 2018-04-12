// client.h
#ifndef __NODE_CLIENT__
#define __NODE_CLIENT__

#include <node.h>
#include <node_object_wrap.h>
#include <v8.h>

#include "../../../shared_SDK/RR_defines_SDK.h"
#include "../../../shared/RR_TCP.h"

#include "Accessors/client_access.h"


class ClientStatus : public node::ObjectWrap
{
public:
	// Creators!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromClientStatus(rrC::_ClientStatus_ALL *_clientStatus);

	ClientStatus(void);
	virtual ~ClientStatus(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	CLIENTSTATUS_ACCESSH

	// node methods
	static void jobThread(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

	rrC::_ClientStatus_ALL* _clientStatus = NULL;  // stays NULL, unless initialized with fromClientStatus method or manually set;

private:
	static v8::Persistent<v8::Function> constructor;
};


class ClientStatusThread : public node::ObjectWrap
{
public:
	// Creators!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromClientStatusThread(rrC::_ClientStatusThread *_clientStatus);

	ClientStatusThread(void);
	virtual ~ClientStatusThread(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	CLIENTSTATUSTHREAD_ACCESSH

	// node methods
	static void hasKSOLoaded(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void isRendering(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void clientStatusAsStringSingle(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

	rrC::_ClientStatusThread* _clientStatusThread = NULL;  // stays NULL, unless initialized with fromClientStatus method or manually set;

private:
	static v8::Persistent<v8::Function> constructor;
};


class ClientList : public node::ObjectWrap
{
public:
	// Creators!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromClientList(_rrTCPclientList *_clientList);

	ClientList(void);
	virtual ~ClientList(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// node methods
	static void count(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void clientStatus(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void at(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

	_rrTCPclientList *_clientList = NULL;  // stays NULL, unless initialized with fromClientList method or manually set;

private:
	static v8::Persistent<v8::Function> constructor;
};


#endif
