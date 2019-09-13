**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_ClientGroup](libnoderr2_datafiles._clientgroup.md)

# Interface: _ClientGroup

## Hierarchy

* **_ClientGroup**

## Index

### Methods

* [addClient](libnoderr2_datafiles._clientgroup.md#addclient)
* [clear](libnoderr2_datafiles._clientgroup.md#clear)
* [count](libnoderr2_datafiles._clientgroup.md#count)
* [getClientName](libnoderr2_datafiles._clientgroup.md#getclientname)
* [getName](libnoderr2_datafiles._clientgroup.md#getname)
* [removeClient](libnoderr2_datafiles._clientgroup.md#removeclient)
* [removeClientbyID](libnoderr2_datafiles._clientgroup.md#removeclientbyid)
* [setName](libnoderr2_datafiles._clientgroup.md#setname)

## Methods

###  addClient

▸ **addClient**(`name`: string): *void*

*Defined in [types.d.ts:969](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L969)*

**`description`** Add a client with the specified name to the list.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`name` | string | The name of the new Client.  |

**Returns:** *void*

___

###  clear

▸ **clear**(): *void*

*Defined in [types.d.ts:946](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L946)*

**`description`** Remove all clients from the group.

**Returns:** *void*

___

###  count

▸ **count**(): *number*

*Defined in [types.d.ts:986](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L986)*

**Returns:** *number*

Number of clients in group.

___

###  getClientName

▸ **getClientName**(`idx`: number): *string*

*Defined in [types.d.ts:963](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L963)*

**`description`** Get client name at the list index.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`idx` | number | The index of the clientName.  |

**Returns:** *string*

___

###  getName

▸ **getName**(): *string*

*Defined in [types.d.ts:951](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L951)*

**Returns:** *string*

The name of the group.

___

###  removeClient

▸ **removeClient**(`name`: string): *void*

*Defined in [types.d.ts:975](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L975)*

**`description`** Remove client from the gorup with the specified name.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`name` | string | The name of the client you want to remove.  |

**Returns:** *void*

___

###  removeClientbyID

▸ **removeClientbyID**(`idx`: number): *void*

*Defined in [types.d.ts:981](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L981)*

**`description`** Remove client at list index from the group.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`idx` | number | The Index of the client you want to remove.  |

**Returns:** *void*

___

###  setName

▸ **setName**(`newName`: string): *void*

*Defined in [types.d.ts:957](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L957)*

**`description`** Set the name of the group.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`newName` | string | The new name of the group.  |

**Returns:** *void*