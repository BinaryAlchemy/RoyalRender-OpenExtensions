**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2](../modules/libnoderr2.md) › [_rrTCPuser](libnoderr2._rrtcpuser.md)

# Interface: _rrTCPuser

## Hierarchy

* **_rrTCPuser**

## Index

### Methods

* [at](libnoderr2._rrtcpuser.md#at)
* [count](libnoderr2._rrtcpuser.md#count)
* [getAnonymous](libnoderr2._rrtcpuser.md#getanonymous)
* [getNewUserPreset](libnoderr2._rrtcpuser.md#getnewuserpreset)
* [getOurUser](libnoderr2._rrtcpuser.md#getouruser)

## Methods

###  at

▸ **at**(`userID`: number): *[rrUserSettings](libnoderr2.rrusersettings.md)*

*Defined in [types.d.ts:193](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L193)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`userID` | number | ID of the user you want to get - int |

**Returns:** *[rrUserSettings](libnoderr2.rrusersettings.md)*

a user from the tcp.users list

___

###  count

▸ **count**(): *number*

*Defined in [types.d.ts:213](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L213)*

**Returns:** *number*

the number of users currently known in rrServer

___

###  getAnonymous

▸ **getAnonymous**(): *[rrUserSettings](libnoderr2.rrusersettings.md)*

*Defined in [types.d.ts:203](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L203)*

**Returns:** *[rrUserSettings](libnoderr2.rrusersettings.md)*

a new anonymous user preset

___

###  getNewUserPreset

▸ **getNewUserPreset**(): *[rrUserSettings](libnoderr2.rrusersettings.md)*

*Defined in [types.d.ts:198](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L198)*

**Returns:** *[rrUserSettings](libnoderr2.rrusersettings.md)*

a new user Preset

___

###  getOurUser

▸ **getOurUser**(): *[rrUserSettings](libnoderr2.rrusersettings.md)*

*Defined in [types.d.ts:208](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L208)*

**Returns:** *[rrUserSettings](libnoderr2.rrusersettings.md)*

the currently logged in user