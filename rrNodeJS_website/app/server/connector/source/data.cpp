#include "data.h"
#include "common.h"

#include "../../sharedLib/RR_other_SDK.h"
#include "../../shared_SDK/RR_version_SDK.inc"
#include "../../sharedLib/RR_files_SDK.h"

#include <QString>


using namespace v8;
// Copied from pyRR2_datafiles

static void getRRModuleVersion(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, rrVersion,
		v8::String::kNormalString, sizeof(rrVersion)));
}

bool IsValidRR_Root_local(const QString &path)
{

	if (path.isEmpty()) return false;
#ifdef RR_OS_LINUX
	if (path.at(0) != PD) return false; //path is relative...
#endif

	if (rrFileExists(path + "sub" + PD + "cfg_global" + PD + "globalconfig.ini")) return true;
	if (rrDirectoryExists(path + "sub" + PD + "cfg_global" + PD)) return true;

#ifdef RR_OS_WIN
	if (rrFileExists(path + "bin" + PD + "win" + PD + "rrClientconsole.exe")) return true;
	if (rrFileExists(path + "bin" + PD + "win" + PD + "rrServerconsole.exe")) return true;
	if (rrFileExists(path + "sub" + PD + "cfg_global" + PD + "relink_win.cfg")) return true;
	if (rrFileExists(QString(path).replace("_debug", "_release") + "sub" + PD + "cfg_global" + PD + "relink_win.cfg")) return true;
#elif defined (RR_OS_MAC)
	if (rrFileExists(path + "bin" + PD + "mac" + PD + "rrClientconsole")) return true;
	if (rrFileExists(path + "bin" + PD + "mac" + PD + "rrServerconsole")) return true;
	if (rrFileExists(path + "sub" + PD + "cfg_global" + PD + "relink_mac.cfg")) return true;
	if (rrFileExists(QString(path).replace("_debug", "_release") + "sub" + PD + "cfg_global" + PD + "relink_mac.cfg")) return true;
#else
	if (rrFileExists(path + "bin" + PD + "lx64" + PD + "rrClientconsole")) return true;
	if (rrFileExists(path + "bin" + PD + "lx64" + PD + "rrServerconsole")) return true;
	if (rrFileExists(path + "sub" + PD + "cfg_global" + PD + "relink_lx.cfg")) return true;
	if (rrFileExists(QString(path).replace("_debug", "_release") + "sub" + PD + "cfg_global" + PD + "relink_lx.cfg")) return true;
#endif

#ifdef defrrDebugJobExport
	return true;
#endif	

	return false;
}

QString getBaseRoot()
{
	QString RR_Root = rrGetEnvironmentVariable("RR_ROOT");
	if (RR_Root.isEmpty()) {
		//pErrorStr = "No environment variable RR_ROOT found.";
		return QString();
	}
	if (!RR_Root.endsWith(PDs)) RR_Root += PDs;
	RR_Root = RR_Root.replace("_debug", "_release");
	if (!IsValidRR_Root_local(RR_Root)) {
		//pErrorStr = "Environment RR_ROOT is not a valid RR installation:'" + RR_Root + "'.";
		return QString();
	}
	QString relinkfilename = RR_Root + "sub" + PDs + "cfg_global" + PDs + "relink_win.cfg";
	if (rrFileExists(relinkfilename)) {
		QFile relFile(relinkfilename);
		if (!relFile.open(QIODevice::ReadOnly | QIODevice::Text)) return "";
		QString line = relFile.readLine();
		line = line.trimmed();
		if (line.startsWith("Root", Qt::CaseInsensitive) && line.contains('=')) {
			RR_Root = line.remove(0, line.indexOf('=') + 1).trimmed();
			if (!RR_Root.endsWith(PD)) RR_Root += PD;
		}
		relFile.close();
	}
	return RR_Root;
}

static void getRRFolder_cfgGlobal(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	QString folder = getBaseRoot();
	if (!folder.isEmpty()) {
		folder += "sub" + PDs + "cfg_global" + PDs;
	}

	args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, folder.toUtf8().data(),
		v8::String::kNormalString, folder.length()));
}

static void getRRFolder_cfgUser(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	QString folder = getBaseRoot();
	if (!folder.isEmpty()) {
		folder += "sub" + PDs + "cfg_user" + PDs;
	}

	args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, folder.toUtf8().data(),
		v8::String::kNormalString, folder.length()));
}

static void getRRFolder_cfgStats(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	QString folder = getBaseRoot();
	if (!folder.isEmpty()) {
		folder += "sub" + PDs + "stats" + PDs;
	}

	args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, folder.toUtf8().data(),
		v8::String::kNormalString, folder.length()));
}

static void getRRFolder_bin(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	v8::HandleScope scope(isolate);

	QString folder = getBaseRoot();
	if (!folder.isEmpty()) {
#ifdef RR_OS_WIN
		folder += "bin" + PDs + "win64" + PDs;
#elif defined  RR_OS_LX
		folder += "bin" + PDs + "lx64" + PDs;
#else
		folder += "bin" + PDs + "mac64" + PDs;

#endif


	}
	args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, folder.toUtf8().data(),
		v8::String::kNormalString, folder.length()));
}


// NodeJS part

static void getNewClientGroupList(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	ClientGroupList::newInst(args);
}

static void getNewClientGroup(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	ClientGroup::newInst(args);
}

static void getDailyStats(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	DailyStatsData::newInst(args);
}

static void getSaveStats(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	StatsSaveData::newInst(args);
}

static void getSaveStatsLS(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	StatsSaveDataLS::newInst(args);
}

static void getClientStats(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	ClientStatsData::newInst(args);
}

static void getFrameStat(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	FrameStat::newInst(args);
}

static void getFrameStatJob(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	FrameStatJob::newInst(args);
}

static void getStatsRenderTime(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	StatsRenderTime::newInst(args);
}


// ClientGroup
//---------- CONSTRUCTION
Persistent<Function> ClientGroup::constructor;

void ClientGroup::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	ClientGroup *clntGrpList = new ClientGroup();
	clntGrpList->Wrap(self);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__clientgrp__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void ClientGroup::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	ClientGroup* client_group = ObjectWrap::Unwrap<ClientGroup>(instance);
	client_group->clntGrp = rrC::_ClientGroup();

	args.GetReturnValue().Set(instance);
}

ClientGroup::ClientGroup(void)
{}

ClientGroup::~ClientGroup(void)
{}

Handle<Value> ClientGroup::fromClientGroup(rrC::_ClientGroup grp)
{
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	ClientGroup* client_group = ObjectWrap::Unwrap<ClientGroup>(instance);
	client_group->clntGrp = grp;

	return instance;
}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ClientGroup::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue( String::NewFromUtf8(isolate,
		"__clientgrp__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- NODE METHODS
void ClientGroup::clear(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	rrC::_ClientGroup& grp = ObjectWrap::Unwrap<ClientGroup>(args.This())->clntGrp;
	grp.clear();
}

void ClientGroup::getName(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	rrC::_ClientGroup& grp = ObjectWrap::Unwrap<ClientGroup>(args.This())->clntGrp;
	_rrString25 grpName = grp.getName();

	args.GetReturnValue().Set(String::NewFromUtf8(isolate,
		grpName.toRRUTF8().value,
		v8::String::kInternalizedString));
}

void ClientGroup::setName(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(setName, String, ARGSDESCR(name))

	rrC::_ClientGroup& grp = ObjectWrap::Unwrap<ClientGroup>(args.This())->clntGrp;
	grp.setName(*v8::String::Utf8Value(args[0]->ToString()));
}

void ClientGroup::getClientName(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(getClientName, Int32, ARGSDESCR(idx))

	rrC::_ClientGroup& grp = ObjectWrap::Unwrap<ClientGroup>(args.This())->clntGrp;
	const _rrString8_50& clName = grp.getClientName(args[0]->ToInt32()->Value());

	v8::Local<v8::String> clnameStr = v8::String::NewFromUtf8(isolate,
		std::string(clName.value,
		clName.length).c_str(),
		v8::String::kInternalizedString);

	args.GetReturnValue().Set(clnameStr);
}

void ClientGroup::addClient(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(addClient, String, ARGSDESCR(name))

	rrC::_ClientGroup& grp = ObjectWrap::Unwrap<ClientGroup>(args.This())->clntGrp;
	grp.addClient(QString::fromUtf8((*v8::String::Utf8Value(args[0]->ToString()))));
}

void ClientGroup::removeClient(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(removeClient, String, ARGSDESCR(name))

	rrC::_ClientGroup& grp = ObjectWrap::Unwrap<ClientGroup>(args.This())->clntGrp;
	grp.removeClient(*v8::String::Utf8Value(args[0]->ToString()));
}

void ClientGroup::removeClientbyID(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(removeClientbyID, Int32, ARGSDESCR(idx));

	rrC::_ClientGroup& grp = ObjectWrap::Unwrap<ClientGroup>(args.This())->clntGrp;
	grp.removeClientbyID(args[0]->ToInt32()->Value());
}

void ClientGroup::count(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	rrC::_ClientGroup& grp = ObjectWrap::Unwrap<ClientGroup>(args.This())->clntGrp;
	args.GetReturnValue().Set(Int32::New(isolate, grp.count()));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(ClientGroup,
	NODE_SET_PROTOTYPE_METHOD(tpl, "clear", clear);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getName", getName);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setName", setName);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getClientName", getClientName);
	NODE_SET_PROTOTYPE_METHOD(tpl, "addClient", addClient);
	NODE_SET_PROTOTYPE_METHOD(tpl, "removeClient", removeClient);
	NODE_SET_PROTOTYPE_METHOD(tpl, "removeClientbyID", removeClientbyID);
    NODE_SET_PROTOTYPE_METHOD(tpl, "count", count);
    ,	)


// ClientGroupList
//---------- CONSTRUCTION
Persistent<Function> ClientGroupList::constructor;

void ClientGroupList::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	ClientGroupList *clntGrpList = new ClientGroupList();
	clntGrpList->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "count", v8::String::kInternalizedString), getCount, setCount);
	self->SetAccessor(String::NewFromUtf8(isolate, "settingsFileDate", v8::String::kInternalizedString), getSettingsFileDate, setSettingsFileDate);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__clientgrplist__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void ClientGroupList::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

