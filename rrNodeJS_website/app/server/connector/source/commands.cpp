// commands.cpp

#include "commands.h"
#include "enums.h"

//#include "RR_DataTypes_commands.h" -- NOT needed, but this is where the enumeration are originally declared!

using namespace v8;


void CMD::init(v8::Handle<v8::Object> exports)
{
	Isolate *isolate = Isolate::GetCurrent();
	// _rrRRCommand  TODO: maybe this should be in rrGlobal only
	{
		ENUM_PRE_INCLUDE
		#include "../../../shared/RR_DataTypes_commands__rrRRCommand.enum"

		obj->Set(v8::String::NewFromUtf8(isolate, "properties", v8::String::kInternalizedString), props);
		exports->Set(String::NewFromUtf8(isolate, "RRCommand", v8::String::kInternalizedString), obj);
	}

	// rrS::_ServerCommand
	{
		ENUM_PRE_INCLUDE
		#include "../../../shared/RR_DataTypes_commands_rrS__ServerCommand.enum"

		obj->Set(v8::String::NewFromUtf8(isolate, "properties", v8::String::kInternalizedString), props);
		exports->Set(String::NewFromUtf8(isolate, "ServerCommand", v8::String::kInternalizedString), obj);
	}

	// _rrTCPjobList_dataIDs
	const Local<Object> _dataIDs = enum_props(isolate, 1, 4, "jlNone", "jlMinInfo", "jlBasic", "jlSend");
	exports->Set(String::NewFromUtf8(isolate, "_dataIDs", v8::String::kInternalizedString), _dataIDs);

	// _rrTCPjobList::_sortIDs
	const Local<Object> _sortIDs = enum_props(isolate, 1, 16, "sQueue", "sUser", "sDateSend", "sPriority",
								"sProject", "sCustomName", "sRenderApp", "sApproved", "sFramesLeft",
								"sFramesDone", "sTimeRemaining", "sStatus", "sScene", "sLayer",
								"sCamera", "sFrameTime");

	// rrj::_JobFilterIDs
	Local<Object> _filterIDs = enum_props_binary(isolate, 1, 5, "isIdle", "isRendering", "isDisabled",
																"isWaitFor", "isFinished");

	// _filterIDs has irregular entries
	Local<Object> filterIDs_props = _filterIDs->Get(String::NewFromUtf8(isolate, "properties", v8::String::kInternalizedString))->ToObject();

	Local<String> prop_name = String::NewFromUtf8(isolate, "isAll", v8::String::kInternalizedString);
	Local<Integer> prop_val = Int32::New(isolate, 255);

	_filterIDs->Set(prop_name, prop_val);
	set_enum_prop(isolate, filterIDs_props, prop_name, prop_val);

	exports->Set(String::NewFromUtf8(isolate, "_dataIDs", v8::String::kInternalizedString), _dataIDs);
	exports->Set(String::NewFromUtf8(isolate, "_sortIDs", v8::String::kInternalizedString), _sortIDs);
	exports->Set(String::NewFromUtf8(isolate, "_filterIDs", v8::String::kInternalizedString), _filterIDs);
}

