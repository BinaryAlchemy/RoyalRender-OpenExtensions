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

*Defined in [types.d.ts:767](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L767)*

**`description`** CPU usage of this job. The value is exported as float (1.0 = 100%).

___

###  jobIDShort

• **jobIDShort**: *number*

*Defined in [types.d.ts:777](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L777)*

**`description`** The ID of the job in a shortened representation (The internal job ID in RR is usually a 64bit number. In this case truncated to 32bit only).

___

###  memRender10MB

• **memRender10MB**: *number*

*Defined in [types.d.ts:772](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L772)*

**`description`** Memory usage of the render job in MB, divided by 10.

___

###  status

• **status**: *number*

*Defined in [types.d.ts:762](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L762)*

**`description`** Job status. See enumeration _Status.

## Methods

###  jobIDShortStr

▸ **jobIDShortStr**(): *string*

*Defined in [types.d.ts:782](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L782)*

**Returns:** *string*

The jobIDShort as human readable string {ID}.