ClientGroupList::ClientGroupList(void) : clntGrp()
{}

ClientGroupList::~ClientGroupList(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ClientGroupList::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	return obj->Has(String::NewFromUtf8(isolate, "__clientgrplist__", v8::String::kInternalizedString));
}

//---------- ACCESSORS
void ClientGroupList::getCount(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const rrC::_ClientGroupList& clntGrpList = ObjectWrap::Unwrap<ClientGroupList>(info.Holder())->clntGrp;
	info.GetReturnValue().Set(v8::Int32::New(isolate, clntGrpList.count));
}

void ClientGroupList::setCount(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	CHECKVAL(count, Int32, "(the number of groups)")
	ObjectWrap::Unwrap<ClientGroupList>(info.Holder())->clntGrp.count = value->ToInt32()->Value();
}

void ClientGroupList::getSettingsFileDate(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	rrC::_ClientGroupList& clntGrpList = ObjectWrap::Unwrap<ClientGroupList>(info.Holder())->clntGrp;
	info.GetReturnValue().Set(Date::New(isolate, clntGrpList.settingsFileDate.toLocalTime() * 1000));
}

void ClientGroupList::setSettingsFileDate(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	CHECKVAL(settingsFileDate, Date, "(Date/Time of the group settings file loaded/saved)")
	if (value->IsDate()) {
		qint64 millisSinceEpoch = v8::Date::Cast(*value)->NumberValue();
		rrC::_ClientGroupList& clntGrpList = ObjectWrap::Unwrap<ClientGroupList>(info.Holder())->clntGrp;
		clntGrpList.settingsFileDate.value = millisSinceEpoch / 1000;
	}
}

//---------- NODE METHODS
void ClientGroupList::loadFromFile(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(loadFromFile, String, ARGSDESCR(FileName))

	rrC::_ClientGroupList& clntGrpList = ObjectWrap::Unwrap<ClientGroupList>(args.This())->clntGrp;
	const bool success = clntGrpList._loadFromFilePython(QString::fromUtf8(*v8::String::Utf8Value(args[0]->ToString())));
	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void ClientGroupList::saveToFile(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(saveToFile, String, ARGSDESCR(FileName))

	rrC::_ClientGroupList& clntGrpList = ObjectWrap::Unwrap<ClientGroupList>(args.This())->clntGrp;
	const bool success = clntGrpList._saveToFile_python(QString::fromUtf8(*v8::String::Utf8Value(args[0]->ToString())));
	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void ClientGroupList::getError(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	rrC::_ClientGroupList& clntGrpList = ObjectWrap::Unwrap<ClientGroupList>(args.This())->clntGrp;
	args.GetReturnValue().Set(String::NewFromUtf8(isolate,
		clntGrpList.getError().toUtf8().data(),
		v8::String::kInternalizedString));
}

void ClientGroupList::clientGroupsMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	rrC::_ClientGroupList& clntGrpList = ObjectWrap::Unwrap<ClientGroupList>(args.This())->clntGrp;
	args.GetReturnValue().Set(Int32::New(isolate, clntGrpList._clientGroups_Max()));
}

void ClientGroupList::clientGroupGet(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(clientGroupGet, Int32, ARGSDESCR(idx))

	int idx = args[0]->ToInt32()->Value();
	rrC::_ClientGroupList& clntGrpList = ObjectWrap::Unwrap<ClientGroupList>(args.This())->clntGrp;

	args.GetReturnValue().Set(ClientGroup::fromClientGroup(clntGrpList._clientGroups_Get(idx)));
}

void ClientGroupList::clientGroupSet(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_2(clientGroupSet, Int32, Object, ARGSDESCR(idx, ClientGroup))

	if (!ClientGroup::objectIs(args[1]->ToObject())) {
		v8::Local<v8::String> exceptionString = v8::String::NewFromUtf8(isolate,
			"second argument is not a ClientGroup!", v8::String::kInternalizedString);
		isolate->ThrowException(Exception::TypeError(exceptionString));
		args.GetReturnValue().Set(Undefined(isolate));
		return;
	}
	
	rrC::_ClientGroup& grp = ObjectWrap::Unwrap<ClientGroup>(args[1]->ToObject())->clntGrp;
	rrC::_ClientGroupList& clntGrpList = ObjectWrap::Unwrap<ClientGroupList>(args.This())->clntGrp;
	clntGrpList._clientGroups_Set(args[0]->ToInt32()->Value(), grp);
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(ClientGroupList,
	NODE_SET_PROTOTYPE_METHOD(tpl, "clientGroup", clientGroupGet);
	NODE_SET_PROTOTYPE_METHOD(tpl, "clientGroupSet", clientGroupSet);
	NODE_SET_PROTOTYPE_METHOD(tpl, "loadFromFile", loadFromFile);
	NODE_SET_PROTOTYPE_METHOD(tpl, "saveToFile", saveToFile);
	NODE_SET_PROTOTYPE_METHOD(tpl, "clientGroupsMax", clientGroupsMax);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getError", getError);
    ,	)


// SingleStat
//---------- CONSTRUCTION
Persistent<Function> SingleStat::constructor;

void SingleStat::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	SingleStat *newStat = new SingleStat();
	newStat->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "avPSUsage", v8::String::kInternalizedString), getAvPSUsage);
	self->SetAccessor(String::NewFromUtf8(isolate, "maxPSUsage", v8::String::kInternalizedString), getMaxPSUsage);
	self->SetAccessor(String::NewFromUtf8(isolate, "avGhzUsage", v8::String::kInternalizedString), getAvGhzUsage);
	self->SetAccessor(String::NewFromUtf8(isolate, "maxGhzUsage", v8::String::kInternalizedString), getMaxGhzUsage);
	self->SetAccessor(String::NewFromUtf8(isolate, "PSneeded", v8::String::kInternalizedString), getPSneeded);
	self->SetAccessor(String::NewFromUtf8(isolate, "renderLicNeeded", v8::String::kInternalizedString), getRenderLicNeeded);
	self->SetAccessor(String::NewFromUtf8(isolate, "jobsWaiting", v8::String::kInternalizedString), getJobsWaiting);
	self->SetAccessor(String::NewFromUtf8(isolate, "jobsDisabled", v8::String::kInternalizedString), getJobsDisabled);
	self->SetAccessor(String::NewFromUtf8(isolate, "jobsIdle", v8::String::kInternalizedString), getJobsIdle);
	self->SetAccessor(String::NewFromUtf8(isolate, "jobsRendering", v8::String::kInternalizedString), getJobsRendering);
	self->SetAccessor(String::NewFromUtf8(isolate, "jobsDone", v8::String::kInternalizedString), getJobsDone);
	self->SetAccessor(String::NewFromUtf8(isolate, "timesSended", v8::String::kInternalizedString), getTimesSended);
	self->SetAccessor(String::NewFromUtf8(isolate, "timesFinished", v8::String::kInternalizedString), getTimesFinished);
	self->SetAccessor(String::NewFromUtf8(isolate, "avMemUsageMB", v8::String::kInternalizedString), getAvMemUsageMB);
	self->SetAccessor(String::NewFromUtf8(isolate, "maxMemUsageMB", v8::String::kInternalizedString), getMaxMemUsageMB);
	self->SetAccessor(String::NewFromUtf8(isolate, "avFrameTime", v8::String::kInternalizedString), getAvFrameTime);
	self->SetAccessor(String::NewFromUtf8(isolate, "framesRendered", v8::String::kInternalizedString), getFramesRendered);
	self->SetAccessor(String::NewFromUtf8(isolate, "framesLeft", v8::String::kInternalizedString), getFramesLeft);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__singlestat__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void SingleStat::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

Handle<Value> SingleStat::fromSingleStat(_singleStat* _snglStat)
{
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	SingleStat* single_stat = ObjectWrap::Unwrap<SingleStat>(instance);
	single_stat->snglStat = _snglStat;

	return instance;
}

SingleStat::SingleStat(void)
{}

SingleStat::~SingleStat(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SingleStat::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__singlestat__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- ACCESSORS
void SingleStat::getAvPSUsage(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
    info.GetReturnValue().Set(Number::New(isolate, _snglStat->avPSUsage));
}

void SingleStat::getMaxPSUsage(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Number::New(isolate, _snglStat->maxPSUsage));
}

void SingleStat::getAvGhzUsage(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Number::New(isolate, _snglStat->avGhzUsage));
}

void SingleStat::getMaxGhzUsage(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Number::New(isolate, _snglStat->maxGhzUsage));
}

void SingleStat::getPSneeded(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Number::New(isolate, _snglStat->PSneeded));
}

void SingleStat::getRenderLicNeeded(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Number::New(isolate, _snglStat->renderLicNeeded));
}

void SingleStat::getJobsWaiting(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Uint32::New(isolate, _snglStat->jobsWaiting));
}

void SingleStat::getJobsDisabled(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Uint32::New(isolate, _snglStat->jobsDisabled));
}

void SingleStat::getJobsIdle(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Uint32::New(isolate, _snglStat->jobsIdle));
}

void SingleStat::getJobsRendering(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Uint32::New(isolate, _snglStat->jobsRendering));
}

void SingleStat::getJobsDone(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Uint32::New(isolate, _snglStat->jobsDone));
}

