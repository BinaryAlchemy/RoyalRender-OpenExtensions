[rrBindingsDocs](../README.md) › [Client](../modules/client.md) › [_ClientStatusThread](client._clientstatusthread.md)

# Interface: _ClientStatusThread

## Hierarchy

* **_ClientStatusThread**

## Index

### Properties

* [clientStatus](client._clientstatusthread.md#clientstatus)
* [jobCPU_Usage](client._clientstatusthread.md#jobcpu_usage)
* [jobID](client._clientstatusthread.md#jobid)
* [jobIsPreview](client._clientstatusthread.md#jobispreview)
* [jobMemoryUsageMB](client._clientstatusthread.md#jobmemoryusagemb)
* [jobMultiFrameID](client._clientstatusthread.md#jobmultiframeid)
* [jobSeqEnd](client._clientstatusthread.md#jobseqend)
* [jobSeqEndJobNr](client._clientstatusthread.md#jobseqendjobnr)
* [jobSeqStart](client._clientstatusthread.md#jobseqstart)
* [jobSeqStartJobNr](client._clientstatusthread.md#jobseqstartjobnr)
* [jobSeqStep](client._clientstatusthread.md#jobseqstep)
* [jobSeqStepJobNr](client._clientstatusthread.md#jobseqstepjobnr)
* [jobStatus](client._clientstatusthread.md#jobstatus)

### Methods

* [clientStatusAsStringSingle](client._clientstatusthread.md#clientstatusasstringsingle)
* [hasKSOLoaded](client._clientstatusthread.md#hasksoloaded)
* [isRendering](client._clientstatusthread.md#isrendering)

## Properties

###  clientStatus

• **clientStatus**: *number*

*Defined in [types.d.ts:2283](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2283)*

___

###  jobCPU_Usage

• **jobCPU_Usage**: *number*

*Defined in [types.d.ts:2284](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2284)*

___

###  jobID

• **jobID**: *[rrUint64](utils.rruint64.md)*

*Defined in [types.d.ts:2245](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2245)*

___

###  jobIsPreview

• **jobIsPreview**: *boolean*

*Defined in [types.d.ts:2281](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2281)*

___

###  jobMemoryUsageMB

• **jobMemoryUsageMB**: *number*

*Defined in [types.d.ts:2285](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2285)*

___

###  jobMultiFrameID

• **jobMultiFrameID**: *number*

*Defined in [types.d.ts:2280](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2280)*

**`description`** Tile id.

___

###  jobSeqEnd

• **jobSeqEnd**: *number*

*Defined in [types.d.ts:2260](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2260)*

**`description`** End frame of the current segment as frame number and internal job number.

___

###  jobSeqEndJobNr

• **jobSeqEndJobNr**: *number*

*Defined in [types.d.ts:2265](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2265)*

**`description`** End frame of the current segment as frame number and internal job number.

___

###  jobSeqStart

• **jobSeqStart**: *number*

*Defined in [types.d.ts:2250](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2250)*

**`description`** Start frame of the current segment as frame number and internal job number.

___

###  jobSeqStartJobNr

• **jobSeqStartJobNr**: *number*

*Defined in [types.d.ts:2255](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2255)*

**`description`** Start frame of the current segment as frame number and internal job number.

___

###  jobSeqStep

• **jobSeqStep**: *number*

*Defined in [types.d.ts:2270](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2270)*

**`description`** Frame step of the current segment as frame number and internal job number.

___

###  jobSeqStepJobNr

• **jobSeqStepJobNr**: *number*

*Defined in [types.d.ts:2275](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2275)*

**`description`** Frame step of the current segment as frame number and internal job number.

___

###  jobStatus

• **jobStatus**: *number*

*Defined in [types.d.ts:2282](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2282)*

## Methods

###  clientStatusAsStringSingle

▸ **clientStatusAsStringSingle**(): *string*

*Defined in [types.d.ts:2300](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2300)*

**Returns:** *string*

The clientStatus+jobstatus of the thread as string.

___

###  hasKSOLoaded

▸ **hasKSOLoaded**(): *boolean*

*Defined in [types.d.ts:2290](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2290)*

**Returns:** *boolean*

True if the thread is keeping a scene in memory.

___

###  isRendering

▸ **isRendering**(): *boolean*

*Defined in [types.d.ts:2295](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2295)*

**Returns:** *boolean*

True if the thread is rendering.
