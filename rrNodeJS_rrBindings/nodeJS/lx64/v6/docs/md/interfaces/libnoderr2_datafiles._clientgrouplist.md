**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_ClientGroupList](libnoderr2_datafiles._clientgrouplist.md)

# Interface: _ClientGroupList

## Hierarchy

* [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md)

  * **_ClientGroupList**

## Index

### Properties

* [count](libnoderr2_datafiles._clientgrouplist.md#count)
* [settingsFileDate](libnoderr2_datafiles._clientgrouplist.md#settingsfiledate)

### Methods

* [clientGroup](libnoderr2_datafiles._clientgrouplist.md#clientgroup)
* [clientGroupSet](libnoderr2_datafiles._clientgrouplist.md#clientgroupset)
* [clientGroupsMax](libnoderr2_datafiles._clientgrouplist.md#clientgroupsmax)
* [getError](libnoderr2_datafiles._clientgrouplist.md#geterror)
* [loadFromFile](libnoderr2_datafiles._clientgrouplist.md#loadfromfile)
* [saveToFile](libnoderr2_datafiles._clientgrouplist.md#savetofile)

## Properties

###  count

• **count**: *number*

*Defined in [types.d.ts:914](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L914)*

**`description`** Get/set the number of groups.

___

###  settingsFileDate

• **settingsFileDate**: *Date*

*Defined in [types.d.ts:909](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L909)*

**`description`** Date/Time of the group settings file loaded/saved.

## Methods

###  clientGroup

▸ **clientGroup**(`idx`: number): *[_ClientGroup](libnoderr2_datafiles._clientgroup.md)*

*Defined in [types.d.ts:920](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L920)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`idx` | number | Index of the clientGroup you want to fetch. |

**Returns:** *[_ClientGroup](libnoderr2_datafiles._clientgroup.md)*

The client group at the specified idx.

___

###  clientGroupSet

▸ **clientGroupSet**(`idx`: number, `group`: [_ClientGroup](libnoderr2_datafiles._clientgroup.md)): *void*

*Defined in [types.d.ts:927](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L927)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`idx` | number | The index of the client group which should be replaced. |
`group` | [_ClientGroup](libnoderr2_datafiles._clientgroup.md) | The client group which should replace the other client group, specified by the idx.  |

**Returns:** *void*

___

###  clientGroupsMax

▸ **clientGroupsMax**(): *number*

*Defined in [types.d.ts:932](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L932)*

**Returns:** *number*

The maximum number of possible groups in this RR version.

___

###  getError

▸ **getError**(): *string*

*Inherited from [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md).[getError](libnoderr2_datafiles._rrstatssharedfunctions.md#geterror)*

*Defined in [types.d.ts:450](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L450)*

**Returns:** *string*

The error message in case the loadFromFile() fails.

___

###  loadFromFile

▸ **loadFromFile**(`FileName`: string): *boolean*

*Inherited from [_rrStatsSharedFunctions](libnoderr2_datafiles._rrstatssharedfunctions.md).[loadFromFile](libnoderr2_datafiles._rrstatssharedfunctions.md#loadfromfile)*

*Defined in [types.d.ts:445](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L445)*

**`description`** Loads the stats from file FileName.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`FileName` | string | Filename of the file which should be loaded.  |

**Returns:** *boolean*

___

###  saveToFile

▸ **saveToFile**(`FileName`: string): *boolean*

*Defined in [types.d.ts:938](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L938)*

**`description`** Saves the stats into file FileName.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`FileName` | string | The file name of the file where the stats should be saved to.  |

**Returns:** *boolean*