void SingleStat::getTimesSended(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Uint32::New(isolate, _snglStat->timesSended));
}

void SingleStat::getTimesFinished(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Uint32::New(isolate, _snglStat->timesFinished));
}

void SingleStat::getAvMemUsageMB(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Uint32::New(isolate, _snglStat->avMemUsageMB));
}

void SingleStat::getMaxMemUsageMB(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Uint32::New(isolate, _snglStat->maxMemUsageMB));
}

void SingleStat::getAvFrameTime(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Uint32::New(isolate, _snglStat->avFrameTime));
}

void SingleStat::getFramesRendered(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Uint32::New(isolate, _snglStat->framesRendered));
}

void SingleStat::getFramesLeft(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _singleStat* _snglStat = ObjectWrap::Unwrap<SingleStat>(info.Holder())->snglStat;
	info.GetReturnValue().Set(Uint32::New(isolate, _snglStat->framesLeft));
}

//---------- NODE METHODS
void SingleStat::clear(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_singleStat* _sngl_stat = ObjectWrap::Unwrap<SingleStat>(args.This())->snglStat;
	_sngl_stat->clear();
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(SingleStat,
    NODE_SET_PROTOTYPE_METHOD(tpl, "clear", clear);
    ,	)


// SingleStatDay
//---------- CONSTRUCTION
Persistent<Function> SingleStatDay::constructor;

void SingleStatDay::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	SingleStatDay *newSnglStatDay = new SingleStatDay();
	newSnglStatDay->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "name", v8::String::kInternalizedString), getName, setName);
	self->SetAccessor(String::NewFromUtf8(isolate, "type", v8::String::kInternalizedString), getType);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__singlestatday__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void SingleStatDay::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	SingleStatDay* self = ObjectWrap::Unwrap<SingleStatDay>(instance);
	self->snglStatDay = new _singleStatDay();

	args.GetReturnValue().Set(instance);
}

Handle<Value> SingleStatDay::fromSingleStatDay(_singleStatDay* _snglStDay)
{
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	SingleStatDay* self = ObjectWrap::Unwrap<SingleStatDay>(instance);
	self->delInternalPointer = false;
	self->snglStatDay = _snglStDay;

	return instance;
}

Handle<Value> SingleStatDay::fromSingleStatDay(const _singleStatDay& _snglStDay)
{
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	SingleStatDay* self = ObjectWrap::Unwrap<SingleStatDay>(instance);
	self->snglStatDay = new _singleStatDay(_snglStDay);

	return instance;
}

SingleStatDay::SingleStatDay(void)
{}

SingleStatDay::~SingleStatDay(void)
{
	if (delInternalPointer) {
		delete snglStatDay;
	}
}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SingleStatDay::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__singlestatday__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- ACCESSORS
void SingleStatDay::getName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_singleStatDay* statDay = ObjectWrap::Unwrap<SingleStatDay>(info.Holder())->snglStatDay;
	statDay->name.toRRUTF8();

	info.GetReturnValue().Set(String::NewFromUtf8(isolate,
		statDay->name.toRRUTF8().value,
		v8::String::kInternalizedString)
		);
}

void SingleStatDay::setName(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	CHECKVAL(name, String, "(Name of the user, project or render app)");

	ObjectWrap::Unwrap<SingleStatDay>(info.Holder())->snglStatDay->name = *v8::String::Utf8Value(value->ToString());
}

void SingleStatDay::getType(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_singleStatDay* statDay = ObjectWrap::Unwrap<SingleStatDay>(info.Holder())->snglStatDay;
	info.GetReturnValue().Set(Int32::New(isolate, statDay->type));
}

//---------- NODE METHODS
void SingleStatDay::statsMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_singleStatDay* _sngl_stat_day = ObjectWrap::Unwrap<SingleStatDay>(args.This())->snglStatDay;
	args.GetReturnValue().Set(Int32::New(isolate, _sngl_stat_day->_stats_Max()));
}

void SingleStatDay::stats(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(stats, Int32, ARGSDESCR(idx));

    _singleStatDay* _sngl_stat_day = ObjectWrap::Unwrap<SingleStatDay>(args.This())->snglStatDay;
    int id = args[0]->ToInt32()->Value();
    _singleStat _sngl_stat;

    if (id >= rrsPerUserStatValues_PerDay - 1)
        _sngl_stat = _sngl_stat_day->stats[rrsPerUserStatValues_PerDay - 1];
    else if (id <= 0)
        _sngl_stat = _sngl_stat_day->stats[0];
    else
        _sngl_stat = _sngl_stat_day->stats[rrsPerUserStatValues_PerDay-1];

    Handle<Value> single_stat = SingleStat::fromSingleStat(&_sngl_stat);
    args.GetReturnValue().Set(single_stat);
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(SingleStatDay,
	NODE_SET_PROTOTYPE_METHOD(tpl, "stats", stats);
    NODE_SET_PROTOTYPE_METHOD(tpl, "statsMax", statsMax);
    ,	)


// StatsSaveData
//---------- CONSTRUCTION
Persistent<Function> StatsSaveData::constructor;

void StatsSaveData::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	StatsSaveData *newStatsSave = new StatsSaveData();
	newStatsSave->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "lastSaveDay", v8::String::kInternalizedString), getLastSaveDay);
	self->SetAccessor(String::NewFromUtf8(isolate, "lastSaveMonth", v8::String::kInternalizedString), getLastSaveMonth);
	self->SetAccessor(String::NewFromUtf8(isolate, "lastSaveYear", v8::String::kInternalizedString), getLastSaveYear);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__statssavedata__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void StatsSaveData::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

StatsSaveData::StatsSaveData(void) : svStatData()
{}

StatsSaveData::~StatsSaveData(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool StatsSaveData::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__statssavedata__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- ACCESSORS
void StatsSaveData::getLastSaveDay(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrsStatsSaveData& statData = ObjectWrap::Unwrap<StatsSaveData>(info.Holder())->svStatData;
	info.GetReturnValue().Set(Int32::New(isolate, statData.lastSaveDay));
}

void StatsSaveData::getLastSaveMonth(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrsStatsSaveData& statData = ObjectWrap::Unwrap<StatsSaveData>(info.Holder())->svStatData;
	info.GetReturnValue().Set(Int32::New(isolate, statData.lastSaveMonth));
}

void StatsSaveData::getLastSaveYear(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrsStatsSaveData& statData = ObjectWrap::Unwrap<StatsSaveData>(info.Holder())->svStatData;
	info.GetReturnValue().Set(Int32::New(isolate, statData.lastSaveYear));
}

//---------- NODE METHODS
void StatsSaveData::day(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(day, Int32, ARGSDESCR(idx));

	_rrsStatsSaveData& statData = ObjectWrap::Unwrap<StatsSaveData>(args.This())->svStatData;
	args.GetReturnValue().Set(StatsType::fromRRStatType(statData.day_Get(args[0]->ToInt32()->Value())));
}

void StatsSaveData::dayMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrsStatsSaveData& statData = ObjectWrap::Unwrap<StatsSaveData>(args.This())->svStatData;
	args.GetReturnValue().Set(Int32::New(isolate, statData.day_Max()));
}

void StatsSaveData::month(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(month, Int32, ARGSDESCR(idx));

	_rrsStatsSaveData& statData = ObjectWrap::Unwrap<StatsSaveData>(args.This())->svStatData;
	args.GetReturnValue().Set(StatsType::fromRRStatType(statData.month_Get(args[0]->ToInt32()->Value())));
}

void StatsSaveData::monthMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrsStatsSaveData& statData = ObjectWrap::Unwrap<StatsSaveData>(args.This())->svStatData;
	args.GetReturnValue().Set(Int32::New(isolate, statData.month_Max()));
}

void StatsSaveData::year(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(year, Int32, ARGSDESCR(idx));

	_rrsStatsSaveData& statData = ObjectWrap::Unwrap<StatsSaveData>(args.This())->svStatData;
	args.GetReturnValue().Set(StatsType::fromRRStatType(statData.year_Get(args[0]->ToInt32()->Value())));
}

void StatsSaveData::yearMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrsStatsSaveData& statData = ObjectWrap::Unwrap<StatsSaveData>(args.This())->svStatData;
	args.GetReturnValue().Set(Int32::New(isolate, statData.year_Max()));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(StatsSaveData,
	NODE_SET_PROTOTYPE_METHOD(tpl, "day", day);
	NODE_SET_PROTOTYPE_METHOD(tpl, "dayMax", dayMax);
	NODE_SET_PROTOTYPE_METHOD(tpl, "month", month);
	NODE_SET_PROTOTYPE_METHOD(tpl, "monthMax", monthMax);
	NODE_SET_PROTOTYPE_METHOD(tpl, "year", year);
    NODE_SET_PROTOTYPE_METHOD(tpl, "yearMax", yearMax);
    ,	)


// StatsSaveDataLS
//---------- CONSTRUCTION
Persistent<Function> StatsSaveDataLS::constructor;

void StatsSaveDataLS::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	StatsSaveDataLS *newStatsSave = new StatsSaveDataLS();
	newStatsSave->Wrap(self);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__statssavedatals__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void StatsSaveDataLS::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

StatsSaveDataLS::StatsSaveDataLS(void) : svStatData()
{}

