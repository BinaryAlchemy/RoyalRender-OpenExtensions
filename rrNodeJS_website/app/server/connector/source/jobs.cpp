// jobs.cpp


#include <string>
#include <map>
#include <stddef.h>

#include "../../../shared_SDK/RR_DataTypes_jobs_comm_SDK.h"

#include "jobs.h"
#include "common.h"
#include "Accessors/job_access.hpp"
#include "enums.h"

/****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
				JOB MIN INFO
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************/

typedef std::map<std::string, short> maskMap;		// mapping the array index of a variable if _rrgUserSettings was an bool array!
static maskMap masks;

//---------- CONSTRUCTION -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	v8::Persistent<v8::Function> JobMinInfo::constructor;

	void JobMinInfo::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		Handle<Object> self = args.This();
		JobMinInfo *job = new JobMinInfo();
		job->Wrap(self);

		for (maskMap::const_iterator beg = masks.begin(), end = masks.end(); beg != end; ++beg)
			self->SetAccessor(String::NewFromUtf8(isolate, beg->first.c_str(), v8::String::kInternalizedString), getMask, setMask);

		JOBMININFO_ACCESS

		self->SetHiddenValue(String::NewFromUtf8(isolate, "__jobmininfo__", v8::String::kInternalizedString), v8::Null(isolate));
		args.GetReturnValue().Set(args.This());
	}

	Handle<Value> JobMinInfo::fromJobMinInfo(rrJ::_JobMinInfo* job)
	{
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance();

		ObjectWrap::Unwrap<JobMinInfo>(instance)->internalOb = job;
		return instance;
	}

	JobMinInfo::JobMinInfo(void)
	{}

	JobMinInfo::~JobMinInfo(void)
	{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	bool JobMinInfo::objectIs(v8::Handle<v8::Object> obj)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
			"__jobmininfo__",
			String::kInternalizedString)
			);

		return !val->IsUndefined();
	}

	void JobMinInfo::getMask(v8::Local<v8::String> name, const PropertyCallbackInfo<Value> &info)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		const JobMinInfo *jobInfo = ObjectWrap::Unwrap<JobMinInfo>(info.Holder());

		const short mask = masks.find(*v8::String::Utf8Value(name->ToString()))->second;
		const bool success = jobInfo->internalOb->m_filterMask & mask;

		info.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
	}

	void JobMinInfo::setMask(v8::Local<v8::String> name, v8::Local<v8::Value> value, const PropertyCallbackInfo<void> &info)
	{
		quint8 &filterMask = ObjectWrap::Unwrap<JobMinInfo>(info.Holder())->internalOb->m_filterMask;
		const bool maskNewVal = value->ToBoolean()->Value();

		const short mask = masks.find(*v8::String::Utf8Value(name->ToString()))->second;
		const bool curMaskvalue = filterMask & mask;

		if (curMaskvalue)
		{
			if (!maskNewVal)
				filterMask ^= mask;
		}
		else if (maskNewVal)
			filterMask |= mask;
	}

//---------- NODE METHODS (outside the JobMinInfo class, as they are static and shared with other classes)

	template <typename T>
	static void IDstr(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

        const QString& idStr = node::ObjectWrap::Unwrap<T>(args.This())->internalOb->IDstr();
		args.GetReturnValue().Set(String::NewFromUtf8(isolate,
			idStr.toUtf8().data(),
			v8::String::kInternalizedString));
	}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	INIT_RR_WRAP(JobMinInfo,
		NODE_SET_PROTOTYPE_METHOD(tpl, "IDstr", IDstr<JobMinInfo>),
		masks["isIdle"] = _JobMinInfo_isIdle;
		masks["isRendering"] = _JobMinInfo_isRendering;
		masks["isDisabled"] = _JobMinInfo_isDisabled;
		masks["isWaitFor"] = _JobMinInfo_isWaitFor;
		masks["isFinished"] = _JobMinInfo_isFinished;)


/****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
				RENDER APP BASIC
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************/

