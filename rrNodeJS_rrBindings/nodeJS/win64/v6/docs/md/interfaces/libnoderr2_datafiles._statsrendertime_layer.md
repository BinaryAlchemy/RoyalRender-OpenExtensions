**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_StatsRenderTime_layer](libnoderr2_datafiles._statsrendertime_layer.md)

# Interface: _StatsRenderTime_layer

## Hierarchy

* **_StatsRenderTime_layer**

## Index

### Properties

* [jobsAdded](libnoderr2_datafiles._statsrendertime_layer.md#jobsadded)
* [name](libnoderr2_datafiles._statsrendertime_layer.md#name)

### Methods

* [getFrameTime](libnoderr2_datafiles._statsrendertime_layer.md#getframetime)
* [timesCount](libnoderr2_datafiles._statsrendertime_layer.md#timescount)

## Properties

###  jobsAdded

• **jobsAdded**: *number*

*Defined in [types.d.ts:1054](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1054)*

**`description`** Number of jobs that have been added. This is NOT the number of jobs in this list.

___

###  name

• **name**: *string*

*Defined in [types.d.ts:1059](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1059)*

**`description`** Name of the layer.

## Methods

###  getFrameTime

▸ **getFrameTime**(`idx`: number): *number*

*Defined in [types.d.ts:1065](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1065)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`idx` | number | The index of the Frame time.  |

**Returns:** *number*

The frame time at idx. The frame time is in PS*s.

___

###  timesCount

▸ **timesCount**(): *number*

*Defined in [types.d.ts:1070](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1070)*

**Returns:** *number*

The number of frame times in this list. The latest job is always at position 0.