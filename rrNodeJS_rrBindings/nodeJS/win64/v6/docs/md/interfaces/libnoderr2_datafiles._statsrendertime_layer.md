[rrBindingsDocs](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_StatsRenderTime_layer](libnoderr2_datafiles._statsrendertime_layer.md)

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

*Defined in [types.d.ts:1055](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1055)*

**`description`** Number of jobs that have been added. This is NOT the number of jobs in this list.

___

###  name

• **name**: *string*

*Defined in [types.d.ts:1060](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1060)*

**`description`** Name of the layer.

## Methods

###  getFrameTime

▸ **getFrameTime**(`idx`: number): *number*

*Defined in [types.d.ts:1066](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1066)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`idx` | number | The index of the Frame time.  |

**Returns:** *number*

The frame time at idx. The frame time is in PS*s.

___

###  timesCount

▸ **timesCount**(): *number*

*Defined in [types.d.ts:1071](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1071)*

**Returns:** *number*

The number of frame times in this list. The latest job is always at position 0.
