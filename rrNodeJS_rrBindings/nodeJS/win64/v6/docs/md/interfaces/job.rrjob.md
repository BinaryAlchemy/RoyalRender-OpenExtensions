**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [Job](../modules/job.md) › [rrJob](job.rrjob.md)

# Interface: rrJob

## Hierarchy

* **rrJob**

## Index

### Properties

* [_Status](job.rrjob.md#_status)
* [_logMessage](job.rrjob.md#_logmessage)
* [_rrOptions](job.rrjob.md#_rroptions)
* [_rrParam](job.rrjob.md#_rrparam)

### Methods

* [getClass_JobBasics](job.rrjob.md#getclass_jobbasics)
* [getClass_SettingsOnly](job.rrjob.md#getclass_settingsonly)

## Properties

###  _Status

• **_Status**: *[_Status](job._status.md)*

*Defined in [types.d.ts:1350](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1350)*

___

###  _logMessage

• **_logMessage**: *[_LogMessage](job._logmessage.md)*

*Defined in [types.d.ts:1335](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1335)*

**`description`** _LogMessage is used for all job log messages and for commands send to a job.

**`example`** 
var rrJob = rrbinding.createRRJob();
tcp.jobSendCommand(jobIDs, rrJob._logMessage.lEnable, 0)

___

###  _rrOptions

• **_rrOptions**: *[_RROptions](job._rroptions.md)*

*Defined in [types.d.ts:1342](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1342)*

**`example`** 
var rrJob = rrbinding.createRRJob();
rrJob.rrOption(rrJob._rrOptions.rroKeepSceneOpen);

___

###  _rrParam

• **_rrParam**: *[_RRParams](job._rrparams.md)*

*Defined in [types.d.ts:1349](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1349)*

**`example`** 
var rrJob = rrbinding.createRRJob();
rrJob.rrParam(rrJob._rrParam.rrpRequiredMemoryGB);

## Methods

###  getClass_JobBasics

▸ **getClass_JobBasics**(): *[_JobBasics](job._jobbasics.md)*

*Defined in [types.d.ts:1357](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1357)*

**Returns:** *[_JobBasics](job._jobbasics.md)*

A basic _JobBasics object with default values.

___

###  getClass_SettingsOnly

▸ **getClass_SettingsOnly**(): *[_SettingsOnly](job._settingsonly.md)*

*Defined in [types.d.ts:1363](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1363)*

**`description`** If you want to change job settings, then you have to use this class and send the rrServer a command with the new values.

**Returns:** *[_SettingsOnly](job._settingsonly.md)*

a basic _SettingsOnly object with default values.