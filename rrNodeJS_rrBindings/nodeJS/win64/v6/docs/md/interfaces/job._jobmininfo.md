[rrBindingsDocs](../README.md) › [Job](../modules/job.md) › [_JobMinInfo](job._jobmininfo.md)

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

*Defined in [types.d.ts:1370](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1370)*

**`description`** The job ID

___

###  companyProjectName

• **companyProjectName**: *string*

*Defined in [types.d.ts:1380](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1380)*

**`description`** The company project of the job

___

###  filterMask

• **filterMask**: *number*

*Defined in [types.d.ts:1395](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1395)*

**`description`** A bit mask for different job states: 1 -> Not Rendering, 2 -> Rendering, 4 -> Disabled, 8 -> Wait for..., 16 -> Finished - See _filterIDs for equivalent data.

___

###  queueIDAtServer

• **queueIDAtServer**: *number*

*Defined in [types.d.ts:1390](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1390)*

**`description`** All jobs have a queue ID which starts at 0. Deleting/Moving jobs changes the queueID.

___

###  rendererName

• **rendererName**: *string*

*Defined in [types.d.ts:1385](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1385)*

**`description`** The name of the render application (Softimage, Nuke, ...)

___

###  userName

• **userName**: *string*

*Defined in [types.d.ts:1375](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1375)*

**`description`** The user who has send the job

## Methods

###  IDstr

▸ **IDstr**(): *string*

*Defined in [types.d.ts:1400](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1400)*

**Returns:** *string*

ID of the job as human readable/remember-able string E.g. {D5Ca}.