//---------- CONSTRUCTION -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	v8::Persistent<v8::Function> RenderAppBasic::constructor;

	void RenderAppBasic::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		Handle<Object> self = args.This();
		RenderAppBasic *_renderApp = new RenderAppBasic();
		_renderApp->Wrap(self);

		RENDERAPPBASIC_ACCESS

		self->SetHiddenValue(String::NewFromUtf8(isolate, "__renderapp__", v8::String::kInternalizedString), v8::Null(isolate));

		args.GetReturnValue().Set(args.This());
	}

	void RenderAppBasic::newInst(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		const unsigned argc = 1;
		Handle<Value> argv[argc] = { args[0] };

		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

		args.GetReturnValue().Set(instance);
	}

	Handle<Value> RenderAppBasic::fromRenderApp(rrRA::_RenderAppBasic* _renderApp)
	{
		// no scope because this is called from other C++ code!
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance();

		ObjectWrap::Unwrap<RenderAppBasic>(instance)->renderApp = _renderApp;

		return instance;
	}

	RenderAppBasic::RenderAppBasic(void)
	{}

	RenderAppBasic::~RenderAppBasic(void)
	{}

	//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	bool RenderAppBasic::objectIs(v8::Handle<v8::Object> obj)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
			"__renderapp__",
			String::kInternalizedString)
			);

		return !val->IsUndefined();
	}

	void RenderAppBasic::versionMinorDisplay(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		QByteArray vMinor = ObjectWrap::Unwrap<RenderAppBasic>(args.This())->renderApp->getVersionMinorDisplay().toUtf8();
		args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, vMinor.data(), v8::String::kInternalizedString));
	}

	void RenderAppBasic::setVersionMinor(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_1(setVersionMinor, String, ARGSDESCR(version))

		rrRA::_RenderAppBasic* _renderApp = ObjectWrap::Unwrap<RenderAppBasic>(args.This())->renderApp;
		_renderApp->setVersionMinor( QString::fromUtf8(*v8::String::Utf8Value(args[0]->ToString())) );
	}

	void RenderAppBasic::setVersionBoth(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_1(setVersionBoth, String, ARGSDESCR(major.minor))

		rrRA::_RenderAppBasic* _renderApp = ObjectWrap::Unwrap<RenderAppBasic>(args.This())->renderApp;
		_renderApp->setVersionBoth(QString::fromUtf8(*v8::String::Utf8Value(args[0]->ToString())));
	}

	void RenderAppBasic::clearBasic(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		ObjectWrap::Unwrap<RenderAppBasic>(args.This())->renderApp->clearBasic();
	}

	//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	INIT_RR_WRAP(RenderAppBasic,
		NODE_SET_PROTOTYPE_METHOD(tpl, "versionMinorDisplay", versionMinorDisplay);
		NODE_SET_PROTOTYPE_METHOD(tpl, "setVersionMinor", setVersionMinor);
		NODE_SET_PROTOTYPE_METHOD(tpl, "setVersionBoth", setVersionBoth);
        NODE_SET_PROTOTYPE_METHOD(tpl, "clearBasic", clearBasic);
        , )