StatsSaveDataLS::~StatsSaveDataLS(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool StatsSaveDataLS::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__statssavedatals__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- NODE METHODS
void StatsSaveDataLS::loadFromFile(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(loadFromFile, String, ARGSDESCR(filename));

	_rrsStatsSaveDataLS& statData = ObjectWrap::Unwrap<StatsSaveDataLS>(args.This())->svStatData;
	bool success = statData.loadFromFile(*v8::String::Utf8Value(args[0]->ToString()));

	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void StatsSaveDataLS::getError(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrsStatsSaveDataLS& statData = ObjectWrap::Unwrap<StatsSaveDataLS>(args.This())->svStatData;
	args.GetReturnValue().Set(String::NewFromUtf8(
		isolate,
		statData.getError().toUtf8().data(),
		String::kInternalizedString)
		);
}

void StatsSaveDataLS::currentLocalTime(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrsStatsSaveDataLS& statData = ObjectWrap::Unwrap<StatsSaveDataLS>(args.This())->svStatData;
	args.GetReturnValue().Set(Int32::New(isolate, statData.currentLocalTime()));
}

void StatsSaveDataLS::day(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(day, Int32, ARGSDESCR(idx));

	_rrsStatsSaveDataLS& statData = ObjectWrap::Unwrap<StatsSaveDataLS>(args.This())->svStatData;
	args.GetReturnValue().Set(StatsType::fromRRStatType(statData.day_Get(args[0]->ToInt32()->Value())));
}

void StatsSaveDataLS::dayMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrsStatsSaveDataLS& statData = ObjectWrap::Unwrap<StatsSaveDataLS>(args.This())->svStatData;
	args.GetReturnValue().Set(Int32::New(isolate, statData.day_Max()));
}

void StatsSaveDataLS::month(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(month, Int32, ARGSDESCR(idx));

	_rrsStatsSaveDataLS& statData = ObjectWrap::Unwrap<StatsSaveDataLS>(args.This())->svStatData;
	args.GetReturnValue().Set(StatsType::fromRRStatType(statData.month_Get(args[0]->ToInt32()->Value())));
}

void StatsSaveDataLS::monthMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrsStatsSaveDataLS& statData = ObjectWrap::Unwrap<StatsSaveDataLS>(args.This())->svStatData;
	args.GetReturnValue().Set(Int32::New(isolate, statData.month_Max()));
}

void StatsSaveDataLS::year(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(year, Int32, ARGSDESCR(idx));

	_rrsStatsSaveDataLS& statData = ObjectWrap::Unwrap<StatsSaveDataLS>(args.This())->svStatData;
	args.GetReturnValue().Set(StatsType::fromRRStatType(statData.year_Get(args[0]->ToInt32()->Value())));
}

void StatsSaveDataLS::yearMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrsStatsSaveDataLS& statData = ObjectWrap::Unwrap<StatsSaveDataLS>(args.This())->svStatData;
	args.GetReturnValue().Set(Int32::New(isolate, statData.year_Max()));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(StatsSaveDataLS,
	NODE_SET_PROTOTYPE_METHOD(tpl, "loadFromFile", loadFromFile);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getError", getError);
	NODE_SET_PROTOTYPE_METHOD(tpl, "currentLocalTime", currentLocalTime);

	NODE_SET_PROTOTYPE_METHOD(tpl, "day", day);
	NODE_SET_PROTOTYPE_METHOD(tpl, "dayMax", dayMax);
	NODE_SET_PROTOTYPE_METHOD(tpl, "month", month);
	NODE_SET_PROTOTYPE_METHOD(tpl, "monthMax", monthMax);
	NODE_SET_PROTOTYPE_METHOD(tpl, "year", year);
    NODE_SET_PROTOTYPE_METHOD(tpl, "yearMax", yearMax);
    ,	)


// StatsType
//---------- CONSTRUCTION
Persistent<Function> StatsType::constructor;

void StatsType::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	StatsType *newStatType = new StatsType();
	newStatType->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "slot_used", v8::String::kInternalizedString), getSlot_used);
	self->SetAccessor(String::NewFromUtf8(isolate, "clients_needed", v8::String::kInternalizedString), getClients_needed);
	self->SetAccessor(String::NewFromUtf8(isolate, "framesPer90s", v8::String::kInternalizedString), getFramesPer90s);
	self->SetAccessor(String::NewFromUtf8(isolate, "clients_free", v8::String::kInternalizedString), getClients_free);
	self->SetAccessor(String::NewFromUtf8(isolate, "client_rendering", v8::String::kInternalizedString), getClient_rendering);
	self->SetAccessor(String::NewFromUtf8(isolate, "clients_disabled", v8::String::kInternalizedString), getClients_disabled);
	self->SetAccessor(String::NewFromUtf8(isolate, "cpuProcess", v8::String::kInternalizedString), getCpuProcess);
	self->SetAccessor(String::NewFromUtf8(isolate, "cpuMachine", v8::String::kInternalizedString), getCpuMachine);
	self->SetAccessor(String::NewFromUtf8(isolate, "serverTemperature", v8::String::kInternalizedString), getServerTemperature);
	self->SetAccessor(String::NewFromUtf8(isolate, "avclientTemperature", v8::String::kInternalizedString), getAvclientTemperature);
	self->SetAccessor(String::NewFromUtf8(isolate, "jobs_unfinished", v8::String::kInternalizedString), getJobs_unfinished);
	self->SetAccessor(String::NewFromUtf8(isolate, "jobs_rendering", v8::String::kInternalizedString), getJobs_rendering);
	self->SetAccessor(String::NewFromUtf8(isolate, "jobs_total", v8::String::kInternalizedString), getJobs_total);
	self->SetAccessor(String::NewFromUtf8(isolate, "memUsageMachine", v8::String::kInternalizedString), getMemUsageMachine);
	self->SetAccessor(String::NewFromUtf8(isolate, "memUsageProcess", v8::String::kInternalizedString), getMemUsageProcess);
	self->SetAccessor(String::NewFromUtf8(isolate, "tCPMemUsageSocket", v8::String::kInternalizedString), getTCPMemUsageSocket);
	self->SetAccessor(String::NewFromUtf8(isolate, "tCPMemUsageData", v8::String::kInternalizedString), getTCPMemUsageData);
	self->SetAccessor(String::NewFromUtf8(isolate, "jobBufferMemUsageJobs", v8::String::kInternalizedString), getJobBufferMemUsageJobs);
	self->SetAccessor(String::NewFromUtf8(isolate, "tCPMemUsageDataCompressed", v8::String::kInternalizedString), getTCPMemUsageDataCompressed);
	self->SetAccessor(String::NewFromUtf8(isolate, "av_frame_time", v8::String::kInternalizedString), getAv_frame_time);
	self->SetAccessor(String::NewFromUtf8(isolate, "frames_to_do", v8::String::kInternalizedString), getFrames_to_do);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__statstype__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void StatsType::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

Handle<Value> StatsType::fromRRStatType(_rrsStats_type rr_stat_type)
{
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	StatsType* stat_type = ObjectWrap::Unwrap<StatsType>(instance);
	stat_type->statType = rr_stat_type;

	return instance;
}

StatsType::StatsType(void) : statType()
{}

StatsType::~StatsType(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool StatsType::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__statstype__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- ACCESSORS
void StatsType::getSlot_used(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(statData.slot_used ? v8::True(isolate) : v8::False(isolate));
}

void StatsType::getClients_needed(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Number::New(isolate, statData.clients_needed));
}

void StatsType::getFramesPer90s(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Number::New(isolate, statData.framesPer90s));
}

void StatsType::getClients_free(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.clients_free));
}

void StatsType::getClient_rendering(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.client_rendering));
}

void StatsType::getClients_disabled(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.clients_disabled));
}

void StatsType::getCpuProcess(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.CpuProcess));
}

void StatsType::getCpuMachine(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.CpuMachine));
}

void StatsType::getServerTemperature(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.serverTemperature));
}

void StatsType::getAvclientTemperature(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.avclientTemperature));
}

void StatsType::getJobs_unfinished(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.jobs_unfinished));
}

void StatsType::getJobs_rendering(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.jobs_rendering));
}

void StatsType::getJobs_total(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.jobs_total));
}

void StatsType::getMemUsageMachine(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.MemUsageMachine));
}

void StatsType::getMemUsageProcess(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.MemUsageProcess));
}

void StatsType::getTCPMemUsageSocket(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.TCPMemUsageSocket));
}

void StatsType::getTCPMemUsageData(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.TCPMemUsageData));
}

void StatsType::getJobBufferMemUsageJobs(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.JobBufferMemUsageJobs));
}

void StatsType::getTCPMemUsageDataCompressed(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.TCPMemUsageDataCompressed));
}

void StatsType::getAv_frame_time(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.av_frame_time));
}

void StatsType::getFrames_to_do(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const _rrsStats_type& statData = ObjectWrap::Unwrap<StatsType>(info.Holder())->statType;
	info.GetReturnValue().Set(Uint32::New(isolate, statData.frames_to_do));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(StatsType, , )


// ClientStatsData
//---------- CONSTRUCTION
Persistent<Function> ClientStatsData::constructor;

void ClientStatsData::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	ClientStatsData *clientStats = new ClientStatsData();
	clientStats->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "StructureID", v8::String::kInternalizedString), getStructureID);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__clientstatsdata__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void ClientStatsData::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

ClientStatsData::ClientStatsData(void) : clStats()
{}

ClientStatsData::~ClientStatsData(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ClientStatsData::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__clientstatsdata__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- ACCESSORS
void ClientStatsData::getStructureID(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_data& cl_stat = ObjectWrap::Unwrap<ClientStatsData>(info.Holder())->clStats;
	info.GetReturnValue().Set(v8::Uint32::New(isolate, cl_stat.StructureID));
}

//---------- NODE METHODS
void ClientStatsData::days(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(days, Int32, ARGSDESCR(idx))

	_rrClientStats_data& _clStat = ObjectWrap::Unwrap<ClientStatsData>(args.This())->clStats;
	args.GetReturnValue().Set(ClientStatsDay::fromRRClientStatDay(_clStat.days[args[0]->ToInt32()->Value()]));
}

void ClientStatsData::daysMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_data& _clStat = ObjectWrap::Unwrap<ClientStatsData>(args.This())->clStats;
	args.GetReturnValue().Set(Int32::New(isolate, _clStat.days_Max()));
}

