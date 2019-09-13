**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_frameStatJob](libnoderr2_datafiles._framestatjob.md)

# Interface: _frameStatJob

## Hierarchy

* [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md)

  * **_frameStatJob**

## Index

### Methods

* [frame](libnoderr2_datafiles._framestatjob.md#frame)
* [frameMax](libnoderr2_datafiles._framestatjob.md#framemax)
* [getError](libnoderr2_datafiles._framestatjob.md#geterror)
* [loadFromFile](libnoderr2_datafiles._framestatjob.md#loadfromfile)

## Methods

###  frame

▸ **frame**(`frame`: number): *[_frameStat](libnoderr2_datafiles._framestat.md)*

*Defined in [types.d.ts:828](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L828)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`frame` | number | The Framenumber of the frame you want to fetch stats from. |

**Returns:** *[_frameStat](libnoderr2_datafiles._framestat.md)*

The stats of frame X. The first frame has index number 0. It is not the frame number in the scene file.

___

###  frameMax

▸ **frameMax**(): *number*

*Defined in [types.d.ts:833](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L833)*

**Returns:** *number*

Max number of frames for this job.

___

###  getError

▸ **getError**(): *string*

*Inherited from [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md).[getError](libnoderr2_datafiles._rrstatssharedfunctions.md#geterror)*

*Defined in [types.d.ts:450](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L450)*

**Returns:** *string*

The error message in case the loadFromFile() fails.

___

###  loadFromFile

▸ **loadFromFile**(`FileName`: string): *boolean*

*Inherited from [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md).[loadFromFile](libnoderr2_datafiles._rrstatssharedfunctions.md#loadfromfile)*

*Defined in [types.d.ts:445](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L445)*

**`description`** Loads the stats from file FileName.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`FileName` | string | Filename of the file which should be loaded.  |

**Returns:** *boolean*