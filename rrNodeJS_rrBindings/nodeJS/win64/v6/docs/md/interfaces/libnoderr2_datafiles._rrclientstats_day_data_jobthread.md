**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_rrClientStats_day_data_jobthread](libnoderr2_datafiles._rrclientstats_day_data_jobthread.md)

# Interface: _rrClientStats_day_data_jobthread

## Hierarchy

* **_rrClientStats_day_data_jobthread**

## Index

### Properties

* [cpuRender](libnoderr2_datafiles._rrclientstats_day_data_jobthread.md#cpurender)
* [jobIDShort](libnoderr2_datafiles._rrclientstats_day_data_jobthread.md#jobidshort)
* [memRender10MB](libnoderr2_datafiles._rrclientstats_day_data_jobthread.md#memrender10mb)
* [status](libnoderr2_datafiles._rrclientstats_day_data_jobthread.md#status)

### Methods

* [jobIDShortStr](libnoderr2_datafiles._rrclientstats_day_data_jobthread.md#jobidshortstr)

## Properties

###  cpuRender

• **cpuRender**: *number*

*Defined in [types.d.ts:768](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L768)*

**`description`** CPU usage of this job. The value is exported as float (1.0 = 100%).

___

###  jobIDShort

• **jobIDShort**: *number*

*Defined in [types.d.ts:778](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L778)*

**`description`** The ID of the job in a shortened representation (The internal job ID in RR is usually a 64bit number. In this case truncated to 32bit only).

___

###  memRender10MB

• **memRender10MB**: *number*

*Defined in [types.d.ts:773](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L773)*

**`description`** Memory usage of the render job in MB, divided by 10.

___

###  status

• **status**: *number*

*Defined in [types.d.ts:763](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L763)*

**`description`** Job status. See enumeration _Status.

## Methods

###  jobIDShortStr

▸ **jobIDShortStr**(): *string*

*Defined in [types.d.ts:783](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L783)*

**Returns:** *string*

The jobIDShort as human readable string {ID}.