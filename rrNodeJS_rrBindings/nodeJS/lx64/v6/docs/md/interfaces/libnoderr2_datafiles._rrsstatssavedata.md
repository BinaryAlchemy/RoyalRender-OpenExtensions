[rrBindingsDocs](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_rrsStatsSaveData](libnoderr2_datafiles._rrsstatssavedata.md)

# Interface: _rrsStatsSaveData

## Hierarchy

* **_rrsStatsSaveData**

  ↳ [_rrsStatsSaveDataLS](libnoderr2_datafiles._rrsstatssavedatals.md)

## Index

### Properties

* [lastSaveDay](libnoderr2_datafiles._rrsstatssavedata.md#lastsaveday)
* [lastSaveMonth](libnoderr2_datafiles._rrsstatssavedata.md#lastsavemonth)
* [lastSaveYear](libnoderr2_datafiles._rrsstatssavedata.md#lastsaveyear)

### Methods

* [day](libnoderr2_datafiles._rrsstatssavedata.md#day)
* [dayMax](libnoderr2_datafiles._rrsstatssavedata.md#daymax)
* [month](libnoderr2_datafiles._rrsstatssavedata.md#month)
* [monthMax](libnoderr2_datafiles._rrsstatssavedata.md#monthmax)
* [year](libnoderr2_datafiles._rrsstatssavedata.md#year)
* [yearMax](libnoderr2_datafiles._rrsstatssavedata.md#yearmax)

## Properties

###  lastSaveDay

• **lastSaveDay**: *number*

*Defined in [types.d.ts:526](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L526)*

**`description`** The time the last index of the day array was saved. This value is the system time in the current time zone divided by 90. Use currentLocalTime() to get the current local time.

___

###  lastSaveMonth

• **lastSaveMonth**: *number*

*Defined in [types.d.ts:531](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L531)*

**`description`** The time the last index of the day array was saved. This value is the system time in the current time zone divided by 1800 (=30 minutes). Use currentLocalTime() to get the current local time.

___

###  lastSaveYear

• **lastSaveYear**: *number*

*Defined in [types.d.ts:536](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L536)*

**`description`** The time the last index of the day array was saved. This value is the system time in the current time zone divided by 21600 (=6 hours). Use currentLocalTime() to get the current local time.

## Methods

###  day

▸ **day**(`idx`: number): *[_rrsStats_type](libnoderr2_datafiles._rrsstats_type.md)*

*Defined in [types.d.ts:541](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L541)*

**`description`** Get the day stats at index idx. Index 0 returns the first 90s of the day, the time from 00:00.00 to 00:01.30. 12:15 in seconds of the day is 12*60*60 + 15*60 = 44100. Divided by 90s  is 44100 / 90 =490. The stats are constantly overwritten with the stats right now, therefore an index larger than the current time returns stats of yesterday. E.g. it is 18:00 right now. If you get the stats from 17:00, then you have the stats from 1 hour ago. If you get the stats from 19:00, then you get the stats from 23h ago. Note: This is only true as long as the rrServer is running and continues to save stats. Otherwise check lastSaveDay.

**Parameters:**

Name | Type |
------ | ------ |
`idx` | number |

**Returns:** *[_rrsStats_type](libnoderr2_datafiles._rrsstats_type.md)*

___

###  dayMax

▸ **dayMax**(): *number*

*Defined in [types.d.ts:546](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L546)*

**Returns:** *number*

Max number of stat values in the array. It returns 960 for the current version.

___

###  month

▸ **month**(): *[_rrsStats_type](libnoderr2_datafiles._rrsstats_type.md)*

*Defined in [types.d.ts:551](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L551)*

**`description`** The server adds the stats of the last 30 minutes to the last index (959) of the array and pushes all other stat values down in the array. Therefore an index of monthMax()-1=959 returns the stats of the last completed 30 minutes. E.g. if the current time is 18:15, then the last stats are from 17:30 - 18:00 Note: This is only true as long as the rrServer is running and continues to save stats. Otherwise check lastSaveMonth.

**Returns:** *[_rrsStats_type](libnoderr2_datafiles._rrsstats_type.md)*

___

###  monthMax

▸ **monthMax**(): *number*

*Defined in [types.d.ts:556](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L556)*

**Returns:** *number*

Max number of stat values in the array. It returns 960 for the current version.

___

###  year

▸ **year**(): *[_rrsStats_type](libnoderr2_datafiles._rrsstats_type.md)*

*Defined in [types.d.ts:561](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L561)*

**`description`** The server adds the stats of the last 30 minutes to the last index (959) of the array and pushes all other stat values down in the array. Therefore an index of yearMax()-1=959 returns the stats of the last completed half day minutes. E.g. if the current time is 18:15, then the last stats are from 00:00 - 12:00 Note: This is only true as long as the rrServer is running and continues to save stats. Otherwise check lastSaveYear.

**Returns:** *[_rrsStats_type](libnoderr2_datafiles._rrsstats_type.md)*

___

###  yearMax

▸ **yearMax**(): *number*

*Defined in [types.d.ts:566](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L566)*

**Returns:** *number*

Max number of stat values in the array. It returns 960 for the current version.