/****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
				JOB LIST
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************/

	//---------- CONSTRUCTION -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	v8::Persistent<v8::Function> JobList::constructor;

	void JobList::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		Handle<Object> self = args.This();
		JobList *jobList = new JobList();
		jobList->Wrap(self);

		self->SetHiddenValue(String::NewFromUtf8(isolate, "__joblist__", v8::String::kInternalizedString), v8::Null(isolate));

		args.GetReturnValue().Set(args.This());
	}

	void JobList::newInst(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		const unsigned argc = 1;
		Handle<Value> argv[argc] = { args[0] };

		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

		args.GetReturnValue().Set(instance);
	}

	Handle<Value> JobList::fromJobList(_rrTCPjobList* _jobList)
	{
		// no scope because this is called from other C++ code!
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance();

		ObjectWrap::Unwrap<JobList>(instance)->_jobList = _jobList;

		return instance;
	}

	JobList::JobList(void)
	{}

	JobList::~JobList(void)
	{}

	//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	bool JobList::objectIs(v8::Handle<v8::Object> obj)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
			"__joblist__",
			String::kInternalizedString)
			);

		return !val->IsUndefined();
	}

	// Node Methods
	void JobList::getMaxJobs(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		v8::Isolate* isolate = v8::Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		_rrTCPjobList* settings = ObjectWrap::Unwrap<JobList>(args.This())->_jobList;
		args.GetReturnValue().Set(v8::Number::New(isolate, settings->getMaxJobs()));
	}

	void JobList::getMaxJobsFiltered(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		v8::Isolate* isolate = v8::Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		_rrTCPjobList* jobList = ObjectWrap::Unwrap<JobList>(args.This())->_jobList;
		args.GetReturnValue().Set(v8::Number::New(isolate, jobList->getMaxJobsFiltered()));
	}

	void JobList::getJobDataType(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_1(getJobBasic, Object, ARGSDESCR(jobId))

		v8::Local<v8::Object> argob = args[0]->ToObject();

		if (!rrUint64::objectIs(argob)) {
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate,
				"argument is not a rrUint64!", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
			return;
		}

		uint64_t uintID = node::ObjectWrap::Unwrap<rrUint64>(argob)->toUint64();

		_rrTCPjobList* jobList = ObjectWrap::Unwrap<JobList>(args.This())->_jobList;
		args.GetReturnValue().Set( Uint32::New(isolate, jobList->getJobDataType(uintID)) );
	}

	void JobList::sort(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		v8::Isolate* isolate = v8::Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_1(sort, Int32, ARGSDESCR(sortIDs));

		_rrTCPjobList* jobList = ObjectWrap::Unwrap<JobList>(args.This())->_jobList;

		_rrTCPjobList::_sortIDs sortId = static_cast<_rrTCPjobList::_sortIDs>(args[0]->ToInt32()->Value());
        jobList->sort(sortId);
	}

	void JobList::getJobMinInfo(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_1(getJobBasic, Object, ARGSDESCR(jobId))

		v8::Local<v8::Object> argob = args[0]->ToObject();

		if (!rrUint64::objectIs(argob)) {
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate,
				"argument is not a rrUint64!", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
			return;
		}

		uint64_t uintID = node::ObjectWrap::Unwrap<rrUint64>(argob)->toUint64();

		_rrTCPjobList* jobList = ObjectWrap::Unwrap<JobList>(args.This())->_jobList;
		rrJ::_JobMinInfo* jobInfo = jobList->getJobMinInfo(uintID);

		if (jobInfo) {
			args.GetReturnValue().Set(JobMinInfo::fromJobMinInfo(jobInfo));
		}
	}

	void JobList::getJobMinInfo_queue(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_1(getJobMinInfo_queue, Int32, ARGSDESCR(queueID))

		_rrTCPjobList* jobList = ObjectWrap::Unwrap<JobList>(args.This())->_jobList;
		rrJ::_JobMinInfo* jobinfo = jobList->getJobMinInfo_queue(args[0]->ToInt32()->Value());
		if (jobinfo) {
			args.GetReturnValue().Set(JobMinInfo::fromJobMinInfo(jobinfo));
		}
	}

	void JobList::getJobMinInfo_filterQueue(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_1(getJobMinInfo_filterQueue, Int32, ARGSDESCR(queueID))

		_rrTCPjobList* jobList = ObjectWrap::Unwrap<JobList>(args.This())->_jobList;
		rrJ::_JobMinInfo* jobinfo = jobList->getJobMinInfo_filterQueue(args[0]->ToInt32()->Value());
		if (jobinfo) {
			args.GetReturnValue().Set(JobMinInfo::fromJobMinInfo(jobinfo));
		}
	}

	void JobList::getJobBasic(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_1(getJobBasic, Object, ARGSDESCR(jobId))

		v8::Local<v8::Object> argob = args[0]->ToObject();

		if (!rrUint64::objectIs(argob)) {
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate,
				"argument is not a rrUint64!", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
			return;
		}

		uint64_t uintID = node::ObjectWrap::Unwrap<rrUint64>(argob)->toUint64();

		_rrTCPjobList* jobList = ObjectWrap::Unwrap<JobList>(args.This())->_jobList;
		rrJ::_JobBasics* basics = jobList->getJobBasic(uintID);
		if (basics) {
			args.GetReturnValue().Set(JobBasics::fromJobBasics(basics));
		}
	}

	void JobList::getJobUpdatedTime(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_1(getJobBasic, Object, ARGSDESCR(jobId))

		v8::Local<v8::Object> argob = args[0]->ToObject();

		if (!rrUint64::objectIs(argob)) {
			v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate,
				"argument is not a rrUint64!", v8::String::kInternalizedString);
			isolate->ThrowException(Exception::TypeError(exceptionString));
			return;
		}

		uint64_t uintID = node::ObjectWrap::Unwrap<rrUint64>(argob)->toUint64();

		_rrTCPjobList* jobList = ObjectWrap::Unwrap<JobList>(args.This())->_jobList;
		Local<Value> upTime = Date::New(isolate, jobList->getJobUpdatedTime(uintID).toLocalTime() * 1000);

		args.GetReturnValue().Set(upTime);
	}

	void JobList::getJobSend(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

        CHECKARGS_1(getJobSend, Object, ARGSDESCR(jobId))

            v8::Local<v8::Object> argob = args[0]->ToObject();

        if (!rrUint64::objectIs(argob)) {
            v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate,
                "argument is not a rrUint64!", v8::String::kInternalizedString);
            isolate->ThrowException(Exception::TypeError(exceptionString));
            return;
        }

        uint64_t uintID = node::ObjectWrap::Unwrap<rrUint64>(argob)->toUint64();
        _rrTCPjobList* jobList = ObjectWrap::Unwrap<JobList>(args.This())->_jobList;

        rrJ::_JobSend* jobsend = jobList->getJobSend(uintID);
        if (jobsend) {
            args.GetReturnValue().Set(JobSend::fromJobSend(jobsend));
        }
        else {
            rrJ::_JobBasics* basic = jobList->getJobBasic(args[0]->ToNumber()->Value());
            if (basic) {
                args.GetReturnValue().Set(JobBasics::fromJobBasics(basic));
            }
        }
	}

	//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	INIT_RR_WRAP(JobList,
		NODE_SET_PROTOTYPE_METHOD(tpl, "getMaxJobs", getMaxJobs);
		NODE_SET_PROTOTYPE_METHOD(tpl, "getJobDataType", getJobDataType);
		NODE_SET_PROTOTYPE_METHOD(tpl, "getJobMinInfo", getJobMinInfo);
		NODE_SET_PROTOTYPE_METHOD(tpl, "getJobBasic", getJobBasic);
		NODE_SET_PROTOTYPE_METHOD(tpl, "getJobSend", getJobSend);
		NODE_SET_PROTOTYPE_METHOD(tpl, "getJobUpdatedTime", getJobUpdatedTime);
		NODE_SET_PROTOTYPE_METHOD(tpl, "getJobMinInfo_queue", getJobMinInfo_queue);
		NODE_SET_PROTOTYPE_METHOD(tpl, "getMaxJobsFiltered", getMaxJobsFiltered);
        NODE_SET_PROTOTYPE_METHOD(tpl, "getJobMinInfo_filterQueue", getJobMinInfo_filterQueue);
        ,	)


/****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
				SETTINGS ONLY
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************/

//---------- CONSTRUCTION -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	v8::Persistent<v8::Function> SettingsOnly::constructor;

	void SettingsOnly::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		Handle<Object> self = args.This();
		SettingsOnly *setOnly = new SettingsOnly();
		setOnly->Wrap(self);

		SETTINGSONLY_ACCESS
		SETTINGSSCENE_ACCESS

		self->SetHiddenValue(String::NewFromUtf8(isolate, "__setonly__", v8::String::kInternalizedString), v8::Null(isolate));

		args.GetReturnValue().Set(args.This());
	}

	void SettingsOnly::newInst(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		const unsigned argc = 1;
		Handle<Value> argv[argc] = { args[0] };

		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

		args.GetReturnValue().Set(instance);
	}

	SettingsOnly::SettingsOnly(void)
	{
		internalOb = new rrJ::_SettingsOnly();
	}

	SettingsOnly::~SettingsOnly(void)
	{
		delete internalOb;
	}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	bool SettingsOnly::objectIs(v8::Handle<v8::Object> obj)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
			"__setonly__",
			String::kInternalizedString)
			);

		return !val->IsUndefined();
	}