void ClientStatsData::loadFromFile(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_data& _clStat = ObjectWrap::Unwrap<ClientStatsData>(args.This())->clStats;

	CHECKARGS_1(loadFromFile, String, ARGSDESCR(filename, [failifnofile]));
	bool success = _clStat.loadFromFile(*v8::String::Utf8Value(args[0]->ToString()));

	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void ClientStatsData::getError(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_data& _clStat = ObjectWrap::Unwrap<ClientStatsData>(args.This())->clStats;

	args.GetReturnValue().Set(String::NewFromUtf8(isolate,
		_clStat.getError().toUtf8().data(),
		String::kInternalizedString));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(ClientStatsData,
	NODE_SET_PROTOTYPE_METHOD(tpl, "days", days);
	NODE_SET_PROTOTYPE_METHOD(tpl, "daysMax", daysMax);
	NODE_SET_PROTOTYPE_METHOD(tpl, "loadFromFile", loadFromFile);
    NODE_SET_PROTOTYPE_METHOD(tpl, "getError", getError);
    ,	)


// ClientStatsDay
//---------- CONSTRUCTION
Persistent<Function> ClientStatsDay::constructor;

void ClientStatsDay::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	ClientStatsDay *clientStats = new ClientStatsDay();
	clientStats->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "daySet", v8::String::kInternalizedString), getDaySet);
	self->SetAccessor(String::NewFromUtf8(isolate, "day", v8::String::kInternalizedString), getDay);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__clientstatsday__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void ClientStatsDay::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

Handle<Value> ClientStatsDay::fromRRClientStatDay(_rrClientStats_day rr_stat_day)
{
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	ClientStatsDay* StatsDay = ObjectWrap::Unwrap<ClientStatsDay>(instance);
	StatsDay->clStats = rr_stat_day;

	return instance;
}

ClientStatsDay::ClientStatsDay(void) : clStats()
{}

ClientStatsDay::~ClientStatsDay(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ClientStatsDay::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__clientstatsday__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- ACCESSORS
void ClientStatsDay::getDaySet(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDay>(info.Holder())->clStats;
	info.GetReturnValue().Set(cl_stat_day.daySet ? v8::True(isolate) : v8::False(isolate));
}

void ClientStatsDay::getDay(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDay>(info.Holder())->clStats;
	info.GetReturnValue().Set(Int32::New(isolate, cl_stat_day.day));
}

//---------- NODE METHODS
void ClientStatsDay::data(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(data, Int32, ARGSDESCR(idx))

	_rrClientStats_day& _clStat = ObjectWrap::Unwrap<ClientStatsDay>(args.This())->clStats;
	args.GetReturnValue().Set(ClientStatsDayData::fromClientDayData(_clStat.data_Get(args[0]->ToInt32()->Value())));
}

void ClientStatsDay::dataMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day& _clStat = ObjectWrap::Unwrap<ClientStatsDay>(args.This())->clStats;
	args.GetReturnValue().Set(Int32::New(isolate, _clStat.data_Max()));
}

void ClientStatsDay::dataHourly(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(dataHourly, Int32, ARGSDESCR(idx))

	_rrClientStats_day& _clStat = ObjectWrap::Unwrap<ClientStatsDay>(args.This())->clStats;
	_clStat.data;
	args.GetReturnValue().Set(ClientStatsDayDataHourly::fromRRClientStatDayDataHourly(_clStat.dataHourly_Get(args[0]->ToInt32()->Value())));
}

void ClientStatsDay::dataHourlyMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day& _clStat = ObjectWrap::Unwrap<ClientStatsDay>(args.This())->clStats;
	args.GetReturnValue().Set(Int32::New(isolate, _clStat.dataHourly_Max()));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(ClientStatsDay,
	NODE_SET_PROTOTYPE_METHOD(tpl, "data", data);
	NODE_SET_PROTOTYPE_METHOD(tpl, "dataMax", dataMax);
	NODE_SET_PROTOTYPE_METHOD(tpl, "dataHourly", dataHourly);
    NODE_SET_PROTOTYPE_METHOD(tpl, "dataHourlyMax", dataHourlyMax);
    ,	)


// ClientStatsDayDataHourly
//---------- CONSTRUCTION
Persistent<Function> ClientStatsDayDataHourly::constructor;

void ClientStatsDayDataHourly::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	ClientStatsDayDataHourly *clientStats = new ClientStatsDayDataHourly();
	clientStats->Wrap(self);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__clientstatsdaydatahourly__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void ClientStatsDayDataHourly::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

Handle<Value> ClientStatsDayDataHourly::fromRRClientStatDayDataHourly(_rrClientStats_day_data_hourly rr_stat_day)
{
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	ClientStatsDayDataHourly* StatsDay = ObjectWrap::Unwrap<ClientStatsDayDataHourly>(instance);
	StatsDay->clStats = rr_stat_day;

	return instance;
}

ClientStatsDayDataHourly::ClientStatsDayDataHourly(void) : clStats()
{}

ClientStatsDayDataHourly::~ClientStatsDayDataHourly(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ClientStatsDayDataHourly::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__clientstatsdaydatahourly__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- NODE METHODS
void ClientStatsDayDataHourly::jobThread(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(jobThread, Int32, ARGSDESCR(idx))

	_rrClientStats_day_data_hourly& _clStat = ObjectWrap::Unwrap<ClientStatsDayDataHourly>(args.This())->clStats;
	args.GetReturnValue().Set(ClientStatsDayDataHourlyJobThread::fromClientStatsDayDataHJobthread(_clStat.jobThread_Get(args[0]->ToInt32()->Value())));
}

void ClientStatsDayDataHourly::jobThreadMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day_data_hourly& _clStat = ObjectWrap::Unwrap<ClientStatsDayDataHourly>(args.This())->clStats;
	args.GetReturnValue().Set(Int32::New(isolate, _clStat.jobThread_Max()));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(ClientStatsDayDataHourly,
	NODE_SET_PROTOTYPE_METHOD(tpl, "jobThread", jobThread);
    NODE_SET_PROTOTYPE_METHOD(tpl, "jobThreadMax", jobThreadMax);
    ,	)


// ClientStatsDayDataHourlyJobThread
//---------- CONSTRUCTION
Persistent<Function> ClientStatsDayDataHourlyJobThread::constructor;

void ClientStatsDayDataHourlyJobThread::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	ClientStatsDayDataHourlyJobThread *clientStats = new ClientStatsDayDataHourlyJobThread();
	clientStats->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "framesDone", v8::String::kInternalizedString), getFramesDone);
	self->SetAccessor(String::NewFromUtf8(isolate, "jobCrashed", v8::String::kInternalizedString), getJobCrashed);
	self->SetAccessor(String::NewFromUtf8(isolate, "jobAborted", v8::String::kInternalizedString), getJobAborted);
	self->SetAccessor(String::NewFromUtf8(isolate, "jobSuccessful", v8::String::kInternalizedString), getJobSuccessful);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__clientstatsdatahourlyjobthread__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void ClientStatsDayDataHourlyJobThread::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

Handle<Value> ClientStatsDayDataHourlyJobThread::fromClientStatsDayDataHJobthread(_rrClientStats_day_data_hourly_jobthread stat_dd_jobthr)
{
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	ClientStatsDayDataHourlyJobThread* client_stat = ObjectWrap::Unwrap<ClientStatsDayDataHourlyJobThread>(instance);
	client_stat->clStats = stat_dd_jobthr;

	return instance;
}

ClientStatsDayDataHourlyJobThread::ClientStatsDayDataHourlyJobThread(void) : clStats()
{}

ClientStatsDayDataHourlyJobThread::~ClientStatsDayDataHourlyJobThread(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ClientStatsDayDataHourlyJobThread::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__clientstatsdatahourlyjobthread__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- ACCESSORS
void ClientStatsDayDataHourlyJobThread::getFramesDone(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day_data_hourly_jobthread& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDayDataHourlyJobThread>(info.Holder())->clStats;
	info.GetReturnValue().Set(Uint32::New(isolate, cl_stat_day.framesDone));
}

void ClientStatsDayDataHourlyJobThread::getJobAborted(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day_data_hourly_jobthread& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDayDataHourlyJobThread>(info.Holder())->clStats;
	info.GetReturnValue().Set(Int32::New(isolate, cl_stat_day.jobAborted));
}

void ClientStatsDayDataHourlyJobThread::getJobCrashed(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day_data_hourly_jobthread& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDayDataHourlyJobThread>(info.Holder())->clStats;
	info.GetReturnValue().Set(Int32::New(isolate, cl_stat_day.jobCrashed));
}

void ClientStatsDayDataHourlyJobThread::getJobSuccessful(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day_data_hourly_jobthread& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDayDataHourlyJobThread>(info.Holder())->clStats;
	info.GetReturnValue().Set(Int32::New(isolate, cl_stat_day.jobSuccessful));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(ClientStatsDayDataHourlyJobThread, , )


// ClientStatsDayData
//---------- CONSTRUCTION
Persistent<Function> ClientStatsDayData::constructor;

void ClientStatsDayData::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	ClientStatsDayData *clientStats = new ClientStatsDayData();
	clientStats->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "userLoggedIn", v8::String::kInternalizedString), getUserLoggedIn);
	self->SetAccessor(String::NewFromUtf8(isolate, "cpuTotal", v8::String::kInternalizedString), getCpuTotal);
	self->SetAccessor(String::NewFromUtf8(isolate, "memTotal10MB", v8::String::kInternalizedString), getMemTotal10MB);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__clientstatsdata__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void ClientStatsDayData::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

