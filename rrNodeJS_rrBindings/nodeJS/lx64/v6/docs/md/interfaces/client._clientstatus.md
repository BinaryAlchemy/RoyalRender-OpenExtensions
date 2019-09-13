**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [Client](../modules/client.md) › [_ClientStatus](client._clientstatus.md)

# Interface: _ClientStatus

## Hierarchy

* **_ClientStatus**

## Index

### Properties

* [CPU_Usage](client._clientstatus.md#cpu_usage)
* [GPU_Usage](client._clientstatus.md#gpu_usage)
* [StructureID](client._clientstatus.md#structureid)
* [VariablesID](client._clientstatus.md#variablesid)
* [availMemoryMB](client._clientstatus.md#availmemorymb)
* [gpuTemperature](client._clientstatus.md#gputemperature)
* [isRunningAsService](client._clientstatus.md#isrunningasservice)
* [localTextureSpaceUsed](client._clientstatus.md#localtexturespaceused)
* [loggedUser](client._clientstatus.md#loggeduser)
* [maxCoresSetForJob](client._clientstatus.md#maxcoressetforjob)
* [maxJobThreads](client._clientstatus.md#maxjobthreads)
* [name](client._clientstatus.md#name)
* [noUserInteraction](client._clientstatus.md#nouserinteraction)
* [tempHDD](client._clientstatus.md#temphdd)
* [version](client._clientstatus.md#version)

### Methods

* [jobThread](client._clientstatus.md#jobthread)

## Properties

###  CPU_Usage

• **CPU_Usage**: *number*

*Defined in [types.d.ts:2222](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2222)*

___

###  GPU_Usage

• **GPU_Usage**: *number*

*Defined in [types.d.ts:2223](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2223)*

___

###  StructureID

• **StructureID**: *number*

*Defined in [types.d.ts:2218](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2218)*

___

###  VariablesID

• **VariablesID**: *number*

*Defined in [types.d.ts:2219](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2219)*

___

###  availMemoryMB

• **availMemoryMB**: *number*

*Defined in [types.d.ts:2226](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2226)*

___

###  gpuTemperature

• **gpuTemperature**: *number*

*Defined in [types.d.ts:2224](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2224)*

___

###  isRunningAsService

• **isRunningAsService**: *boolean*

*Defined in [types.d.ts:2225](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2225)*

___

###  localTextureSpaceUsed

• **localTextureSpaceUsed**: *number*

*Defined in [types.d.ts:2220](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2220)*

___

###  loggedUser

• **loggedUser**: *string*

*Defined in [types.d.ts:2227](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2227)*

___

###  maxCoresSetForJob

• **maxCoresSetForJob**: *number*

*Defined in [types.d.ts:2228](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2228)*

___

###  maxJobThreads

• **maxJobThreads**: *number*

*Defined in [types.d.ts:2221](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2221)*

___

###  name

• **name**: *string*

*Defined in [types.d.ts:2217](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2217)*

___

###  noUserInteraction

• **noUserInteraction**: *number*

*Defined in [types.d.ts:2233](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2233)*

**`description`** Minutes since last user interaction.

___

###  tempHDD

• **tempHDD**: *number*

*Defined in [types.d.ts:2235](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2235)*

___

###  version

• **version**: *string*

*Defined in [types.d.ts:2234](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2234)*

## Methods

###  jobThread

▸ **jobThread**(`threadID`: number): *[_ClientStatusThread](client._clientstatusthread.md)*

*Defined in [types.d.ts:2241](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L2241)*

**`description`** The render thread by ID. The maximum threadID is maxJobThreads.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`threadID` | number | ThreadID of the client status thread you want to fetch.  |

**Returns:** *[_ClientStatusThread](client._clientstatusthread.md)*