//---------- NODE METHODS (outside the SettingsOnly class, as they are static and shared with other classes)---------------------------------------------------------------------------------------------------------------------------------------
	static void rrOption(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_1(rrOption, Int32, ARGSDESCR(id));

		rrJ::_SettingsOnly* settings = node::ObjectWrap::Unwrap<SettingsOnly>(args.This())->internalOb;
		args.GetReturnValue().Set(settings->rrOptions_Get(args[0]->ToInt32()->Value()) ? v8::True(isolate) : v8::False(isolate));
	}

	static void rrOption_Set(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_2(rrOption_Set, Int32, Boolean, ARGSDESCR(id, newValue))

		rrJ::_SettingsOnly* settings = node::ObjectWrap::Unwrap<SettingsOnly>(args.This())->internalOb;
		settings->rrOptions_Set(args[0]->ToInt32()->Value(), args[1]->ToBoolean()->Value());
	}

	static void rrParam(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_1(rrParam, Int32, ARGSDESCR(id))

		rrJ::_SettingsOnly* settings = node::ObjectWrap::Unwrap<SettingsOnly>(args.This())->internalOb;
		args.GetReturnValue().Set(settings->rrParam_Get(args[0]->ToInt32()->Value()));
	}

	static void rrParam_Set(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_2(rrParam_Set, Int32, Int32, ARGSDESCR(id, newValue))
		rrJ::_SettingsOnly* settings = node::ObjectWrap::Unwrap<SettingsOnly>(args.This())->internalOb;
		settings->rrParam_Set(args[0]->ToInt32()->Value(), args[1]->ToInt32()->Value());
	}

	static void custom_Str(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_1(custom_Str, String, ARGSDESCR(name))

		rrJ::_SettingsOnly* settings = node::ObjectWrap::Unwrap<SettingsOnly>(args.This())->internalOb;

		args.GetReturnValue().Set(String::NewFromUtf8(isolate,
			settings->custom_Str(QString::fromUtf8(*v8::String::Utf8Value(args[0]->ToString()))).toUtf8().data(),
			v8::String::kInternalizedString));
	}

	static void customSet_Str(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_2(customSet_Str, String, String, ARGSDESCR(name, value))

		rrJ::_SettingsOnly* settings = node::ObjectWrap::Unwrap<SettingsOnly>(args.This())->internalOb;

		settings->customSet_Str(
			QString::fromUtf8(*v8::String::Utf8Value(args[0]->ToString())),
			QString::fromUtf8(*v8::String::Utf8Value(args[1]->ToString()))
			);
	}

	static void custom_UserInfo(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		rrJ::_SettingsOnly* settings = node::ObjectWrap::Unwrap<SettingsOnly>(args.This())->internalOb;
		args.GetReturnValue().Set(String::NewFromUtf8(isolate,
			settings->custom_UserInfo().toUtf8().data(),
			v8::String::kInternalizedString));
	}

	static void customSet_UserInfo(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_1(customSet_UserInfo, String, ARGSDESCR(name))

		rrJ::_SettingsOnly* settings = node::ObjectWrap::Unwrap<SettingsOnly>(args.This())->internalOb;
		settings->customSet_UserInfo(
			QString::fromUtf8(*v8::String::Utf8Value(args[0]->ToString()))
			);
	}

	static void customGet_maxIDs(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		rrJ::_SettingsOnly* settings = node::ObjectWrap::Unwrap<SettingsOnly>(args.This())->internalOb;
		args.GetReturnValue().Set(Number::New(isolate, settings->custom_maxIDs()));
	}

	static void custom_StrByID(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_1(customSet_StrByID, Int32, ARGSDESCR(index))
		rrJ::_SettingsOnly* settings = node::ObjectWrap::Unwrap<SettingsOnly>(args.This())->internalOb;
		args.GetReturnValue().Set(String::NewFromUtf8(isolate,
			settings->custom_StrByID(args[0]->ToInt32()->Value()).toUtf8().data(),
			v8::String::kInternalizedString));
	}

	static void customSet_StrByID(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_2(customSet_StrByID, Int32, String, ARGSDESCR(index, value))

		rrJ::_SettingsOnly* settings = node::ObjectWrap::Unwrap<SettingsOnly>(args.This())->internalOb;
		settings->customSet_StrByID(args[0]->ToInt32()->Value(),
			QString::fromUtf8(*v8::String::Utf8Value(args[1]->ToString())));
	}

	static void custom_NameByID(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_2(custom_NameByID, Int32, Int32, ARGSDESCR(index, value))
		rrJ::_SettingsOnly* settings = node::ObjectWrap::Unwrap<SettingsOnly>(args.This())->internalOb;

		args.GetReturnValue().Set(String::NewFromUtf8(isolate,
			settings->custom_NameByID(args[0]->ToInt32()->Value()).toUtf8().data(),
			v8::String::kInternalizedString));
	}

	static void custom_AllAsString(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		rrJ::_SettingsOnly* settings = node::ObjectWrap::Unwrap<SettingsOnly>(args.This())->internalOb;

		args.GetReturnValue().Set(String::NewFromUtf8(isolate,
			settings->custom_AllAsString().toUtf8().data(),
			v8::String::kInternalizedString));
	}

	static void custom_ClearAll(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		rrJ::_SettingsOnly* settings = node::ObjectWrap::Unwrap<SettingsOnly>(args.This())->internalOb;
		settings->custom_ClearAll();
	}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	INIT_RR_WRAP(SettingsOnly,
		NODE_SET_PROTOTYPE_METHOD(tpl, "rrOption", rrOption);
		NODE_SET_PROTOTYPE_METHOD(tpl, "rrOption_Set", rrOption_Set);
		NODE_SET_PROTOTYPE_METHOD(tpl, "rrParam", rrParam);
		NODE_SET_PROTOTYPE_METHOD(tpl, "rrParam_Set", rrParam_Set);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_Str", custom_Str);
		NODE_SET_PROTOTYPE_METHOD(tpl, "customSet_Str", customSet_Str);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_UserInfo", custom_UserInfo);
		NODE_SET_PROTOTYPE_METHOD(tpl, "customSet_UserInfo", customSet_UserInfo);
		NODE_SET_PROTOTYPE_METHOD(tpl, "customGet_maxIDs", customGet_maxIDs);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_StrByID", custom_StrByID);
		NODE_SET_PROTOTYPE_METHOD(tpl, "customSet_StrByID", customSet_StrByID);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_NameByID", custom_NameByID);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_AllAsString", custom_AllAsString);
        NODE_SET_PROTOTYPE_METHOD(tpl, "custom_ClearAll", custom_ClearAll);
        , )