Handle<Value> ClientStatsDayData::fromClientDayData(_rrClientStats_day_data cl_statday_data)
{
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	ClientStatsDayData* client_stat = ObjectWrap::Unwrap<ClientStatsDayData>(instance);
	client_stat->clStats = cl_statday_data;

	return instance;
}

ClientStatsDayData::ClientStatsDayData(void) : clStats()
{}

ClientStatsDayData::~ClientStatsDayData(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ClientStatsDayData::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__clientstatsdata__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- ACCESSORS
void ClientStatsDayData::getUserLoggedIn(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day_data& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDayData>(info.Holder())->clStats;
	info.GetReturnValue().Set(cl_stat_day.userLoggedIn ? v8::True(isolate) : v8::False(isolate));
}

void ClientStatsDayData::getMemTotal10MB(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day_data& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDayData>(info.Holder())->clStats;
	info.GetReturnValue().Set(Uint32::New(isolate, cl_stat_day.memTotal10MB));
}

void ClientStatsDayData::getCpuTotal(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day_data& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDayData>(info.Holder())->clStats;
	// XXX: returning a 0.0-100.0 float like in pyhon module, rather then a rr_percent wrapper
	info.GetReturnValue().Set(Number::New(isolate, cl_stat_day.cpuTotal.toFperc()));
}

//---------- NODE METHODS
void ClientStatsDayData::jobThreadMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day_data& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDayData>(args.This())->clStats;

	args.GetReturnValue().Set(Int32::New(isolate, cl_stat_day.jobThread_Max()));
}

void ClientStatsDayData::jobThread(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(jobThread, Int32, ARGSDESCR(idx))

	_rrClientStats_day_data& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDayData>(args.This())->clStats;
	Handle<v8::Value> cl_stat_thread = ClientStatsDayDataJobthread::fromClientStatsDayDataJobthread(cl_stat_day.jobThread_Get(args[0]->ToInt32()->Value()));

	args.GetReturnValue().Set(cl_stat_thread);
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(ClientStatsDayData,
	NODE_SET_PROTOTYPE_METHOD(tpl, "jobThread", jobThread);
    NODE_SET_PROTOTYPE_METHOD(tpl, "jobThreadMax", jobThreadMax);
    ,	)


// ClientStatsDayDataJobthread
//---------- CONSTRUCTION
Persistent<Function> ClientStatsDayDataJobthread::constructor;

void ClientStatsDayDataJobthread::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	ClientStatsDayDataJobthread *clientStats = new ClientStatsDayDataJobthread();
	clientStats->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "status", v8::String::kInternalizedString), getStatus);
	self->SetAccessor(String::NewFromUtf8(isolate, "cpuRender", v8::String::kInternalizedString), getCpuRender);
	self->SetAccessor(String::NewFromUtf8(isolate, "memRender10MB", v8::String::kInternalizedString), getMemRender10MB);
	self->SetAccessor(String::NewFromUtf8(isolate, "jobIDShort", v8::String::kInternalizedString), getJobIDShort);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__clientstatsdaydatajobthread__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void ClientStatsDayDataJobthread::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

Handle<Value> ClientStatsDayDataJobthread::fromClientStatsDayDataJobthread(_rrClientStats_day_data_jobthread stat_dd_jobthr)
{
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	ClientStatsDayDataJobthread* client_stat = ObjectWrap::Unwrap<ClientStatsDayDataJobthread>(instance);
	client_stat->clStats = stat_dd_jobthr;

	return instance;
}

ClientStatsDayDataJobthread::ClientStatsDayDataJobthread(void) : clStats()
{}

ClientStatsDayDataJobthread::~ClientStatsDayDataJobthread(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ClientStatsDayDataJobthread::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__clientstatsdaydatajobthread__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- ACCESSORS
void ClientStatsDayDataJobthread::getStatus(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day_data_jobthread& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDayDataJobthread>(info.Holder())->clStats;
	info.GetReturnValue().Set(Int32::New(isolate, cl_stat_day.status));
}

void ClientStatsDayDataJobthread::getCpuRender(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day_data_jobthread& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDayDataJobthread>(info.Holder())->clStats;
	info.GetReturnValue().Set(Number::New(isolate, cl_stat_day.cpuRender.toFperc()));
}

void ClientStatsDayDataJobthread::getMemRender10MB(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day_data_jobthread& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDayDataJobthread>(info.Holder())->clStats;

	info.GetReturnValue().Set(Uint32::New(isolate, cl_stat_day.memRender10MB));
}

void ClientStatsDayDataJobthread::getJobIDShort(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day_data_jobthread& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDayDataJobthread>(info.Holder())->clStats;

	info.GetReturnValue().Set(Uint32::New(isolate, cl_stat_day.jobIDShort));
}

//---------- NODE METHODS
void ClientStatsDayDataJobthread::jobIDShortStr(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_rrClientStats_day_data_jobthread& cl_stat_day = ObjectWrap::Unwrap<ClientStatsDayDataJobthread>(args.This())->clStats;

	args.GetReturnValue().Set(String::NewFromUtf8(isolate,
		cl_stat_day.jobIDShortStr().toUtf8().data(),
		String::kInternalizedString));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(ClientStatsDayDataJobthread,
    NODE_SET_PROTOTYPE_METHOD(tpl, "jobIDShortStr", jobIDShortStr);
    ,	)


// FrameStatJob
//---------- CONSTRUCTION
Persistent<Function> FrameStatJob::constructor;

void FrameStatJob::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	FrameStatJob *frameStatJob = new FrameStatJob();
	frameStatJob->Wrap(self);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__framestatjob__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void FrameStatJob::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

FrameStatJob::FrameStatJob(void) : frmStat()
{}

FrameStatJob::~FrameStatJob(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FrameStatJob::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__framestatjob__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}


//---------- NODE METHODS
void FrameStatJob::loadFromFile(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(loadFromFile, String, ARGSDESCR(FileName))

	_frameStatJob& frm_stat_job = ObjectWrap::Unwrap<FrameStatJob>(args.This())->frmStat;
	const bool success = frm_stat_job._python_loadFromFile(QString::fromUtf8(*v8::String::Utf8Value(args[0]->ToString())));
	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void FrameStatJob::getError(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_frameStatJob& frm_stat_job = ObjectWrap::Unwrap<FrameStatJob>(args.This())->frmStat;

	args.GetReturnValue().Set(String::NewFromUtf8(isolate,
		frm_stat_job.getError().toUtf8().data(),
		String::kInternalizedString));
}

void FrameStatJob::frameMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_frameStatJob& frm_stat_job = ObjectWrap::Unwrap<FrameStatJob>(args.This())->frmStat;
	args.GetReturnValue().Set(Int32::New(isolate, frm_stat_job._frames_Max()));
}

void FrameStatJob::frame(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(frame, Int32, ARGSDESCR(frame))

	_frameStatJob& frm_stat_job = ObjectWrap::Unwrap<FrameStatJob>(args.This())->frmStat;
	v8::Handle<v8::Value> frm_stat = FrameStat::fromFrameStat(frm_stat_job._frames_Get(args[0]->ToInt32()->Value()));
	args.GetReturnValue().Set(frm_stat);
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(FrameStatJob,
	NODE_SET_PROTOTYPE_METHOD(tpl, "loadFromFile", loadFromFile);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getError", getError);
	NODE_SET_PROTOTYPE_METHOD(tpl, "frameMax", frameMax);
    NODE_SET_PROTOTYPE_METHOD(tpl, "frame", frame);
    , )


// FrameStat
//---------- CONSTRUCTION
Persistent<Function> FrameStat::constructor;

void FrameStat::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	FrameStat *frameStat = new FrameStat();
	frameStat->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "logFileStart", v8::String::kInternalizedString), getLogFileStart);
	self->SetAccessor(String::NewFromUtf8(isolate, "logFileStartFrame", v8::String::kInternalizedString), getLogFileStartFrame);
	self->SetAccessor(String::NewFromUtf8(isolate, "renderTime5Sec", v8::String::kInternalizedString), getRenderTime5Sec);
	self->SetAccessor(String::NewFromUtf8(isolate, "frameNrJob", v8::String::kInternalizedString), getFrameNrJob);
	self->SetAccessor(String::NewFromUtf8(isolate, "client", v8::String::kInternalizedString), getClient);
	self->SetAccessor(String::NewFromUtf8(isolate, "averageValue", v8::String::kInternalizedString), getAverageValue);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__framestat__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void FrameStat::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

Handle<Value> FrameStat::fromFrameStat(_frameStat _frm_stat)
{
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	FrameStat* frm_stat = ObjectWrap::Unwrap<FrameStat>(instance);
	frm_stat->frmStat = _frm_stat;

	return instance;
}

FrameStat::FrameStat(void) : frmStat()
{}

FrameStat::~FrameStat(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FrameStat::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__framestat__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- ACCESSORS
void FrameStat::getLogFileStart(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_frameStat& frm_stat = ObjectWrap::Unwrap<FrameStat>(info.Holder())->frmStat;

	info.GetReturnValue().Set(v8::Date::New(isolate, _rrTime(frm_stat.logFileStart).toLocalTime() * 1000));
}

void FrameStat::getLogFileStartFrame(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_frameStat& frm_stat = ObjectWrap::Unwrap<FrameStat>(info.Holder())->frmStat;
	info.GetReturnValue().Set(Uint32::New(isolate, frm_stat.logFileStartFrame));
}

void FrameStat::getRenderTime5Sec(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_frameStat& frm_stat = ObjectWrap::Unwrap<FrameStat>(info.Holder())->frmStat;
	info.GetReturnValue().Set(Uint32::New(isolate, frm_stat.renderTime5Sec));
}

void FrameStat::getFrameNrJob(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_frameStat& frm_stat = ObjectWrap::Unwrap<FrameStat>(info.Holder())->frmStat;
	info.GetReturnValue().Set(Uint32::New(isolate, frm_stat.frameNrJob));
}

void FrameStat::getAverageValue(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_frameStat& frm_stat = ObjectWrap::Unwrap<FrameStat>(info.Holder())->frmStat;
	info.GetReturnValue().Set(Uint32::New(isolate, frm_stat.averageValue));
}

void FrameStat::getClient(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_frameStat& frm_stat = ObjectWrap::Unwrap<FrameStat>(info.Holder())->frmStat;

	v8::Local<v8::String> clname = v8::String::NewFromUtf8(isolate,
		std::string(frm_stat.client.value,
		frm_stat.client.length).c_str(),
		v8::String::kInternalizedString);

	
	info.GetReturnValue().Set(clname);
}

//---------- NODE METHODS
void FrameStat::partMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_frameStat& frm_stat = ObjectWrap::Unwrap<FrameStat>(args.This())->frmStat;
	args.GetReturnValue().Set(Int32::New(isolate, frm_stat._part_Max()));
}

void FrameStat::part(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(part, Int32, ARGSDESCR(idx))

	_frameStat& frm_stat = ObjectWrap::Unwrap<FrameStat>(args.This())->frmStat;
	args.GetReturnValue().Set(FrameStatPart::fromFrameStatPart(frm_stat._part_Get(args[0]->ToInt32()->Value())));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(FrameStat,
	NODE_SET_PROTOTYPE_METHOD(tpl, "part", part);
    NODE_SET_PROTOTYPE_METHOD(tpl, "partMax", partMax);
    ,   )


// FrameStatPart
//---------- CONSTRUCTION
Persistent<Function> FrameStatPart::constructor;

void FrameStatPart::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	FrameStatPart *frameStat = new FrameStatPart();
	frameStat->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "jobMemoryMB", v8::String::kInternalizedString), getJobMemoryMB);
	self->SetAccessor(String::NewFromUtf8(isolate, "jobCPU", v8::String::kInternalizedString), getJobCPU);
	self->SetAccessor(String::NewFromUtf8(isolate, "nonJobCPU", v8::String::kInternalizedString), getNonJobCPU);
	self->SetAccessor(String::NewFromUtf8(isolate, "renderThreads", v8::String::kInternalizedString), getRenderThreads);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__framestatpart__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void FrameStatPart::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

