[rrBindingsDocs](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md)

# Interface: _rrStatsSharedFunctions

## Hierarchy

* **_rrStatsSharedFunctions**

  ↳ [_DailyStats_Data](libnoderr2_datafiles._dailystats_data.md)

  ↳ [_rrsStatsSaveDataLS](libnoderr2_datafiles._rrsstatssavedatals.md)

  ↳ [_rrClientStats_Data](libnoderr2_datafiles._rrclientstats_data.md)

  ↳ [_frameStatJob](libnoderr2_datafiles._framestatjob.md)

  ↳ [_ClientGroupList](libnoderr2_datafiles._clientgrouplist.md)

## Index

### Methods

* [getError](libnoderr2_datafiles._rrstatssharedfunctions.md#geterror)
* [loadFromFile](libnoderr2_datafiles._rrstatssharedfunctions.md#loadfromfile)

## Methods

###  getError

▸ **getError**(): *string*

*Defined in [types.d.ts:451](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L451)*

**Returns:** *string*

The error message in case the loadFromFile() fails.

___

###  loadFromFile

▸ **loadFromFile**(`FileName`: string): *boolean*

*Defined in [types.d.ts:446](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L446)*

**`description`** Loads the stats from file FileName.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`FileName` | string | Filename of the file which should be loaded.  |

**Returns:** *boolean*