/****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
				JOB BASIC
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************/

//---------- CONSTRUCTION -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	v8::Persistent<v8::Function> JobBasics::constructor;

	void JobBasics::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		Handle<Object> self = args.This();
		JobBasics *jobbasic = new JobBasics();
		jobbasic->Wrap(self);

		JOBBASIC_ACCESS
		SETTINGSSCENE_ACCESS
		
		self->SetHiddenValue(String::NewFromUtf8(isolate, "__jobbasic__", v8::String::kInternalizedString), v8::Null(isolate));
		args.GetReturnValue().Set(args.This());
	}

	void JobBasics::newInst(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		const unsigned argc = 1;
		Handle<Value> argv[argc] = { args[0] };

		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

		JobBasics* jobBasic = ObjectWrap::Unwrap<JobBasics>(instance);
		jobBasic->internalOb = new rrJ::_JobBasics();

		args.GetReturnValue().Set(instance);
	}

	Handle<Value> JobBasics::fromJobBasics(rrJ::_JobBasics* _basic)
	{
		// no scope because this is called from other C++ code!
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance();

		JobBasics* jobBasic = ObjectWrap::Unwrap<JobBasics>(instance);
		jobBasic->internalOb = _basic;
		jobBasic->delInternalPointer = false;  // internal jobbasics belongs to another object

		return instance;
	}

	JobBasics::JobBasics(void)
	{}

	JobBasics::~JobBasics(void)
	{
		if (delInternalPointer)
		{
			delete internalOb;
		}
	}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	bool JobBasics::objectIs(v8::Handle<v8::Object> obj)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
			"__jobbasic__",
			String::kInternalizedString)
			);

		return !val->IsUndefined();
	}

