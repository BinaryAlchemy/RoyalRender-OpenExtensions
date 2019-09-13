**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_rrClientStats_Data](libnoderr2_datafiles._rrclientstats_data.md)

# Interface: _rrClientStats_Data

## Hierarchy

* [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md)

  * **_rrClientStats_Data**

## Index

### Properties

* [structureID](libnoderr2_datafiles._rrclientstats_data.md#structureid)

### Methods

* [days](libnoderr2_datafiles._rrclientstats_data.md#days)
* [daysMax](libnoderr2_datafiles._rrclientstats_data.md#daysmax)
* [getError](libnoderr2_datafiles._rrclientstats_data.md#geterror)
* [loadFromFile](libnoderr2_datafiles._rrclientstats_data.md#loadfromfile)

## Properties

###  structureID

• **structureID**: *number*

*Defined in [types.d.ts:682](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L682)*

**`description`** Should be the hex value A101.

## Methods

###  days

▸ **days**(`idx`: number): *[_rrClientStats_day](libnoderr2_datafiles._rrclientstats_day.md)*

*Defined in [types.d.ts:688](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L688)*

**`description`** Get the data per day. Index (daysMax() - 1) is the last day written into the stats file. If the client is currently running, then this is today. Index (daysMax() - 2) is the day before. Check days(...).daySet and days(...).day to verify that you got some data and that it is the right day.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`idx` | number | The Index of the _rrClientStats_day instance you want to fetch.  |

**Returns:** *[_rrClientStats_day](libnoderr2_datafiles._rrclientstats_day.md)*

___

###  daysMax

▸ **daysMax**(): *boolean*

*Defined in [types.d.ts:693](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L693)*

**Returns:** *boolean*

The maximum number of days in this array (180).

___

###  getError

▸ **getError**(): *string*

*Inherited from [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md).[getError](libnoderr2_datafiles._rrstatssharedfunctions.md#geterror)*

*Defined in [types.d.ts:450](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L450)*

**Returns:** *string*

The error message in case the loadFromFile() fails.

___

###  loadFromFile

▸ **loadFromFile**(`FileName`: string): *boolean*

*Inherited from [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md).[loadFromFile](libnoderr2_datafiles._rrstatssharedfunctions.md#loadfromfile)*

*Defined in [types.d.ts:445](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L445)*

**`description`** Loads the stats from file FileName.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`FileName` | string | Filename of the file which should be loaded.  |

**Returns:** *boolean*