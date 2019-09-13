**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [Client](../modules/client.md) › [_ClientStatusThread](client._clientstatusthread.md)

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

*Defined in [types.d.ts:2284](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2284)*

___

###  jobCPU_Usage

• **jobCPU_Usage**: *number*

*Defined in [types.d.ts:2285](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2285)*

___

###  jobID

• **jobID**: *[rrUint64](utils.rruint64.md)*

*Defined in [types.d.ts:2246](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2246)*

___

###  jobIsPreview

• **jobIsPreview**: *boolean*

*Defined in [types.d.ts:2282](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2282)*

___

###  jobMemoryUsageMB

• **jobMemoryUsageMB**: *number*

*Defined in [types.d.ts:2286](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2286)*

___

###  jobMultiFrameID

• **jobMultiFrameID**: *number*

*Defined in [types.d.ts:2281](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2281)*

**`description`** Tile id.

___

###  jobSeqEnd

• **jobSeqEnd**: *number*

*Defined in [types.d.ts:2261](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2261)*

**`description`** End frame of the current segment as frame number and internal job number.

___

###  jobSeqEndJobNr

• **jobSeqEndJobNr**: *number*

*Defined in [types.d.ts:2266](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2266)*

**`description`** End frame of the current segment as frame number and internal job number.

___

###  jobSeqStart

• **jobSeqStart**: *number*

*Defined in [types.d.ts:2251](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2251)*

**`description`** Start frame of the current segment as frame number and internal job number.

___

###  jobSeqStartJobNr

• **jobSeqStartJobNr**: *number*

*Defined in [types.d.ts:2256](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2256)*

**`description`** Start frame of the current segment as frame number and internal job number.

___

###  jobSeqStep

• **jobSeqStep**: *number*

*Defined in [types.d.ts:2271](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2271)*

**`description`** Frame step of the current segment as frame number and internal job number.

___

###  jobSeqStepJobNr

• **jobSeqStepJobNr**: *number*

*Defined in [types.d.ts:2276](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2276)*

**`description`** Frame step of the current segment as frame number and internal job number.

___

###  jobStatus

• **jobStatus**: *number*

*Defined in [types.d.ts:2283](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2283)*

## Methods

###  clientStatusAsStringSingle

▸ **clientStatusAsStringSingle**(): *string*

*Defined in [types.d.ts:2301](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2301)*

**Returns:** *string*

The clientStatus+jobstatus of the thread as string.

___

###  hasKSOLoaded

▸ **hasKSOLoaded**(): *boolean*

*Defined in [types.d.ts:2291](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2291)*

**Returns:** *boolean*

True if the thread is keeping a scene in memory.

___

###  isRendering

▸ **isRendering**(): *boolean*

*Defined in [types.d.ts:2296](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2296)*

**Returns:** *boolean*

True if the thread is rendering.