//---------- NODE METHODS (outside the JobBasics class, as they are static and shared with other classes)---------------------------------------------------------------------------------------------------------------------------------------
	static void waitForPreID(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_1(waitForPreID, Int32, ARGSDESCR(index))

		rrJ::_JobBasics* jobbasic = node::ObjectWrap::Unwrap<JobBasics>(args.This())->internalOb;
		args.GetReturnValue().Set(Number::New(isolate, jobbasic->getWaitForPreID(args[0]->ToInt32()->Value())));
	}

	static void waitForPreID_set(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_2(waitForPreID_set, Int32, Number, ARGSDESCR(index, value))

		rrJ::_JobBasics* jobbasic = node::ObjectWrap::Unwrap<JobBasics>(args.This())->internalOb;
		jobbasic->setWaitForPreID(args[0]->ToInt32()->Value(), args[1]->ToNumber()->Value());
	}

	static void channelFileName(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_1(channelFileName, Int32, ARGSDESCR(index))

		rrJ::_JobBasics* jobbasic = node::ObjectWrap::Unwrap<JobBasics>(args.This())->internalOb;
		args.GetReturnValue().Set(String::NewFromUtf8(isolate,
			jobbasic->channelFileName(args[0]->ToInt32()->Value()).toRRUTF8().value,
			v8::String::kInternalizedString));
	}

	static void channelFileName_set(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_2(channelFileName_set, Int32, String, ARGSDESCR(index, value))

		rrJ::_JobBasics* jobbasic = node::ObjectWrap::Unwrap<JobBasics>(args.This())->internalOb;
		jobbasic->channelSetFileName(args[0]->ToInt32()->Value(),
		QString::fromUtf8(*v8::String::Utf8Value(args[1]->ToString())));
	}

	static void channelExtension(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_1(channelExtension, Int32, ARGSDESCR(index))

		rrJ::_JobBasics* jobbasic = node::ObjectWrap::Unwrap<JobBasics>(args.This())->internalOb;
		args.GetReturnValue().Set(String::NewFromUtf8(isolate,
			jobbasic->channelExtension(args[0]->ToInt32()->Value()).toRRUTF8().value,
			v8::String::kInternalizedString));
	}

	static void channelExtension_set(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_2(channelExtension_set, Int32, String, ARGSDESCR(index, value))

		rrJ::_JobBasics* jobbasic = node::ObjectWrap::Unwrap<JobBasics>(args.This())->internalOb;
		jobbasic->channelSetExtension(args[0]->ToInt32()->Value(),
			QString::fromUtf8(*v8::String::Utf8Value(args[1]->ToString())));
	}

	static void IDstrFull(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		rrJ::_JobBasics* jobbasic = node::ObjectWrap::Unwrap<JobBasics>(args.This())->internalOb;
		args.GetReturnValue().Set(String::NewFromUtf8(isolate,
			jobbasic->IDstrFull().toUtf8().data(),
			v8::String::kInternalizedString));
	}

	static void sceneDisplayName(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		rrJ::_JobBasics* jobbasic = node::ObjectWrap::Unwrap<JobBasics>(args.This())->internalOb;
		args.GetReturnValue().Set(String::NewFromUtf8(isolate,
			jobbasic->getSceneDisplayName().toUtf8().data(),
			v8::String::kInternalizedString));
	}

	static void splitImageFileInto_DirFileExt(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		CHECKARGS_1(check_SplitImageFileInto_DirFileExt, Boolean, ARGSDESCR(percentPadding))

		rrJ::_JobBasics* jobbasic = node::ObjectWrap::Unwrap<JobBasics>(args.This())->internalOb;
		jobbasic->splitImageFileInto_DirFileExt();
	}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	INIT_RR_WRAP(JobBasics,
		NODE_SET_PROTOTYPE_METHOD(tpl, "waitForPreID", waitForPreID);
		NODE_SET_PROTOTYPE_METHOD(tpl, "waitForPreID_set", waitForPreID_set);
		NODE_SET_PROTOTYPE_METHOD(tpl, "channelFileName", channelFileName);
		NODE_SET_PROTOTYPE_METHOD(tpl, "channelFileName_set", channelFileName_set);
		NODE_SET_PROTOTYPE_METHOD(tpl, "channelExtension", channelExtension);
		NODE_SET_PROTOTYPE_METHOD(tpl, "channelExtension_set", channelExtension_set);
		NODE_SET_PROTOTYPE_METHOD(tpl, "IDstr", IDstr<JobBasics>);
		NODE_SET_PROTOTYPE_METHOD(tpl, "IDstrFull", IDstrFull);
		NODE_SET_PROTOTYPE_METHOD(tpl, "sceneDisplayName", sceneDisplayName);
		NODE_SET_PROTOTYPE_METHOD(tpl, "splitImageFileInto_DirFileExt", splitImageFileInto_DirFileExt);
		/* Shared with Settings Only */
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_Str", custom_Str);
		NODE_SET_PROTOTYPE_METHOD(tpl, "customSet_Str", customSet_Str);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_UserInfo", custom_UserInfo);
		NODE_SET_PROTOTYPE_METHOD(tpl, "customSet_UserInfo", customSet_UserInfo);
		NODE_SET_PROTOTYPE_METHOD(tpl, "customGet_maxIDs", customGet_maxIDs);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_StrByID", custom_StrByID);
		NODE_SET_PROTOTYPE_METHOD(tpl, "customSet_StrByID", customSet_StrByID);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_NameByID", custom_NameByID);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_AllAsString", custom_AllAsString);
        NODE_SET_PROTOTYPE_METHOD(tpl, "custom_ClearAll", custom_ClearAll);
        ,  )


/****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
		JOB SEND
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************/

//---------- CONSTRUCTION -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		v8::Persistent<v8::Function> JobSend::constructor;

