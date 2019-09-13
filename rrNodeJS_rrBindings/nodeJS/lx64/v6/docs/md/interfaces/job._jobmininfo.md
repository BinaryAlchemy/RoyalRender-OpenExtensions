**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [Job](../modules/job.md) › [_JobMinInfo](job._jobmininfo.md)

# Interface: _JobMinInfo

## Hierarchy

* **_JobMinInfo**

## Index

### Properties

* [ID](job._jobmininfo.md#id)
* [companyProjectName](job._jobmininfo.md#companyprojectname)
* [filterMask](job._jobmininfo.md#filtermask)
* [queueIDAtServer](job._jobmininfo.md#queueidatserver)
* [rendererName](job._jobmininfo.md#renderername)
* [userName](job._jobmininfo.md#username)

### Methods

* [IDstr](job._jobmininfo.md#idstr)

## Properties

###  ID

• **ID**: *[rrUint64](utils.rruint64.md)*

*Defined in [types.d.ts:1369](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1369)*

**`description`** The job ID

___

###  companyProjectName

• **companyProjectName**: *string*

*Defined in [types.d.ts:1379](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1379)*

**`description`** The company project of the job

___

###  filterMask

• **filterMask**: *number*

*Defined in [types.d.ts:1394](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1394)*

**`description`** A bit mask for different job states: 1 -> Not Rendering, 2 -> Rendering, 4 -> Disabled, 8 -> Wait for..., 16 -> Finished - See _filterIDs for equivalent data.

___

###  queueIDAtServer

• **queueIDAtServer**: *number*

*Defined in [types.d.ts:1389](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1389)*

**`description`** All jobs have a queue ID which starts at 0. Deleting/Moving jobs changes the queueID.

___

###  rendererName

• **rendererName**: *string*

*Defined in [types.d.ts:1384](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1384)*

**`description`** The name of the render application (Softimage, Nuke, ...)

___

###  userName

• **userName**: *string*

*Defined in [types.d.ts:1374](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1374)*

**`description`** The user who has send the job

## Methods

###  IDstr

▸ **IDstr**(): *string*

*Defined in [types.d.ts:1399](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1399)*

**Returns:** *string*

ID of the job as human readable/remember-able string E.g. {D5Ca}.