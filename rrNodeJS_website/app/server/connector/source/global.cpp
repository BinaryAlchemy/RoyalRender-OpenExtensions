#include <stdarg.h>

#include "common.h"
#include "global.h"
#include "enums.h"

using namespace v8;


// RRGlobal
//---------- CONSTRUCTION
Persistent<Function> RRGlobal::constructor;

void RRGlobal::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	RRGlobal *rr_global = new RRGlobal();
	rr_global->Wrap(self);

	// rrC::_ClientCommand
	{
		ENUM_PRE_INCLUDE
		#include "../../../shared/RR_DataTypes_commands_rrc__ClientCommand.enum"
		
		obj->Set(v8::String::NewFromUtf8(isolate, "properties", v8::String::kInternalizedString), props);
		self->Set(String::NewFromUtf8(isolate, "ClientCommand", v8::String::kInternalizedString), obj);
	}

	// rrRA::_executeJobType
	Local<Object> _jobType = enum_props(isolate, 1, 4, "none", "once", "eachClient", "perFrame");
	self->Set(String::NewFromUtf8(isolate, "executeJobType", v8::String::kInternalizedString), _jobType);

	// _rrLogLvL
	Local<Object> logLvL = enum_props(isolate, 1, 5, "critical", "error", "warning", "info", "progress");

	Local<Object> logLvL_props = logLvL->Get(String::NewFromUtf8(isolate, "properties", v8::String::kInternalizedString))->ToObject();

	Local<String> prop_name = String::NewFromUtf8(isolate, "debug", v8::String::kInternalizedString);
	Local<Integer> prop_val = Int32::New(isolate, 10);

	logLvL->Set(prop_name, prop_val);
	set_enum_prop(isolate, logLvL_props, prop_name, prop_val);

	self->Set(String::NewFromUtf8(isolate, "logLvL", v8::String::kInternalizedString), logLvL);

	Local<Object> cl_status_lst = enum_props(isolate, 1, 30, "sOff", "sFree", "sDisabled", "sRendering", "sRenderingSuccessful",
		"sAborted", "sCrashed", "sDisabledAllowLittle", "sRenderingStarting", "sNoLicense", "sPermanentCrashed", "sClientFreeze",
		"sAbortedDisable", "sAbortedLowMemory", "sAbortedFrozen", "sAbortedHighUserCPU", "sAbortedFrameTime", "sAbortedWorkinghours",
		"sAbortedReservedClient", "sAbortedHighPriority", "sAbortedrrControl", "sAbortedAverage", "sAbortedLicenseBlock",
		"sAbortedLocalMachine", "sAbortedProcessFound", "sRenderingSuccessfulNoNewJob", "sDisabledWorkinghours",
		"sDisabledWorkinghoursAllowLittle", "sDisabledKeepDisabled", "sCrashedKSOLogError");

	self->Set(String::NewFromUtf8(isolate, "ClientStatusList", v8::String::kInternalizedString), cl_status_lst);

	Local<Object> cl_status_job = enum_props(isolate, 1, 21, "sjNone", "sjHighCpuUsage", "sjWorkingHours", "sjSatelliteRendering",
		"sjWait", "sjLowMemory", "sjInWOL", "sjUserLoggedOff", "sjShutdown", "sjInWOLBroken", "sjAbortProcess", "sjClientOff",
		"sjClientLost", "sjUITakeOver", "sjDeferMode", "sjVmBooting", "sjVmCreating", "sjMacRestart", "sjMacShutdown", "sjAppRestart",
		"sjAppShutdown", "sjShutdownExtern");

	self->Set(String::NewFromUtf8(isolate, "ClientStatusJob", v8::String::kInternalizedString), cl_status_job);

	// rrP::_rrpReturnCode
	Local<Object> pluginReturn = enum_props(isolate, 1, 28, "rUnknownError", "rSuccessful", "rFileNotFound", "rFileFailedToOpen",
				"rUnsupportedFormat", "rRRDataVersionConflict", "rCError", "rMemError", "rPluginFileMissing", "rPluginLoadError",
				"rSuccessfulIgnoreNoJobs", "rOtherError", "rWrongFileSize", "rNoImageDimensions", "rDataError", "rImageDimensionsToLarge",
				"rRequireFullLoad", "rNoPluginforFileType", "rPythonError", "rFileSizeToSmall", "rDebugCompile", "rIsPlaceHolderFile",
				"rFileFailedToSave", "rSuccessfulRetryLoad", "rFileBuffertoSmall", "rNoImageOutput", "rAbsolutePathsRequired", "rLoadEndOfFileOnly",
				"rSuccessfulPython");

    self->Set(String::NewFromUtf8(isolate, "pluginReturn", v8::String::kInternalizedString), pluginReturn);

	// property for object recognition
	self->SetHiddenValue(String::NewFromUtf8(isolate, "__rrglobal__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void RRGlobal::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

RRGlobal::RRGlobal(void)
{}

RRGlobal::~RRGlobal(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool RRGlobal::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__rrglobal__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(RRGlobal, , )
