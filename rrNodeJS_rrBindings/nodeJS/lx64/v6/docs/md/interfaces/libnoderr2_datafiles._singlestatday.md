**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_singleStatDay](libnoderr2_datafiles._singlestatday.md)

# Interface: _singleStatDay

## Hierarchy

* **_singleStatDay**

## Index

### Properties

* [name](libnoderr2_datafiles._singlestatday.md#name)
* [type](libnoderr2_datafiles._singlestatday.md#type)

### Methods

* [stats](libnoderr2_datafiles._singlestatday.md#stats)
* [statsMax](libnoderr2_datafiles._singlestatday.md#statsmax)

## Properties

###  name

• **name**: *string*

*Defined in [types.d.ts:472](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L472)*

**`description`** Name of the user, project or render app.

___

###  type

• **type**: *number*

*Defined in [types.d.ts:477](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L477)*

**`description`** 0 -> User stats, 1 -> Project stats, 2 -> Render app stats

## Methods

###  stats

▸ **stats**(`idx`: number): *[_singleStat](libnoderr2_datafiles._singlestat.md)*

*Defined in [types.d.ts:483](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L483)*

**`description`** Each array item contains the stats for 15 minutes of that day: 0: 00:00- 00:15 1: 00:15- 00:30 2: 00:30- 00:45 ...

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`idx` | number | Array idx of the statistics data.  |

**Returns:** *[_singleStat](libnoderr2_datafiles._singlestat.md)*

___

###  statsMax

▸ **statsMax**(): *number*

*Defined in [types.d.ts:488](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L488)*

**Returns:** *number*

The maximum number of possible _singleStat values. It always returns 96 for this RR version. (24h/96 = 15 min)