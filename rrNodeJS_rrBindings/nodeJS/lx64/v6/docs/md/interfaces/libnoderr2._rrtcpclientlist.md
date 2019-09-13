**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2](../modules/libnoderr2.md) › [_rrTCPclientList](libnoderr2._rrtcpclientlist.md)

# Interface: _rrTCPclientList

## Hierarchy

* **_rrTCPclientList**

## Index

### Methods

* [at](libnoderr2._rrtcpclientlist.md#at)
* [clientStatus](libnoderr2._rrtcpclientlist.md#clientstatus)
* [count](libnoderr2._rrtcpclientlist.md#count)

## Methods

###  at

▸ **at**(`clientID`: number): *[_ClientStatus](client._clientstatus.md)*

*Defined in [types.d.ts:332](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L332)*

**`description`** Retrieves a client by its ID from the rrServer

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`clientID` | number | the clientID of the client we want to investigate further  |

**Returns:** *[_ClientStatus](client._clientstatus.md)*

___

###  clientStatus

▸ **clientStatus**(`clientID`: number): *string*

*Defined in [types.d.ts:341](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L341)*

**`description`** Retrieves the current status of the specified client

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`clientID` | number | The clientID of the client we want to investigate further  |

**Returns:** *string*

___

###  count

▸ **count**(): *number*

*Defined in [types.d.ts:336](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L336)*

**`description`** Fetches the amount of registered clients which were returned by the clientGetList() function

**Returns:** *number*