[rrBindingsDocs](../README.md) › [libNodeRR2](../modules/libnoderr2.md) › [_rrTCPuser](libnoderr2._rrtcpuser.md)

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

*Defined in [types.d.ts:194](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L194)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`userID` | number | ID of the user you want to get - int |

**Returns:** *[rrUserSettings](libnoderr2.rrusersettings.md)*

a user from the tcp.users list

___

###  count

▸ **count**(): *number*

*Defined in [types.d.ts:214](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L214)*

**Returns:** *number*

the number of users currently known in rrServer

___

###  getAnonymous

▸ **getAnonymous**(): *[rrUserSettings](libnoderr2.rrusersettings.md)*

*Defined in [types.d.ts:204](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L204)*

**Returns:** *[rrUserSettings](libnoderr2.rrusersettings.md)*

a new anonymous user preset

___

###  getNewUserPreset

▸ **getNewUserPreset**(): *[rrUserSettings](libnoderr2.rrusersettings.md)*

*Defined in [types.d.ts:199](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L199)*

**Returns:** *[rrUserSettings](libnoderr2.rrusersettings.md)*

a new user Preset

___

###  getOurUser

▸ **getOurUser**(): *[rrUserSettings](libnoderr2.rrusersettings.md)*

*Defined in [types.d.ts:209](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L209)*

**Returns:** *[rrUserSettings](libnoderr2.rrusersettings.md)*

the currently logged in user
