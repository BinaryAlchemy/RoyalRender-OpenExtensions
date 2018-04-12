// tcp.h
#ifndef __NODE_TCP__
#define __NODE_TCP__

#include <node.h>
#include <node_object_wrap.h>
#include <v8.h>

#include "../../../shared_SDK/RR_DataTypes_jobs_SDK.h"
#include "../../../shared_SDK/RR_defines_SDK.h"
#include "../../../shared/RR_TCP.h"
#include "../../../shared/RR_TCP_joblist.h"
#include "../../../shared/RR_Code.h"


class TCP : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst  (const v8::FunctionCallbackInfo<v8::Value>& args);

	TCP(const char*);
	~TCP(void);

	// misc
	static void errorMessage (const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getGlobalInfo(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getMemUsage(const v8::FunctionCallbackInfo<v8::Value>& args);

	// accessors
	static void getUsers(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& args);
	static void getClients(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& args);
	static void getJobs(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& args);

	// connection
	static void setServer(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void setLogin(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getRRServer(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void connectionStats(const v8::FunctionCallbackInfo<v8::Value>& args);

	// jobs
	static void jobSetFilter(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void jobGetInfoBasic(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void jobGetInfoSend(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void jobSendCommand(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void jobModify(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void jobSubmitNew(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void lastUpdateJobs_ServerTime(const v8::FunctionCallbackInfo<v8::Value>&args);
	static void lastUpdateJobs_OurTime(const v8::FunctionCallbackInfo<v8::Value>&args);

	// users
	static void userGet(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void userNew(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void userMod(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void userWasPartialFail(const v8::FunctionCallbackInfo<v8::Value>& args);

	// clients
	static void listClients(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void clientSendCommand(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void clientGetList(const v8::FunctionCallbackInfo<v8::Value>& args);

	// initialization
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;

	bool user_p_wasPartialFail;
	_rrTCP rrTCP;
};

#endif
