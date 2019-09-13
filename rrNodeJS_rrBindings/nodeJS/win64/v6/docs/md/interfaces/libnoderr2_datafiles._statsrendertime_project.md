**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_StatsRenderTime_project](libnoderr2_datafiles._statsrendertime_project.md)

# Interface: _StatsRenderTime_project

## Hierarchy

* **_StatsRenderTime_project**

## Index

### Properties

* [lastUsed](libnoderr2_datafiles._statsrendertime_project.md#lastused)
* [name](libnoderr2_datafiles._statsrendertime_project.md#name)

### Methods

* [getLayer](libnoderr2_datafiles._statsrendertime_project.md#getlayer)
* [layerCount](libnoderr2_datafiles._statsrendertime_project.md#layercount)

## Properties

###  lastUsed

• **lastUsed**: *Date*

*Defined in [types.d.ts:1031](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1031)*

**`returns`** The last time a job was added to this list.

___

###  name

• **name**: *string*

*Defined in [types.d.ts:1036](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1036)*

**`returns`** Name of the project.

## Methods

###  getLayer

▸ **getLayer**(`idx`: number): *[_StatsRenderTime_layer](libnoderr2_datafiles._statsrendertime_layer.md)*

*Defined in [types.d.ts:1041](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1041)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`idx` | number | The index of the Layer you want to fetch.  |

**Returns:** *[_StatsRenderTime_layer](libnoderr2_datafiles._statsrendertime_layer.md)*

___

###  layerCount

▸ **layerCount**(): *number*

*Defined in [types.d.ts:1046](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1046)*

**Returns:** *number*

The number of layers in this list.