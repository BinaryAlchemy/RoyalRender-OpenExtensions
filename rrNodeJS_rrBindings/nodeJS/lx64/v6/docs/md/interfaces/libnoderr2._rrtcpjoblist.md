**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2](../modules/libnoderr2.md) › [_rrTCPjobList](libnoderr2._rrtcpjoblist.md)

# Interface: _rrTCPjobList

## Hierarchy

* **_rrTCPjobList**

## Index

### Methods

* [getJobBasic](libnoderr2._rrtcpjoblist.md#getjobbasic)
* [getJobDataType](libnoderr2._rrtcpjoblist.md#getjobdatatype)
* [getJobMinInfo](libnoderr2._rrtcpjoblist.md#getjobmininfo)
* [getJobMinInfo_filterQueue](libnoderr2._rrtcpjoblist.md#getjobmininfo_filterqueue)
* [getJobMinInfo_queue](libnoderr2._rrtcpjoblist.md#getjobmininfo_queue)
* [getJobSend](libnoderr2._rrtcpjoblist.md#getjobsend)
* [getJobUpdatedTime](libnoderr2._rrtcpjoblist.md#getjobupdatedtime)
* [getMaxJobs](libnoderr2._rrtcpjoblist.md#getmaxjobs)
* [getMaxJobsFiltered](libnoderr2._rrtcpjoblist.md#getmaxjobsfiltered)

## Methods

###  getJobBasic

▸ **getJobBasic**(`jobID`: [rrUint64](utils.rruint64.md)): *[_JobBasics](job._jobbasics.md)*

*Defined in [types.d.ts:251](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L251)*

**`description`** If there is no _JobBasics for this job, then an empty job is returned. It has some fields like scene name set to ??..

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`jobID` | [rrUint64](utils.rruint64.md) | ID of the job you want to get the basic info from. |

**Returns:** *[_JobBasics](job._jobbasics.md)*

The basic information of a Job.

___

###  getJobDataType

▸ **getJobDataType**(`jobID`: [rrUint64](utils.rruint64.md)): *[_EdataIDs](libnoderr2._edataids.md)*

*Defined in [types.d.ts:237](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L237)*

**`description`** Tells you which data class is currently available for that job.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`jobID` | [rrUint64](utils.rruint64.md) | The ID of the job you want to know the DataType of. |

**Returns:** *[_EdataIDs](libnoderr2._edataids.md)*

one of the following _dataIDs enums as number values: jlNone  |   jlMinInfo   |   jlBasic   |   jlSend

___

###  getJobMinInfo

▸ **getJobMinInfo**(`jobID`: [rrUint64](utils.rruint64.md)): *[_JobMinInfo](job._jobmininfo.md)*

*Defined in [types.d.ts:244](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L244)*

**`description`** Fetches the MinInfo of a job from the rrServer.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`jobID` | [rrUint64](utils.rruint64.md) | ID of the job you want to get the min info from. |

**Returns:** *[_JobMinInfo](job._jobmininfo.md)*

The minimum information of a Job.

___

###  getJobMinInfo_filterQueue

▸ **getJobMinInfo_filterQueue**(`ID`: number): *[_JobMinInfo](job._jobmininfo.md)*

*Defined in [types.d.ts:289](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L289)*

**`description`** for a loop with getMaxJobsFiltered().

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`ID` | number | queueID |

**Returns:** *[_JobMinInfo](job._jobmininfo.md)*

a _JobMinInfo Object

___

###  getJobMinInfo_queue

▸ **getJobMinInfo_queue**(`ID`: number): *[_JobMinInfo](job._jobmininfo.md)*

*Defined in [types.d.ts:277](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L277)*

**`description`** for a loop with getMaxJobs().

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`ID` | number | the queueID |

**Returns:** *[_JobMinInfo](job._jobmininfo.md)*

NULL if queueID is invalid, else a _JobMinInfo Object

___

###  getJobSend

▸ **getJobSend**(`jobID`: [rrUint64](utils.rruint64.md)): *[_JobSend](job._jobsend.md)*

*Defined in [types.d.ts:258](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L258)*

**`description`** If there is no _JobSend for this job, then it returns getJobBasic().

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`jobID` | [rrUint64](utils.rruint64.md) | ID of the send job. |

**Returns:** *[_JobSend](job._jobsend.md)*

The job which has been send.

___

###  getJobUpdatedTime

▸ **getJobUpdatedTime**(`jobID`: [rrUint64](utils.rruint64.md)): *Date*

*Defined in [types.d.ts:265](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L265)*

**`description`** Returns the time this job object was updated by jobGetInfoBasic() or jobGetInfoSend(). The time is the rrServer time. Note: This is not the last time the job was changed. Use job.lastSettingsChanged or job.lastInfoChanged to get that information.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`jobID` | [rrUint64](utils.rruint64.md) | ID of the job you want to get the updated Time for. |

**Returns:** *Date*

the time this job object was updated by jobGetInfoBasic() or jobGetInfoSend().

___

###  getMaxJobs

▸ **getMaxJobs**(): *number*

*Defined in [types.d.ts:270](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L270)*

**Returns:** *number*

Total number of jobs in RR.

___

###  getMaxJobsFiltered

▸ **getMaxJobsFiltered**(): *number*

*Defined in [types.d.ts:282](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L282)*

**Returns:** *number*

Total number of jobs in your filtered list