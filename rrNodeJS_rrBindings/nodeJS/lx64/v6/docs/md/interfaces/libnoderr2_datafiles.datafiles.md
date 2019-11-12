[rrBindingsDocs](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [DataFiles](libnoderr2_datafiles.datafiles.md)

# Interface: DataFiles

## Hierarchy

* **DataFiles**

## Index

### Methods

* [_ClientGroup](libnoderr2_datafiles.datafiles.md#_clientgroup)
* [_ClientGroupList](libnoderr2_datafiles.datafiles.md#_clientgrouplist)
* [_StatsRenderTime](libnoderr2_datafiles.datafiles.md#_statsrendertime)
* [_dailyStats_data](libnoderr2_datafiles.datafiles.md#_dailystats_data)
* [_frameStatJob](libnoderr2_datafiles.datafiles.md#_framestatjob)
* [_rrClientStats_data](libnoderr2_datafiles.datafiles.md#_rrclientstats_data)
* [_rrsStatsSaveData](libnoderr2_datafiles.datafiles.md#_rrsstatssavedata)
* [_rrsStatsSaveDataLS](libnoderr2_datafiles.datafiles.md#_rrsstatssavedatals)
* [getRRFolder_bin](libnoderr2_datafiles.datafiles.md#getrrfolder_bin)
* [getRRFolder_cfgGlobal](libnoderr2_datafiles.datafiles.md#getrrfolder_cfgglobal)
* [getRRFolder_cfgStats](libnoderr2_datafiles.datafiles.md#getrrfolder_cfgstats)
* [getRRFolder_cfgUser](libnoderr2_datafiles.datafiles.md#getrrfolder_cfguser)
* [getRRModuleVersion](libnoderr2_datafiles.datafiles.md#getrrmoduleversion)

## Methods

###  _ClientGroup

▸ **_ClientGroup**(`idx`: number): *[_ClientGroup](libnoderr2_datafiles._clientgroup.md)*

*Defined in [types.d.ts:436](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L436)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`idx` | number | The idx of the client group. |

**Returns:** *[_ClientGroup](libnoderr2_datafiles._clientgroup.md)*

A new _ClientGroup instance.

___

###  _ClientGroupList

▸ **_ClientGroupList**(): *[_ClientGroupList](libnoderr2_datafiles._clientgrouplist.md)*

*Defined in [types.d.ts:418](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L418)*

**`description`** The client group list.

**Returns:** *[_ClientGroupList](libnoderr2_datafiles._clientgrouplist.md)*

A new _ClientGroupList instance.

___

###  _StatsRenderTime

▸ **_StatsRenderTime**(): *[_StatsRenderTime](libnoderr2_datafiles._statsrendertime.md)*

*Defined in [types.d.ts:430](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L430)*

**`description`** Every time a job is finished, it adds its average frame time to a list, separated by each layer of each project. It includes the last 100 finished jobs of each layer name of each project. (For example the the last 100 jobs of render layer "Ambient Occlusion" of project "FancyDrink-Commercial")

**Returns:** *[_StatsRenderTime](libnoderr2_datafiles._statsrendertime.md)*

A new _StatsRenderTime Instance.

___

###  _dailyStats_data

▸ **_dailyStats_data**(): *[_DailyStats_Data](libnoderr2_datafiles._dailystats_data.md)*

*Defined in [types.d.ts:394](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L394)*

**`description`** Job information for each project, user and render application that was used. Informations like Memory usage, CPU usage, Number of jobs rendering, idle, finished, .., Number of frames rendered and frames to be rendered.

**Returns:** *[_DailyStats_Data](libnoderr2_datafiles._dailystats_data.md)*

A new _DailyStats_Data instance.

___

###  _frameStatJob

▸ **_frameStatJob**(): *[_frameStatJob](libnoderr2_datafiles._framestatjob.md)*

*Defined in [types.d.ts:424](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L424)*

**`description`** Same data as the the "frames rendered" table in rrControl. Per frame information includes Render time, Memory (5 times per frame), CPU usage (5 times per frame)

**Returns:** *[_frameStatJob](libnoderr2_datafiles._framestatjob.md)*

A _frameStatJob instance.

___

###  _rrClientStats_data

▸ **_rrClientStats_data**(): *[_rrClientStats_Data](libnoderr2_datafiles._rrclientstats_data.md)*

*Defined in [types.d.ts:406](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L406)*

**`description`** rrClient stats with CPU usage, memory usage, current job, ...

**Returns:** *[_rrClientStats_Data](libnoderr2_datafiles._rrclientstats_data.md)*

A new _rrClientStats_Data instance.

___

###  _rrsStatsSaveData

▸ **_rrsStatsSaveData**(): *[_rrsStatsSaveData](libnoderr2_datafiles._rrsstatssavedata.md)*

*Defined in [types.d.ts:400](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L400)*

**`description`** Same as you see in rrControl tab "Global Info".Clients enabled, disabled, rendering. Jobs rendering, waiting Frames rendered, waiting, Server CPU usage.

**Returns:** *[_rrsStatsSaveData](libnoderr2_datafiles._rrsstatssavedata.md)*

A new _rrsStatsSaveData instance.

___

###  _rrsStatsSaveDataLS

▸ **_rrsStatsSaveDataLS**(): *[_rrsStatsSaveDataLS](libnoderr2_datafiles._rrsstatssavedatals.md)*

*Defined in [types.d.ts:412](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L412)*

**`description`** This class loads the file [RR]\sub\stats\server_stats.db This statistics file is used to create the server stats in rrControl, tab Global Info. There are three different stats: "day": A 24h statistic, saved every 90seconds. "month": A 20 day statistic, saved every 30 minutes. "year": A 160 days statistic, saved every 6 hours.

**Returns:** *[_rrsStatsSaveDataLS](libnoderr2_datafiles._rrsstatssavedatals.md)*

A _rrsStatsSaveDataLS instance.

___

###  getRRFolder_bin

▸ **getRRFolder_bin**(): *string*

*Defined in [types.d.ts:388](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L388)*

**Returns:** *string*

The path [RR]/bin/[OS] It has to be executed from a machine in an RR environment (System variable RR_ROOT is defined). Otherwise it returns an empty string.

___

###  getRRFolder_cfgGlobal

▸ **getRRFolder_cfgGlobal**(): *string*

*Defined in [types.d.ts:373](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L373)*

**Returns:** *string*

The path [RR]/sub/cfg_global. It has to be executed from a machine in an RR environment (System variable RR_ROOT is defined). Otherwise it returns an empty string.

___

###  getRRFolder_cfgStats

▸ **getRRFolder_cfgStats**(): *string*

*Defined in [types.d.ts:383](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L383)*

**Returns:** *string*

The path [RR]/sub/stats. It has to be executed from a machine in an RR environment (System variable RR_ROOT is defined). Otherwise it returns an empty string.

___

###  getRRFolder_cfgUser

▸ **getRRFolder_cfgUser**(): *string*

*Defined in [types.d.ts:378](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L378)*

**Returns:** *string*

The path [RR]/sub/cfg_user. It has to be executed from a machine in an RR environment (System variable RR_ROOT is defined). Otherwise it returns an empty string.

___

###  getRRModuleVersion

▸ **getRRModuleVersion**(): *string*

*Defined in [types.d.ts:368](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L368)*

**`description`** Requires to call any jobGet..() function.

**Returns:** *string*
