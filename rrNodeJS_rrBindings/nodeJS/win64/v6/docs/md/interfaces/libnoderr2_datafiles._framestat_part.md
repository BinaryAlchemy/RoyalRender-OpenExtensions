**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_frameStat_part](libnoderr2_datafiles._framestat_part.md)

# Interface: _frameStat_part

## Hierarchy

* **_frameStat_part**

## Index

### Properties

* [jobCPU](libnoderr2_datafiles._framestat_part.md#jobcpu)
* [jobMemoryMB](libnoderr2_datafiles._framestat_part.md#jobmemorymb)
* [nonJobCPU](libnoderr2_datafiles._framestat_part.md#nonjobcpu)
* [renderThreads](libnoderr2_datafiles._framestat_part.md#renderthreads)

## Properties

###  jobCPU

• **jobCPU**: *number*

*Defined in [types.d.ts:891](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L891)*

**`returns`** CPU usage of the job.

___

###  jobMemoryMB

• **jobMemoryMB**: *number*

*Defined in [types.d.ts:886](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L886)*

**`returns`** Memory usage of job.

___

###  nonJobCPU

• **nonJobCPU**: *number*

*Defined in [types.d.ts:896](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L896)*

**`returns`** Other CPU usage of the machine.

___

###  renderThreads

• **renderThreads**: *number*

*Defined in [types.d.ts:901](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L901)*

**`returns`** Number of job threads rendering on the client at this moment.