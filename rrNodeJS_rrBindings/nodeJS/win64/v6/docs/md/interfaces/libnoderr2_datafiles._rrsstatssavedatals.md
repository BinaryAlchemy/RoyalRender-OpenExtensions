[rrBindingsDocs](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_rrsStatsSaveDataLS](libnoderr2_datafiles._rrsstatssavedatals.md)

# Interface: _rrsStatsSaveDataLS

## Hierarchy

* [_rrsStatsSaveData](libnoderr2_datafiles._rrsstatssavedata.md)

* [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md)

  ↳ **_rrsStatsSaveDataLS**

## Index

### Properties

* [lastSaveDay](libnoderr2_datafiles._rrsstatssavedatals.md#lastsaveday)
* [lastSaveMonth](libnoderr2_datafiles._rrsstatssavedatals.md#lastsavemonth)
* [lastSaveYear](libnoderr2_datafiles._rrsstatssavedatals.md#lastsaveyear)

### Methods

* [currentLocalTime](libnoderr2_datafiles._rrsstatssavedatals.md#currentlocaltime)
* [day](libnoderr2_datafiles._rrsstatssavedatals.md#day)
* [dayMax](libnoderr2_datafiles._rrsstatssavedatals.md#daymax)
* [getError](libnoderr2_datafiles._rrsstatssavedatals.md#geterror)
* [loadFromFile](libnoderr2_datafiles._rrsstatssavedatals.md#loadfromfile)
* [month](libnoderr2_datafiles._rrsstatssavedatals.md#month)
* [monthMax](libnoderr2_datafiles._rrsstatssavedatals.md#monthmax)
* [year](libnoderr2_datafiles._rrsstatssavedatals.md#year)
* [yearMax](libnoderr2_datafiles._rrsstatssavedatals.md#yearmax)

## Properties

###  lastSaveDay

• **lastSaveDay**: *number*

*Inherited from [_rrsStatsSaveData](libnoderr2_datafiles._rrsstatssavedata.md).[lastSaveDay](libnoderr2_datafiles._rrsstatssavedata.md#lastsaveday)*

*Defined in [types.d.ts:527](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L527)*

**`description`** The time the last index of the day array was saved. This value is the system time in the current time zone divided by 90. Use currentLocalTime() to get the current local time.

___

###  lastSaveMonth

• **lastSaveMonth**: *number*

*Inherited from [_rrsStatsSaveData](libnoderr2_datafiles._rrsstatssavedata.md).[lastSaveMonth](libnoderr2_datafiles._rrsstatssavedata.md#lastsavemonth)*

*Defined in [types.d.ts:532](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L532)*

**`description`** The time the last index of the day array was saved. This value is the system time in the current time zone divided by 1800 (=30 minutes). Use currentLocalTime() to get the current local time.

___

###  lastSaveYear

• **lastSaveYear**: *number*

*Inherited from [_rrsStatsSaveData](libnoderr2_datafiles._rrsstatssavedata.md).[lastSaveYear](libnoderr2_datafiles._rrsstatssavedata.md#lastsaveyear)*

*Defined in [types.d.ts:537](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L537)*

**`description`** The time the last index of the day array was saved. This value is the system time in the current time zone divided by 21600 (=6 hours). Use currentLocalTime() to get the current local time.

## Methods

###  currentLocalTime

▸ **currentLocalTime**(): *number*

*Defined in [types.d.ts:519](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L519)*

**Returns:** *number*

The current system time in the local time zone in seconds. The system time is based on the default unix timestamp (seconds since 00:00 hours, Jan 1, 1970).

___

###  day

▸ **day**(`idx`: number): *[_rrsStats_type](libnoderr2_datafiles._rrsstats_type.md)*

*Inherited from [_rrsStatsSaveData](libnoderr2_datafiles._rrsstatssavedata.md).[day](libnoderr2_datafiles._rrsstatssavedata.md#day)*

*Defined in [types.d.ts:542](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L542)*

**`description`** Get the day stats at index idx. Index 0 returns the first 90s of the day, the time from 00:00.00 to 00:01.30. 12:15 in seconds of the day is 12*60*60 + 15*60 = 44100. Divided by 90s  is 44100 / 90 =490. The stats are constantly overwritten with the stats right now, therefore an index larger than the current time returns stats of yesterday. E.g. it is 18:00 right now. If you get the stats from 17:00, then you have the stats from 1 hour ago. If you get the stats from 19:00, then you get the stats from 23h ago. Note: This is only true as long as the rrServer is running and continues to save stats. Otherwise check lastSaveDay.

**Parameters:**

Name | Type |
------ | ------ |
`idx` | number |

**Returns:** *[_rrsStats_type](libnoderr2_datafiles._rrsstats_type.md)*

___

###  dayMax

▸ **dayMax**(): *number*

*Inherited from [_rrsStatsSaveData](libnoderr2_datafiles._rrsstatssavedata.md).[dayMax](libnoderr2_datafiles._rrsstatssavedata.md#daymax)*

*Defined in [types.d.ts:547](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L547)*

**Returns:** *number*

Max number of stat values in the array. It returns 960 for the current version.

___

###  getError

▸ **getError**(): *string*

*Inherited from [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md).[getError](libnoderr2_datafiles._rrstatssharedfunctions.md#geterror)*

*Defined in [types.d.ts:451](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L451)*

**Returns:** *string*

The error message in case the loadFromFile() fails.

___

###  loadFromFile

▸ **loadFromFile**(`FileName`: string): *boolean*

*Inherited from [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md).[loadFromFile](libnoderr2_datafiles._rrstatssharedfunctions.md#loadfromfile)*

*Defined in [types.d.ts:446](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L446)*

**`description`** Loads the stats from file FileName.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`FileName` | string | Filename of the file which should be loaded.  |

**Returns:** *boolean*

___

###  month

▸ **month**(): *[_rrsStats_type](libnoderr2_datafiles._rrsstats_type.md)*

*Inherited from [_rrsStatsSaveData](libnoderr2_datafiles._rrsstatssavedata.md).[month](libnoderr2_datafiles._rrsstatssavedata.md#month)*

*Defined in [types.d.ts:552](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L552)*

**`description`** The server adds the stats of the last 30 minutes to the last index (959) of the array and pushes all other stat values down in the array. Therefore an index of monthMax()-1=959 returns the stats of the last completed 30 minutes. E.g. if the current time is 18:15, then the last stats are from 17:30 - 18:00 Note: This is only true as long as the rrServer is running and continues to save stats. Otherwise check lastSaveMonth.

**Returns:** *[_rrsStats_type](libnoderr2_datafiles._rrsstats_type.md)*

___

###  monthMax

▸ **monthMax**(): *number*

*Inherited from [_rrsStatsSaveData](libnoderr2_datafiles._rrsstatssavedata.md).[monthMax](libnoderr2_datafiles._rrsstatssavedata.md#monthmax)*

*Defined in [types.d.ts:557](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L557)*

**Returns:** *number*

Max number of stat values in the array. It returns 960 for the current version.

___

###  year

▸ **year**(): *[_rrsStats_type](libnoderr2_datafiles._rrsstats_type.md)*

*Inherited from [_rrsStatsSaveData](libnoderr2_datafiles._rrsstatssavedata.md).[year](libnoderr2_datafiles._rrsstatssavedata.md#year)*

*Defined in [types.d.ts:562](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L562)*

**`description`** The server adds the stats of the last 30 minutes to the last index (959) of the array and pushes all other stat values down in the array. Therefore an index of yearMax()-1=959 returns the stats of the last completed half day minutes. E.g. if the current time is 18:15, then the last stats are from 00:00 - 12:00 Note: This is only true as long as the rrServer is running and continues to save stats. Otherwise check lastSaveYear.

**Returns:** *[_rrsStats_type](libnoderr2_datafiles._rrsstats_type.md)*

___

###  yearMax

▸ **yearMax**(): *number*

*Inherited from [_rrsStatsSaveData](libnoderr2_datafiles._rrsstatssavedata.md).[yearMax](libnoderr2_datafiles._rrsstatssavedata.md#yearmax)*

*Defined in [types.d.ts:567](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L567)*

**Returns:** *number*

Max number of stat values in the array. It returns 960 for the current version.