void JobSend::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		Handle<Object> self = args.This();
		JobSend *_jobSend = new JobSend();
		_jobSend->Wrap(self);

		// Accessors
		SETTINGSSCENE_ACCESS
		SETTINGSONLY_ACCESS
		JOBBASIC_ACCESS
		JOBSEND_ACCESS

			self->SetHiddenValue(String::NewFromUtf8(isolate, "__jobsend__", v8::String::kInternalizedString), v8::Null(isolate));

		args.GetReturnValue().Set(args.This());
	}

	Handle<Value> JobSend::fromJobSend(rrJ::_JobSend* jobSend)
	{
		// no scope because this is called from other C++ code!
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance();

		ObjectWrap::Unwrap<JobSend>(instance)->internalOb = jobSend;

		return instance;
	}

	JobSend::JobSend(void)
	{}

	JobSend::~JobSend(void)
	{}

	//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	bool JobSend::objectIs(v8::Handle<v8::Object> obj)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
			"__jobsend__",
			String::kInternalizedString)
			);

		return !val->IsUndefined();
	}

	//---------- NODE METHODS
	static void clientAssigned(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_1(clientAssigned, Int32, ARGSDESCR(clientNumber))

		rrJ::_JobSend* jobsend = node::ObjectWrap::Unwrap<JobSend>(args.This())->internalOb;
		bool assigned = jobsend->clientAssigned_Get(args[0]->ToInt32()->Value());
		args.GetReturnValue().Set(assigned ? v8::True(isolate) : v8::False(isolate));
	}

	static void clientAssigned_Set(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_2(clientAssigned_Set, Int32, Int32, ARGSDESCR(clientNumber, Value))

		rrJ::_JobSend* jobsend = node::ObjectWrap::Unwrap<JobSend>(args.This())->internalOb;
		jobsend->clientAssigned_Set(args[0]->ToInt32()->Value(), args[1]->ToInt32()->Value());
	}

	static void clientValue_Get(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_2(clientValue_Get, Int32, Int32, ARGSDESCR(clientNumber, valueID))

		rrJ::_JobSend* jobsend = node::ObjectWrap::Unwrap<JobSend>(args.This())->internalOb;
		args.GetReturnValue().Set(v8::Number::New(isolate, jobsend->clientAssigned_Get(args[0]->ToInt32()->Value())));
	}

	static void fileNumber2jobNumber(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_2(fileNumber2jobNumber, Number, Int32, ARGSDESCR(filenumber, MultiFrameID))

		rrJ::_JobSend* jobsend = node::ObjectWrap::Unwrap<JobSend>(args.This())->internalOb;
		args.GetReturnValue().Set( v8::Int32::New(isolate, jobsend->fn2F(args[0]->ToInt32()->Value(), args[1]->ToInt32()->Value())) );
	}

	static void jobNumber2fileNumber(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_1(jobNumber2fileNumber, Int32, ARGSDESCR(jobNumber))

		rrJ::_JobSend* jobsend = node::ObjectWrap::Unwrap<JobSend>(args.This())->internalOb;
		args.GetReturnValue().Set( v8::Number::New(isolate, jobsend->F2fn_noMulti(args[0]->ToInt32()->Value())) );
	}

	static void jobNumber2multiID(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_1(jobNumber2multiID, Int32, ARGSDESCR(jobNumber))

		rrJ::_JobSend* jobsend = node::ObjectWrap::Unwrap<JobSend>(args.This())->internalOb;
		args.GetReturnValue().Set(v8::Int32::New(isolate, jobsend->F2fn_getMulti(args[0]->ToInt32()->Value())));
	}

	static void previewID2FrameNr(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_1(previewID2FrameNr, Int32, ARGSDESCR(id))

		rrJ::_JobSend* jobsend = node::ObjectWrap::Unwrap<JobSend>(args.This())->internalOb;
		args.GetReturnValue().Set(v8::Int32::New(isolate, jobsend->previewID2FrameNr(args[0]->ToInt32()->Value())));
	}

	static void previewFilenameThumbnail(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_1(previewFilenameThumbnail, Int32, ARGSDESCR(id))

		rrJ::_JobSend* jobsend = node::ObjectWrap::Unwrap<JobSend>(args.This())->internalOb;
        const QString& previewFilenameThumbnail = jobsend->previewFilenameThumbnail_Python(args[0]->ToInt32()->Value());

		args.GetReturnValue().Set(String::NewFromUtf8(isolate,
			previewFilenameThumbnail.toUtf8().data(),
			v8::String::kInternalizedString));
	}

	static void previewFilenameRGB(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_1(previewFilenameRGB, Int32, ARGSDESCR(id))

		rrJ::_JobSend* jobsend = node::ObjectWrap::Unwrap<JobSend>(args.This())->internalOb;
        const QString& previewFileNameRGB = jobsend->previewFilenameRGB_Python(args[0]->ToInt32()->Value());

		args.GetReturnValue().Set(String::NewFromUtf8(isolate,
			previewFileNameRGB.toUtf8().data(),
			v8::String::kInternalizedString));
	}

	static void previewFilenameA(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		CHECKARGS_1(previewFilenameA, Int32, ARGSDESCR(id))

		rrJ::_JobSend* jobsend = node::ObjectWrap::Unwrap<JobSend>(args.This())->internalOb;
        const QString& previewFilenameA = jobsend->previewFilenameA_Python(args[0]->ToInt32()->Value());

		args.GetReturnValue().Set(String::NewFromUtf8(isolate,
			previewFilenameA.toUtf8().data(),
			v8::String::kInternalizedString));
	}

	//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	INIT_RR_WRAP(JobSend,
		NODE_SET_PROTOTYPE_METHOD(tpl, "clientAssigned", clientAssigned);
		NODE_SET_PROTOTYPE_METHOD(tpl, "clientAssigned_Set", clientAssigned_Set);
		NODE_SET_PROTOTYPE_METHOD(tpl, "clientValue_Get", clientValue_Get);
		NODE_SET_PROTOTYPE_METHOD(tpl, "fileNumber2jobNumber", fileNumber2jobNumber);
		NODE_SET_PROTOTYPE_METHOD(tpl, "jobNumber2fileNumber", jobNumber2fileNumber);
		NODE_SET_PROTOTYPE_METHOD(tpl, "jobNumber2multiID", jobNumber2multiID);
		NODE_SET_PROTOTYPE_METHOD(tpl, "previewID2FrameNr", previewID2FrameNr);
		NODE_SET_PROTOTYPE_METHOD(tpl, "previewFilenameThumbnail", previewFilenameThumbnail);
		NODE_SET_PROTOTYPE_METHOD(tpl, "previewFilenameRGB", previewFilenameRGB);
		NODE_SET_PROTOTYPE_METHOD(tpl, "previewFilenameA", previewFilenameA);
		/* from JobBasics*/
		NODE_SET_PROTOTYPE_METHOD(tpl, "waitForPreID", waitForPreID);
		NODE_SET_PROTOTYPE_METHOD(tpl, "waitForPreID_set", waitForPreID_set);
		NODE_SET_PROTOTYPE_METHOD(tpl, "channelFileName", channelFileName);
		NODE_SET_PROTOTYPE_METHOD(tpl, "channelFileName_set", channelFileName_set);
		NODE_SET_PROTOTYPE_METHOD(tpl, "channelExtension", channelExtension);
		NODE_SET_PROTOTYPE_METHOD(tpl, "channelExtension_set", channelExtension_set);
		NODE_SET_PROTOTYPE_METHOD(tpl, "IDstr", IDstr<JobSend>);
		NODE_SET_PROTOTYPE_METHOD(tpl, "IDstrFull", IDstrFull);
		NODE_SET_PROTOTYPE_METHOD(tpl, "sceneDisplayName", sceneDisplayName);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_Str", custom_Str);
		NODE_SET_PROTOTYPE_METHOD(tpl, "customSet_Str", customSet_Str);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_UserInfo", custom_UserInfo);
		NODE_SET_PROTOTYPE_METHOD(tpl, "customSet_UserInfo", customSet_UserInfo);
		NODE_SET_PROTOTYPE_METHOD(tpl, "customGet_maxIDs", customGet_maxIDs);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_StrByID", custom_StrByID);
		NODE_SET_PROTOTYPE_METHOD(tpl, "customSet_StrByID", customSet_StrByID);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_NameByID", custom_NameByID);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_AllAsString", custom_AllAsString);
		NODE_SET_PROTOTYPE_METHOD(tpl, "custom_ClearAll", custom_ClearAll);
        NODE_SET_PROTOTYPE_METHOD(tpl, "splitImageFileInto_DirFileExt", splitImageFileInto_DirFileExt); \
            /* from SettingsOnly */
            NODE_SET_PROTOTYPE_METHOD(tpl, "rrOption", rrOption); \
            NODE_SET_PROTOTYPE_METHOD(tpl, "rrOption_Set", rrOption_Set); \
            NODE_SET_PROTOTYPE_METHOD(tpl, "rrParam", rrParam); \
            NODE_SET_PROTOTYPE_METHOD(tpl, "rrParam_Set", rrParam_Set); 
        , )


