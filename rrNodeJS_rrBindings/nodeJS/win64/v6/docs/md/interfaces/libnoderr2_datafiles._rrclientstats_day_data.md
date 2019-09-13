**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_rrClientStats_day_data](libnoderr2_datafiles._rrclientstats_day_data.md)

# Interface: _rrClientStats_day_data

## Hierarchy

* **_rrClientStats_day_data**

## Index

### Properties

* [cpuTotal](libnoderr2_datafiles._rrclientstats_day_data.md#cputotal)
* [memTotal10MB](libnoderr2_datafiles._rrclientstats_day_data.md#memtotal10mb)
* [userLoggedIn](libnoderr2_datafiles._rrclientstats_day_data.md#userloggedin)

### Methods

* [jobThread](libnoderr2_datafiles._rrclientstats_day_data.md#jobthread)
* [jobThreadMax](libnoderr2_datafiles._rrclientstats_day_data.md#jobthreadmax)

## Properties

###  cpuTotal

• **cpuTotal**: *number*

*Defined in [types.d.ts:740](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L740)*

**`description`** CPU usage as percentage of the system. The value is exported as float (1.0 = 100%).

___

###  memTotal10MB

• **memTotal10MB**: *number*

*Defined in [types.d.ts:745](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L745)*

**`description`** Total memory usage in MiB, divided by 10.

___

###  userLoggedIn

• **userLoggedIn**: *boolean*

*Defined in [types.d.ts:735](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L735)*

**`description`** Was a user logged in?

## Methods

###  jobThread

▸ **jobThread**(): *[_rrClientStats_day_data_jobthread](libnoderr2_datafiles._rrclientstats_day_data_jobthread.md)*

*Defined in [types.d.ts:750](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L750)*

**Returns:** *[_rrClientStats_day_data_jobthread](libnoderr2_datafiles._rrclientstats_day_data_jobthread.md)*

The data of a job thread.

___

###  jobThreadMax

▸ **jobThreadMax**(): *number*

*Defined in [types.d.ts:755](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L755)*

**Returns:** *number*

The number of job threads the client was running in this time slot.