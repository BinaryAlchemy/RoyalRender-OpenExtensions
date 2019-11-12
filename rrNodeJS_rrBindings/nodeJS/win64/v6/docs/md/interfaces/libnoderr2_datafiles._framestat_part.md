[rrBindingsDocs](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_frameStat_part](libnoderr2_datafiles._framestat_part.md)

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

*Defined in [types.d.ts:892](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L892)*

**`returns`** CPU usage of the job.

___

###  jobMemoryMB

• **jobMemoryMB**: *number*

*Defined in [types.d.ts:887](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L887)*

**`returns`** Memory usage of job.

___

###  nonJobCPU

• **nonJobCPU**: *number*

*Defined in [types.d.ts:897](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L897)*

**`returns`** Other CPU usage of the machine.

___

###  renderThreads

• **renderThreads**: *number*

*Defined in [types.d.ts:902](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L902)*

**`returns`** Number of job threads rendering on the client at this moment.