/****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
	rrJob
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************************************************************************************/

//---------- CONSTRUCTION -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	v8::Persistent<v8::Function> rrJob::constructor;

	rrJob::rrJob(void)
	{}

	rrJob::~rrJob(void)
	{}

	void rrJob::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);

		Handle<Object> self = args.This();
		rrJob *job = new rrJob();
		job->Wrap(self);

		// enum properties
		{
			ENUM_PRE_INCLUDE
			#include "../../../shared_SDK/RR_DataTypes_jobs_LogMessage_SDK.enum"

			obj->Set(v8::String::NewFromUtf8(isolate, "properties", v8::String::kInternalizedString), props);
			self->Set(String::NewFromUtf8(isolate, "_logMessage", v8::String::kInternalizedString), obj);
		}

		{
			ENUM_PRE_INCLUDE
			#include "../../../shared_SDK/RR_DataTypes_RenderApp_SDK.enum"

			obj->Set(v8::String::NewFromUtf8(isolate, "properties", v8::String::kInternalizedString), props);
			self->Set(String::NewFromUtf8(isolate, "_rrOptions", v8::String::kInternalizedString), obj);
		}

		{
			ENUM_PRE_INCLUDE
			#include "../../../shared_SDK/RR_DataTypes_RenderApp_params_SDK.enum"

			obj->Set(v8::String::NewFromUtf8(isolate, "properties", v8::String::kInternalizedString), props);
			self->Set(String::NewFromUtf8(isolate, "_rrParam", v8::String::kInternalizedString), obj);
		}

		Local<Object> _status = enum_props(isolate, 20, 11, "sNone", "sFirstCheck", "sWaitForJobs", "sScriptPreRender",
										"sPreviewRender", "sWaitForApprovalMain", "sMainRender", "sScriptPostRender",
										"sWaitForApprovalDone", "sScriptFinished", "sFinished");

		// status has two more values
		Local<Object> status_props = _status->Get(String::NewFromUtf8(isolate, "properties", v8::String::kInternalizedString))->ToObject();

		Local<String> prop_name = String::NewFromUtf8(isolate, "sScriptAfterPreview", v8::String::kInternalizedString);
		Local<Integer> prop_val = Int32::New(isolate, 90);
		_status->Set(prop_name, prop_val);
		set_enum_prop(isolate, status_props, prop_name, prop_val);

		prop_name = String::NewFromUtf8(isolate, "sWaitForJobsAfterPreview", v8::String::kInternalizedString);
		prop_val = Int32::New(isolate, 110);
		_status->Set(prop_name, prop_val);
		set_enum_prop(isolate, status_props, prop_name, prop_val);

		self->Set(String::NewFromUtf8(isolate, "_Status", v8::String::kInternalizedString), _status);

		args.GetReturnValue().Set(args.This());
	}

	void rrJob::newInst(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		v8::HandleScope scope(isolate);

		const unsigned argc = 1;
		Handle<Value> argv[argc] = { args[0] };

		Local<Function> cons = Local<Function>::New(isolate, constructor);
		v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

		args.GetReturnValue().Set(instance);
	}

	void rrJob::getClass_JobBasics(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
		JobBasics::newInst(args);
	}

	void rrJob::getClass_SettingsOnly(const v8::FunctionCallbackInfo<v8::Value>& args)
	{
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope scope(isolate);
		SettingsOnly::newInst(args);
	}

	//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	INIT_RR_WRAP(rrJob, NODE_SET_PROTOTYPE_METHOD(tpl, "getClass_JobBasics", getClass_JobBasics);
    NODE_SET_PROTOTYPE_METHOD(tpl, "getClass_SettingsOnly", getClass_SettingsOnly); 
    ,   RenderAppBasic::init();
		JobMinInfo::init();
		JobBasics::init();
		SettingsOnly::init();
		JobList::init();
        JobSend::init();
		)
