// data.h
#ifndef __NODE_DATA__
#define __NODE_DATA__

#include <node.h>
#include <node_object_wrap.h>
#include <v8.h>

#include "../../shared/RR_DataTypes_clientlist.h"
#include "../../shared/RR_DataTypes_clientgroups.h"
#include "../../rrServerconsole/rrServer_CheckThread_Serverstats.h"
#include "../../rrClient/rrClient_Stats.h"
#include "../../shared/RR_DataTypes_framestats.h"
#include "../../shared/RR_DataTypes_StatsRenderTime.h"


class DataFiles : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);

	DataFiles(void);
	~DataFiles(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
};


class ClientGroup : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromClientGroup(rrC::_ClientGroup grp);

	ClientGroup(void);
	~ClientGroup(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// node methods
	static void clear(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getName(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void setName(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getClientName(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void addClient(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void removeClient(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void removeClientbyID(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void count(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

	rrC::_ClientGroup clntGrp;  // unset, unless initialized with fromClientGroup or NewInst or manually;
private:
	static v8::Persistent<v8::Function> constructor;
};


class ClientGroupList : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);

	ClientGroupList(void);
	~ClientGroupList(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// node methods
	static void clientGroupGet(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	clientGroupSet(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	clientGroupsMax(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	loadFromFile(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	saveToFile(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	getError(const v8::FunctionCallbackInfo<v8::Value>& args);

	// accessors
	static void getCount(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void setCount(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
	static void getSettingsFileDate(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void setSettingsFileDate(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	rrC::_ClientGroupList clntGrp;
};


class SingleStat : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromSingleStat(_singleStat* _snglStat);

	SingleStat(void);
	~SingleStat(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getAvPSUsage(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getMaxPSUsage(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getAvGhzUsage(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getMaxGhzUsage(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getPSneeded(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getRenderLicNeeded(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getJobsWaiting(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getJobsDisabled(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getJobsIdle(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getJobsRendering(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getJobsDone(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getTimesSended(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getTimesFinished(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getAvMemUsageMB(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getMaxMemUsageMB(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getAvFrameTime(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getFramesRendered(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getFramesLeft(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);

	// node methods
	static void clear(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_singleStat* snglStat = NULL; // stays NULL, unless initialized with fromSingleStat method or manually set;
};


class SingleStatDay : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromSingleStatDay(_singleStatDay* _snglStDay);
    static v8::Handle<v8::Value> fromSingleStatDay(const _singleStatDay& _snglStDay);

	SingleStatDay(void);
	~SingleStatDay(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void setName(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
	static void getType(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);

	// node methods
	static void stats(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	statsMax(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_singleStatDay* snglStatDay = NULL;  // stays NULL, unless initialized with fromSingleStatDay or NewInst, or manually set;
	bool delInternalPointer = true;
};


class StatsSaveData : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);

	StatsSaveData(void);
	~StatsSaveData(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getLastSaveDay(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getLastSaveMonth(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getLastSaveYear(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);

	// node methods
	static void day(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	dayMax(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	month(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	monthMax(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	year(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	yearMax(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	loadFromFile(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	getError(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_rrsStatsSaveData svStatData;
};

class StatsSaveDataLS : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);

	StatsSaveDataLS(void);
	~StatsSaveDataLS(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// node methods
	static void	loadFromFile(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	getError(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	currentLocalTime(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void day(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	dayMax(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	month(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	monthMax(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	year(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	yearMax(const v8::FunctionCallbackInfo<v8::Value>& args);
	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_rrsStatsSaveDataLS svStatData;
};

class StatsType : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromRRStatType(_rrsStats_type _stat_type);

	StatsType(void);
	~StatsType(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getSlot_used(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getClients_needed(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getFramesPer90s(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getClients_free(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getClient_rendering(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getClients_disabled(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getCpuProcess(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getCpuMachine(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getServerTemperature(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getAvclientTemperature(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getJobs_unfinished(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getJobs_rendering(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getJobs_total(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getMemUsageMachine(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getMemUsageProcess(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getTCPMemUsageSocket(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getTCPMemUsageData(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getJobBufferMemUsageJobs(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getTCPMemUsageDataCompressed(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getAv_frame_time(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getFrames_to_do(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_rrsStats_type statType;
};


class ClientStatsData : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);

	ClientStatsData(void);
	~ClientStatsData(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getStructureID(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);

	// node methods
	static void days(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	daysMax(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	loadFromFile(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	getError(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_rrClientStats_data clStats;
};


class ClientStatsDay : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromRRClientStatDay(_rrClientStats_day _snglStDay);

	ClientStatsDay(void);
	~ClientStatsDay(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getDaySet(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getDay(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);

	// node methods
	static void	data(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	dataMax(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	dataHourly(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	dataHourlyMax(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_rrClientStats_day clStats;
};


class ClientStatsDayDataHourly : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromRRClientStatDayDataHourly(_rrClientStats_day_data_hourly _snglStDay);

	ClientStatsDayDataHourly(void);
	~ClientStatsDayDataHourly(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// node methods
	static void	jobThread(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	jobThreadMax(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_rrClientStats_day_data_hourly clStats;
};


class ClientStatsDayDataHourlyJobThread : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromClientStatsDayDataHJobthread(_rrClientStats_day_data_hourly_jobthread stat_dd_jobthr);

	ClientStatsDayDataHourlyJobThread(void);
	~ClientStatsDayDataHourlyJobThread(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getFramesDone(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getJobCrashed(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getJobAborted(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getJobSuccessful(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_rrClientStats_day_data_hourly_jobthread clStats;
};


class ClientStatsDayData : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromClientDayData(_rrClientStats_day_data cl_statday_data);

	ClientStatsDayData(void);
	~ClientStatsDayData(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getUserLoggedIn(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getCpuTotal(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getMemTotal10MB(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);

	// node methods
	static void	jobThread(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	jobThreadMax(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_rrClientStats_day_data clStats;
};


class ClientStatsDayDataJobthread : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromClientStatsDayDataJobthread(_rrClientStats_day_data_jobthread stat_dd_jobthr);

	ClientStatsDayDataJobthread(void);
	~ClientStatsDayDataJobthread(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getStatus(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getCpuRender(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getMemRender10MB(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getJobIDShort(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);

	// node methods
	static void	jobIDShortStr(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_rrClientStats_day_data_jobthread clStats;
};


class FrameStatJob : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);

	FrameStatJob(void);
	~FrameStatJob(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// node methods
	static void	loadFromFile(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	getError(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	frame(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	frameMax(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_frameStatJob frmStat;
};


class FrameStat : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromFrameStat(_frameStat _frm_stat);

	FrameStat(void);
	~FrameStat(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getLogFileStart(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getLogFileStartFrame(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getRenderTime5Sec(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getFrameNrJob(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getClient(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getAverageValue(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);

	// node methods
	static void	part(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	partMax(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_frameStat frmStat;
};


class FrameStatPart : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromFrameStatPart(_frameStat_part _stat_part);

	FrameStatPart(void);
	~FrameStatPart(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getJobMemoryMB(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getJobCPU(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getNonJobCPU(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getRenderThreads(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_frameStat_part frmStat;
};


class StatsRenderTime : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);

	StatsRenderTime(void);
	~StatsRenderTime(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getCount(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void setCount(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);
	static void getLastSaved(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	
	// node methods
	static void	getProject(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	loadFile(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	saveFile(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	getError(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_StatsRenderTime statsRndTime;
};


class StatsRenderTimeProject : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromStatRenderTimeProject(_StatsRenderTime_project _stat_rnd);

	StatsRenderTimeProject(void);
	~StatsRenderTimeProject(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getLastUsed(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);

	// node methods
	static void	getLayer(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	layerCount(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_StatsRenderTime_project statsRndTime;
};


class StatsRenderTimeLayer : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Handle<v8::Value> fromStatRenderTimeLayer(_StatsRenderTime_layer _stat_rnd);

	StatsRenderTimeLayer(void);
	~StatsRenderTimeLayer(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// accessors
	static void getJobsAdded(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);
	static void getName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);

	// node methods
	static void	getFrameTime(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	timesCount(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_StatsRenderTime_layer statsRndTime;
};


class DailyStatsData : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);

	DailyStatsData(void);
	~DailyStatsData(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// node methods
	static void singleStats(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	singleStatsMax(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	loadFromFile(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void	getError(const v8::FunctionCallbackInfo<v8::Value>& args);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
	_dailyStats_data dsData;
};

#endif
