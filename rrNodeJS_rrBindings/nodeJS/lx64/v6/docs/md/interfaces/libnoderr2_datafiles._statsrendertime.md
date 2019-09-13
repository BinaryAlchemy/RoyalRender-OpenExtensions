**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_StatsRenderTime](libnoderr2_datafiles._statsrendertime.md)

# Interface: _StatsRenderTime

## Hierarchy

* **_StatsRenderTime**

## Index

### Properties

* [lastSaved](libnoderr2_datafiles._statsrendertime.md#lastsaved)
* [prjCount](libnoderr2_datafiles._statsrendertime.md#prjcount)

### Methods

* [getError](libnoderr2_datafiles._statsrendertime.md#geterror)
* [getProject](libnoderr2_datafiles._statsrendertime.md#getproject)
* [loadFile](libnoderr2_datafiles._statsrendertime.md#loadfile)
* [saveFile](libnoderr2_datafiles._statsrendertime.md#savefile)

## Properties

###  lastSaved

• **lastSaved**: *Date*

*Defined in [types.d.ts:999](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L999)*

**`description`** Date/Time of the group settings file saved.

___

###  prjCount

• **prjCount**: *number*

*Defined in [types.d.ts:994](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L994)*

**`description`** Get the number of groups.

## Methods

###  getError

▸ **getError**(): *string*

*Defined in [types.d.ts:1023](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L1023)*

**Returns:** *string*

The error message in case the loadFile() or saveFile() fails.

___

###  getProject

▸ **getProject**(`idx`: number): *[_StatsRenderTime_project](libnoderr2_datafiles._statsrendertime_project.md)*

*Defined in [types.d.ts:1006](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L1006)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`idx` | number | The index of the project you want to fetch. |

**Returns:** *[_StatsRenderTime_project](libnoderr2_datafiles._statsrendertime_project.md)*

The project of the specified index.

___

###  loadFile

▸ **loadFile**(`FileName`: string): *boolean*

*Defined in [types.d.ts:1012](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L1012)*

**`description`** Loads the stats from file FileName.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`FileName` | string | The name of the file you want to load the stats from.  |

**Returns:** *boolean*

___

###  saveFile

▸ **saveFile**(`FileName`: string): *boolean*

*Defined in [types.d.ts:1018](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L1018)*

**`description`** Saves the stats into file FileName.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`FileName` | string | The name of the file you want to save the stats to.  |

**Returns:** *boolean*