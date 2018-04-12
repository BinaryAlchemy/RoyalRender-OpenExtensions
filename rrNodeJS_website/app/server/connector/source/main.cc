#include <node.h>
#include <v8.h>

#include "tcp.h"
#include "commands.h"
#include "user.h"
#include "jobs.h"
#include "client.h"
#include "data.h"
#include "global.h"

using namespace v8;

void createTCP(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	TCP::newInst(args);
}

void createRRData(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	DataFiles::newInst(args);
}

void createUserSettings(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	UserSettings::newInst(args);
}

void createRRJob(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	rrJob::newInst(args);
}

void createRRGlobal(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	RRGlobal::newInst(args);
}

void Init(Handle<Object> target)
{
	rrJob::init();
	TCP::init();
	User::init();
	ClientList::init();
	DataFiles::init();
	RRGlobal::init();
	rrUint64::init();

    CMD::init(target);

	NODE_SET_METHOD(target, "_rrTCP", createTCP);
	NODE_SET_METHOD(target, "createTCP", createTCP);  // backward compatibility with early functions
    NODE_SET_METHOD(target, "createUserSettings", createUserSettings);
    NODE_SET_METHOD(target, "createRRJob", createRRJob);
	NODE_SET_METHOD(target, "datafiles", createRRData);
	NODE_SET_METHOD(target, "rrGlobal", createRRGlobal);
}

NODE_MODULE(jsRR, Init)
