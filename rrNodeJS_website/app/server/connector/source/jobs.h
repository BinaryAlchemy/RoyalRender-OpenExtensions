// jobs.h
#ifndef __NODE_JOB__
#define __NODE_JOB__

#include <node.h>
#include <v8.h>
#include <node_object_wrap.h>

#include "../../../shared_SDK/RR_defines_SDK.h"
#include "../../../shared/RR_TCP_Joblist.h"

#include "Accessors/job_access.h"


using namespace v8;


class JobMinInfo: public node::ObjectWrap
{
public:
	// Creators!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static Handle<Value> fromJobMinInfo(rrJ::_JobMinInfo *job);

	JobMinInfo(void);
	virtual ~JobMinInfo(void);
	void setJob(const rrJ::_JobMinInfo &job);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// Accessors
	JOBMININFO_ACCESSH

	static void getMask(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info);
	static void setMask(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info);

	// ---- init
	static void init(void);

	rrJ::_JobMinInfo* internalOb = NULL;  // stays NULL, unless initialized with fromJobMinInfo method or manually set;

private:
	static v8::Persistent<v8::Function> constructor;		
};


class JobList : public node::ObjectWrap
{
public:
	// Creators!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromJobList(_rrTCPjobList *job);

	JobList(void);
	virtual ~JobList(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	//node methods
	static void getJobBasic(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getJobDataType(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getJobUpdatedTime(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getJobMinInfo(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getJobMinInfo_filterQueue(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getJobMinInfo_queue(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getJobSend(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getMaxJobs(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getMaxJobsFiltered(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void sort(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

	_rrTCPjobList *_jobList = NULL;  // stays NULL, unless initialized with fromJobList method or manually set;

private:
	static v8::Persistent<v8::Function> constructor;
};


class SettingsOnly : public node::ObjectWrap
{
public:
	// Creators!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);

	SettingsOnly(void);
	virtual ~SettingsOnly(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// Accessors
	SETTINGSONLY_ACCESSH(SettingsOnly)
	SETTINGSSCENE_ACCESSH(SettingsOnly)

	// ---- init
	static void init(void);

	rrJ::_SettingsOnly* internalOb;

private:
	static v8::Persistent<v8::Function> constructor;
};


class JobBasics : public node::ObjectWrap
{
public:
	// Creators!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static Handle<Value> fromJobBasics(rrJ::_JobBasics*);

	JobBasics(void);
	virtual ~JobBasics(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// Accessors
	JOBBASIC_ACCESSH(JobBasics)
	SETTINGSSCENE_ACCESSH(JobBasics)

	// ---- init
	static void init(void);

	rrJ::_JobBasics* internalOb = NULL; // stays NULL, unless initialized with fromJobBasic or NewInst(), or manually set;

private:
	static v8::Persistent<v8::Function> constructor;
	bool delInternalPointer = true;
};


class JobSend : public node::ObjectWrap
{
public:
	// Creators!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static Handle<Value> fromJobSend(rrJ::_JobSend*);

	JobSend(void);
	virtual ~JobSend(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// Accessors
	JOBBASIC_ACCESSH(JobSend)
	SETTINGSONLY_ACCESSH(JobSend)
	SETTINGSSCENE_ACCESSH(JobSend)
	JOBSEND_ACCESSH

	// ---- init
	static void init(void);

	rrJ::_JobSend* internalOb = NULL; // stays NULL, unless initialized with fromJobSend, or manually set;

private:
	static v8::Persistent<v8::Function> constructor;
};


class rrJob : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);

	rrJob(void);
	virtual ~rrJob(void);

	// node methods
	static void getClass_JobBasics(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getClass_SettingsOnly(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
};

#endif
