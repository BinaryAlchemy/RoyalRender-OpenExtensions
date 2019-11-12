[rrBindingsDocs](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_DailyStats_Data](libnoderr2_datafiles._dailystats_data.md)

# Interface: _DailyStats_Data

## Hierarchy

* [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md)

  ↳ **_DailyStats_Data**

## Index

### Methods

* [getError](libnoderr2_datafiles._dailystats_data.md#geterror)
* [loadFromFile](libnoderr2_datafiles._dailystats_data.md#loadfromfile)
* [singleStats](libnoderr2_datafiles._dailystats_data.md#singlestats)
* [singleStatsMax](libnoderr2_datafiles._dailystats_data.md#singlestatsmax)

## Methods

###  getError

▸ **getError**(): *string*

*Inherited from [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md).[getError](libnoderr2_datafiles._rrstatssharedfunctions.md#geterror)*

*Defined in [types.d.ts:450](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L450)*

**Returns:** *string*

The error message in case the loadFromFile() fails.

___

###  loadFromFile

▸ **loadFromFile**(`FileName`: string): *boolean*

*Inherited from [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md).[loadFromFile](libnoderr2_datafiles._rrstatssharedfunctions.md#loadfromfile)*

*Defined in [types.d.ts:445](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L445)*

**`description`** Loads the stats from file FileName.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`FileName` | string | Filename of the file which should be loaded.  |

**Returns:** *boolean*

___

###  singleStats

▸ **singleStats**(`id`: number): *[_singleStatDay](libnoderr2_datafiles._singlestatday.md)[]*

*Defined in [types.d.ts:459](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L459)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`id` | number | 0 -> User stats, 1 -> Project stats, 2 -> Render app stats |

**Returns:** *[_singleStatDay](libnoderr2_datafiles._singlestatday.md)[]*

A list of statistics.

___

###  singleStatsMax

▸ **singleStatsMax**(): *number*

*Defined in [types.d.ts:464](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L464)*

**Returns:** *number*

The number of different stat lists. Which is 3.