Handle<Value> FrameStatPart::fromFrameStatPart(_frameStat_part _stat_part)
{
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	FrameStatPart* frm_stat = FrameStatPart::Unwrap<FrameStatPart>(instance);
	frm_stat->frmStat = _stat_part;

	return instance;
}

FrameStatPart::FrameStatPart(void) : frmStat()
{}

FrameStatPart::~FrameStatPart(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FrameStatPart::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__framestatpart__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- ACCESSORS
void FrameStatPart::getJobMemoryMB(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_frameStat_part& frm_stat = ObjectWrap::Unwrap<FrameStatPart>(info.Holder())->frmStat;

	info.GetReturnValue().Set(Uint32::New(isolate, frm_stat.jobMemoryMB));
}

void FrameStatPart::getJobCPU(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_frameStat_part& frm_stat = ObjectWrap::Unwrap<FrameStatPart>(info.Holder())->frmStat;
	// XXX: returning a 0.0-100.0 float like in pyhon module, rather then a rr_percent wrapper
	info.GetReturnValue().Set(Number::New(isolate, frm_stat.jobCPU.toFperc()));
}

void FrameStatPart::getNonJobCPU(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_frameStat_part& frm_stat = ObjectWrap::Unwrap<FrameStatPart>(info.Holder())->frmStat;
	// XXX: returning a 0.0-100.0 float like in pyhon module, rather then a rr_percent wrapper
	info.GetReturnValue().Set(Number::New(isolate, frm_stat.nonJobCPU.toFperc()));
}

void FrameStatPart::getRenderThreads(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_frameStat_part& frm_stat = ObjectWrap::Unwrap<FrameStatPart>(info.Holder())->frmStat;

	info.GetReturnValue().Set(Uint32::New(isolate, frm_stat.renderThreads));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(FrameStatPart, , )


// DailyStatsData
//---------- CONSTRUCTION
Persistent<Function> DailyStatsData::constructor;

void DailyStatsData::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	DailyStatsData *dailyStats = new DailyStatsData();
	dailyStats->Wrap(self);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__dailystatsdata__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void DailyStatsData::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

DailyStatsData::DailyStatsData(void) : dsData()
{}

DailyStatsData::~DailyStatsData(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool DailyStatsData::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__dailystatsdata__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- NODE METHODS
void DailyStatsData::singleStats(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(singleStats, Int32, ARGSDESCR(id))

	DailyStatsData* dStats = ObjectWrap::Unwrap<DailyStatsData>(args.This());
	const list_singleStatDay& stat_lst = dStats->dsData._singleStats_Get(args[0]->ToInt32()->Value());
	int num_stats = stat_lst.length();

	Local<Array> stat_arr = Array::New(isolate, num_stats);
	for (int i = 0; i < num_stats; ++i) {
        stat_arr->Set(i, SingleStatDay::fromSingleStatDay(stat_lst.value(i)));
	}
	args.GetReturnValue().Set(stat_arr);
}

void DailyStatsData::singleStatsMax(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	DailyStatsData* dStats = ObjectWrap::Unwrap<DailyStatsData>(args.This());
	args.GetReturnValue().Set(Int32::New(isolate, dStats->dsData._singleStats_Max()));
}

void DailyStatsData::loadFromFile(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	bool success = false;
	DailyStatsData* dStats = ObjectWrap::Unwrap<DailyStatsData>(args.This());
	if (args.Length() == 1) {
		CHECKARGS_1(loadFromFile, String, ARGSDESCR(filename, [failifnofile]));
		success = dStats->dsData.loadFromFile(*v8::String::Utf8Value(args[0]->ToString()));
	}
	else {
		CHECKARGS_2(loadFromFile, String, Boolean, ARGSDESCR(filename, [failifnofile]));
		success = dStats->dsData.loadFromFile(*v8::String::Utf8Value(args[0]->ToString()), args[1]->ToBoolean()->Value());
	}
	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void DailyStatsData::getError(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_dailyStats_data& dStats = ObjectWrap::Unwrap<DailyStatsData>(args.This())->dsData;
	args.GetReturnValue().Set(String::NewFromUtf8(isolate,
												dStats.getError().toUtf8().data(),
												String::kInternalizedString));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(DailyStatsData,
	NODE_SET_PROTOTYPE_METHOD(tpl, "singleStats", singleStats);
	NODE_SET_PROTOTYPE_METHOD(tpl, "singleStatsMax", singleStatsMax);
	NODE_SET_PROTOTYPE_METHOD(tpl, "loadFromFile", loadFromFile);
    NODE_SET_PROTOTYPE_METHOD(tpl, "getError", getError);
    , )


// StatsRenderTime
//---------- CONSTRUCTION
Persistent<Function> StatsRenderTime::constructor;

void StatsRenderTime::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	StatsRenderTime *statrender = new StatsRenderTime();
	statrender->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "prjCount", v8::String::kInternalizedString), getCount, setCount);
	self->SetAccessor(String::NewFromUtf8(isolate, "lastSaved", v8::String::kInternalizedString), getLastSaved);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__statrendertime__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void StatsRenderTime::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

StatsRenderTime::StatsRenderTime(void) : statsRndTime()
{}

StatsRenderTime::~StatsRenderTime(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool StatsRenderTime::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__statrendertime__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- ACCESSORS
void StatsRenderTime::getCount(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_StatsRenderTime& stat_rnd = ObjectWrap::Unwrap<StatsRenderTime>(info.Holder())->statsRndTime;
	info.GetReturnValue().Set(v8::Int32::New(isolate, stat_rnd.prjCount));
}

void StatsRenderTime::setCount(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	CHECKVAL(count, Int32, "(number of groups)")

	_StatsRenderTime& stat_rnd = ObjectWrap::Unwrap<StatsRenderTime>(info.Holder())->statsRndTime;
	stat_rnd.prjCount = value->ToInt32()->Value();
}

void StatsRenderTime::getLastSaved(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_StatsRenderTime& stat_rnd = ObjectWrap::Unwrap<StatsRenderTime>(info.Holder())->statsRndTime;
	info.GetReturnValue().Set(v8::Date::New(isolate, stat_rnd.lastSaved.toLocalTime() * 1000));
}

//---------- NODE METHODS
void StatsRenderTime::getProject(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(getProject, Int32, ARGSDESCR(idx))

	_StatsRenderTime& stat_rnd = ObjectWrap::Unwrap<StatsRenderTime>(args.This())->statsRndTime;
	Handle<Value> stat_rnd_prj = StatsRenderTimeProject::fromStatRenderTimeProject(stat_rnd.getProject(args[0]->ToInt32()->Value()));
	args.GetReturnValue().Set(stat_rnd_prj);
}

void StatsRenderTime::loadFile(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(loadFile, String, ARGSDESCR(filename, [failifnofile]));

	_StatsRenderTime& stat_rnd = ObjectWrap::Unwrap<StatsRenderTime>(args.This())->statsRndTime;
	bool success = stat_rnd.loadFile(*v8::String::Utf8Value(args[0]->ToString()));

	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void StatsRenderTime::saveFile(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(saveFile, String, ARGSDESCR(filename, [failifnofile]));

	_StatsRenderTime& stat_rnd = ObjectWrap::Unwrap<StatsRenderTime>(args.This())->statsRndTime;
	bool success = stat_rnd.saveFile(*v8::String::Utf8Value(args[0]->ToString()));

	args.GetReturnValue().Set(success ? v8::True(isolate) : v8::False(isolate));
}

void StatsRenderTime::getError(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_StatsRenderTime& stat_rnd = ObjectWrap::Unwrap<StatsRenderTime>(args.This())->statsRndTime;

	args.GetReturnValue().Set(String::NewFromUtf8(isolate,
		stat_rnd.getErrorString().toUtf8().data(),
		v8::String::kInternalizedString));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(StatsRenderTime,
	NODE_SET_PROTOTYPE_METHOD(tpl, "getProject", getProject);
	NODE_SET_PROTOTYPE_METHOD(tpl, "loadFile", loadFile);
	NODE_SET_PROTOTYPE_METHOD(tpl, "saveFile", saveFile);
    NODE_SET_PROTOTYPE_METHOD(tpl, "getError", getError);
    ,	)


// StatsRenderTimeProject
//---------- CONSTRUCTION
Persistent<Function> StatsRenderTimeProject::constructor;

void StatsRenderTimeProject::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	StatsRenderTimeProject *statrender = new StatsRenderTimeProject();
	statrender->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "lastUsed", v8::String::kInternalizedString), getLastUsed);
	self->SetAccessor(String::NewFromUtf8(isolate, "name", v8::String::kInternalizedString), getName);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__statrendertimeproject__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void StatsRenderTimeProject::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

Handle<Value> StatsRenderTimeProject::fromStatRenderTimeProject(_StatsRenderTime_project _stat_rnd)
{
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	StatsRenderTimeProject* stat_rnd = StatsRenderTimeProject::Unwrap<StatsRenderTimeProject>(instance);
	stat_rnd->statsRndTime = _stat_rnd;

	return instance;
}

StatsRenderTimeProject::StatsRenderTimeProject(void) : statsRndTime()
{}

StatsRenderTimeProject::~StatsRenderTimeProject(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool StatsRenderTimeProject::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__statrendertimeproject__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- ACCESSORS
void StatsRenderTimeProject::getLastUsed(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_StatsRenderTime_project& stat_rnd = ObjectWrap::Unwrap<StatsRenderTimeProject>(info.Holder())->statsRndTime;
	info.GetReturnValue().Set(Date::New(isolate, stat_rnd.lastUsed.toLocalTime() * 1000));
}

void StatsRenderTimeProject::getName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_StatsRenderTime_project& stat_rnd = ObjectWrap::Unwrap<StatsRenderTimeProject>(info.Holder())->statsRndTime;

	info.GetReturnValue().Set(String::NewFromUtf8(isolate,
		stat_rnd.name.toRRUTF8().value,
		v8::String::kInternalizedString));
}

//---------- NODE METHODS
void StatsRenderTimeProject::getLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(getLayer, Int32, ARGSDESCR(idx))

	_StatsRenderTime_project& stat_rnd = ObjectWrap::Unwrap<StatsRenderTimeProject>(args.This())->statsRndTime;
	Handle<Value> stat_rnd_lay = StatsRenderTimeLayer::fromStatRenderTimeLayer(stat_rnd.getLayer(args[0]->ToInt32()->Value()));

	args.GetReturnValue().Set(stat_rnd_lay);
}

void StatsRenderTimeProject::layerCount(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_StatsRenderTime_project& stat_rnd = ObjectWrap::Unwrap<StatsRenderTimeProject>(args.This())->statsRndTime;
	args.GetReturnValue().Set(Int32::New(isolate, stat_rnd.layerCount()));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(StatsRenderTimeProject,
	NODE_SET_PROTOTYPE_METHOD(tpl, "layerCount", layerCount);
    NODE_SET_PROTOTYPE_METHOD(tpl, "getLayer", getLayer);
    ,	)


// StatsRenderTimeLayer
//---------- CONSTRUCTION
Persistent<Function> StatsRenderTimeLayer::constructor;

void StatsRenderTimeLayer::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	StatsRenderTimeLayer *statrender = new StatsRenderTimeLayer();
	statrender->Wrap(self);

	self->SetAccessor(String::NewFromUtf8(isolate, "jobsAdded", v8::String::kInternalizedString), getJobsAdded);
	self->SetAccessor(String::NewFromUtf8(isolate, "name", v8::String::kInternalizedString), getName);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__statrendertimelayer__", String::kInternalizedString), Null(isolate));
	args.GetReturnValue().Set(args.This());
}

void StatsRenderTimeLayer::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

Handle<Value> StatsRenderTimeLayer::fromStatRenderTimeLayer(_StatsRenderTime_layer _stat_rnd)
{
	Isolate* isolate = Isolate::GetCurrent();
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	v8::Local<v8::Object> instance = cons->NewInstance();

	StatsRenderTimeLayer* stats_rnd = ObjectWrap::Unwrap<StatsRenderTimeLayer>(instance);
	stats_rnd->statsRndTime = _stat_rnd;

	return instance;
}

StatsRenderTimeLayer::StatsRenderTimeLayer(void) : statsRndTime()
{}

StatsRenderTimeLayer::~StatsRenderTimeLayer(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool StatsRenderTimeLayer::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Local<v8::Value> val = obj->GetHiddenValue(String::NewFromUtf8(isolate,
		"__statrendertimelayer__",
		String::kInternalizedString)
		);

	return !val->IsUndefined();
}

//---------- ACCESSORS
void StatsRenderTimeLayer::getJobsAdded(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_StatsRenderTime_layer& stat_rnd = ObjectWrap::Unwrap<StatsRenderTimeLayer>(info.Holder())->statsRndTime;
	info.GetReturnValue().Set(Int32::New(isolate, stat_rnd.jobsAdded));
}

void StatsRenderTimeLayer::getName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_StatsRenderTime_layer& stat_rnd = ObjectWrap::Unwrap<StatsRenderTimeLayer>(info.Holder())->statsRndTime;

	info.GetReturnValue().Set(String::NewFromUtf8(isolate,
		stat_rnd.name.toRRUTF8().value,
		v8::String::kInternalizedString));
}

//---------- NODE METHODS
void StatsRenderTimeLayer::timesCount(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	_StatsRenderTime_layer& stat_rnd = ObjectWrap::Unwrap<StatsRenderTimeLayer>(args.This())->statsRndTime;
	args.GetReturnValue().Set(Int32::New(isolate, stat_rnd.timesCount()));
}

void StatsRenderTimeLayer::getFrameTime(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	CHECKARGS_1(getFrameTime, Int32, ARGSDESCR(idx))

	_StatsRenderTime_layer& stat_rnd = ObjectWrap::Unwrap<StatsRenderTimeLayer>(args.This())->statsRndTime;
	args.GetReturnValue().Set(Int32::New(isolate, stat_rnd.getFrameTime(args[0]->ToInt32()->Value())));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(StatsRenderTimeLayer,
	NODE_SET_PROTOTYPE_METHOD(tpl, "timesCount", timesCount);
    NODE_SET_PROTOTYPE_METHOD(tpl, "getFrameTime", getFrameTime);
    , )


// DataFiles
//---------- CONSTRUCTION
Persistent<Function> DataFiles::constructor;

void DataFiles::construct(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Handle<Object> self = args.This();
	DataFiles *dataFiles = new DataFiles();
	dataFiles->Wrap(self);

	self->SetHiddenValue(String::NewFromUtf8(isolate, "__datafiles__", String::kInternalizedString), Null(isolate));

	args.GetReturnValue().Set(args.This());
}

void DataFiles::newInst(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };

	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

DataFiles::DataFiles(void)
{}

DataFiles::~DataFiles(void)
{}

//---------- MISC -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool DataFiles::objectIs(v8::Handle<v8::Object> obj)
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	return obj->Has(String::NewFromUtf8(isolate, "__datafiles__", v8::String::kInternalizedString));
}

//---------- INITIALIZE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INIT_RR_WRAP(DataFiles,
	NODE_SET_PROTOTYPE_METHOD(tpl, "_ClientGroupList", getNewClientGroupList);
	NODE_SET_PROTOTYPE_METHOD(tpl, "_ClientGroup", getNewClientGroup);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getRRFolder_cfgUser", getRRFolder_cfgUser);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getRRFolder_cfgStats", getRRFolder_cfgStats);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getRRFolder_bin", getRRFolder_bin);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getRRFolder_cfgGlobal", getRRFolder_cfgGlobal);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getRRModuleVersion", getRRModuleVersion);
	NODE_SET_PROTOTYPE_METHOD(tpl, "_dailyStats_data", getDailyStats);
	NODE_SET_PROTOTYPE_METHOD(tpl, "_rrsStatsSaveData", getSaveStats);
	NODE_SET_PROTOTYPE_METHOD(tpl, "_rrsStatsSaveDataLS", getSaveStatsLS);
	NODE_SET_PROTOTYPE_METHOD(tpl, "_rrClientStats_data", getClientStats);
	NODE_SET_PROTOTYPE_METHOD(tpl, "_frameStatJob", getFrameStatJob);
	NODE_SET_PROTOTYPE_METHOD(tpl, "_StatsRenderTime", getStatsRenderTime),

	ClientGroupList::init();
	ClientGroup::init();
	SingleStat::init();
	SingleStatDay::init();
	DailyStatsData::init();
	StatsSaveData::init();
	StatsSaveDataLS::init();
	ClientStatsData::init();
	ClientStatsDay::init();
	ClientStatsDayData::init();
	ClientStatsDayDataHourly::init();
	ClientStatsDayDataJobthread::init();
	ClientStatsDayDataHourlyJobThread::init();
	FrameStat::init();
	FrameStatJob::init();
	FrameStatPart::init();
	StatsType::init();
	StatsRenderTime::init();
	StatsRenderTimeProject::init();
	StatsRenderTimeLayer::init();
	)
