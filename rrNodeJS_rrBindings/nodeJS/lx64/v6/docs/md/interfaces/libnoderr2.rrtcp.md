**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2](../modules/libnoderr2.md) › [rrTCP](libnoderr2.rrtcp.md)

# Interface: rrTCP

## Hierarchy

* **rrTCP**

## Index

### Properties

* [clients](libnoderr2.rrtcp.md#clients)
* [jobs](libnoderr2.rrtcp.md#jobs)
* [users](libnoderr2.rrtcp.md#users)

### Methods

* [clientGetList](libnoderr2.rrtcp.md#clientgetlist)
* [clientSendCommand](libnoderr2.rrtcp.md#clientsendcommand)
* [connectionStats](libnoderr2.rrtcp.md#connectionstats)
* [connectionStatsJSON](libnoderr2.rrtcp.md#connectionstatsjson)
* [errorMessage](libnoderr2.rrtcp.md#errormessage)
* [getGlobalInfo](libnoderr2.rrtcp.md#getglobalinfo)
* [getMemUsage](libnoderr2.rrtcp.md#getmemusage)
* [getRRServer](libnoderr2.rrtcp.md#getrrserver)
* [jobGetInfoBasic](libnoderr2.rrtcp.md#jobgetinfobasic)
* [jobGetInfoSend](libnoderr2.rrtcp.md#jobgetinfosend)
* [jobModify](libnoderr2.rrtcp.md#jobmodify)
* [jobSendCommand](libnoderr2.rrtcp.md#jobsendcommand)
* [jobSetFilter](libnoderr2.rrtcp.md#jobsetfilter)
* [jobSubmitNew](libnoderr2.rrtcp.md#jobsubmitnew)
* [lastUpdateJobs_OurTime](libnoderr2.rrtcp.md#lastupdatejobs_ourtime)
* [lastUpdateJobs_ServerTime](libnoderr2.rrtcp.md#lastupdatejobs_servertime)
* [setLogin](libnoderr2.rrtcp.md#setlogin)
* [setServer](libnoderr2.rrtcp.md#setserver)
* [userGet](libnoderr2.rrtcp.md#userget)
* [userModify](libnoderr2.rrtcp.md#usermodify)
* [userNew](libnoderr2.rrtcp.md#usernew)

## Properties

###  clients

• **clients**: *[_rrTCPclientList](libnoderr2._rrtcpclientlist.md)*

*Defined in [types.d.ts:32](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L32)*

**`description`** Requires to call  clientGetList() first.

___

###  jobs

• **jobs**: *[_rrTCPjobList](libnoderr2._rrtcpjoblist.md)*

*Defined in [types.d.ts:27](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L27)*

**`description`** Requires to call any jobGet..() function.

___

###  users

• **users**: *[_rrTCPuser](libnoderr2._rrtcpuser.md)*

*Defined in [types.d.ts:37](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L37)*

**`description`** Requires to call userGet() first.

## Methods

###  clientGetList

▸ **clientGetList**(): *boolean*

*Defined in [types.d.ts:154](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L154)*

**`description`** gets all the registered clients from the rrServer and stores it into the clients property of the rrTCP

**Returns:** *boolean*

boolean

___

###  clientSendCommand

▸ **clientSendCommand**(`clientArray`: number[], `ID`: [_EClientCommand](rrglobal._eclientcommand.md), `param?`: undefined | string): *boolean*

*Defined in [types.d.ts:163](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L163)*

**`description`** Sends a command to rrClients. clientArray is a list with client IDs. If the list has only one element and the ID is -1, then the command is applied to all clients. param is an optional string parameter. It can be used to send commandlines to the client with the commandID _rrTCP._ClientCommand.cCommandLine If the function returns false, then please check errorMessage().

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`clientArray` | number[] | An array of client IDs which should receive the new command. |
`ID` | [_EClientCommand](rrglobal._eclientcommand.md) | The ClientCommandID of the Command which should be send to the clients. |
`param?` | undefined \| string | Additional parameters which should be send with the new command. |

**Returns:** *boolean*

true if the operation succeeded.

___

###  connectionStats

▸ **connectionStats**(): *string*

*Defined in [types.d.ts:81](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L81)*

**`description`** Information about the last connections.

**Returns:** *string*

___

###  connectionStatsJSON

▸ **connectionStatsJSON**(): *string*

*Defined in [types.d.ts:86](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L86)*

**`description`** Information about the last connections.

**Returns:** *string*

___

###  errorMessage

▸ **errorMessage**(): *string*

*Defined in [types.d.ts:65](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L65)*

**`description`** If there was any error, then this function will return a non-empty string. Else it will return undefined.

**Returns:** *string*

An error message for more detail

___

###  getGlobalInfo

▸ **getGlobalInfo**(): *[_rrGlobalInfo](libnoderr2._rrglobalinfo.md)*

*Defined in [types.d.ts:70](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L70)*

**Returns:** *[_rrGlobalInfo](libnoderr2._rrglobalinfo.md)*

_rrGlobalInfo Object - Global info about the rrServer Application like how many WOlAble Clients there are, etc.

___

###  getMemUsage

▸ **getMemUsage**(): *number*

*Defined in [types.d.ts:76](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L76)*

**`description`** Returns the current memory usage of _rrTCP.

**Returns:** *number*

string

___

###  getRRServer

▸ **getRRServer**(): *string*

*Defined in [types.d.ts:44](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L44)*

**`description`** This function tries to get the rrServer name or IP from the RR folder in your company. It uses the RR_ROOT environment variable installed by rrWorkstationInstaller. Therefore it does only work in your company. If you want to connect from outside your company, you have to use a DynDNS service.

**Returns:** *string*

___

###  jobGetInfoBasic

▸ **jobGetInfoBasic**(`jobID?`: [rrUint64](utils.rruint64.md)): *boolean*

*Defined in [types.d.ts:103](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L103)*

**`description`** You should call jobSetFilter() first to get only jobs with that you need to reduce network traffic. 1.Retrieves the job info of job with {ID} jobID. If jobID is 0, then it updates all jobs that match the filter. 2. Retrieves _MinInfo of all jobs.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`jobID?` | [rrUint64](utils.rruint64.md) | the JobID of a specific Job you want to fetch from the server  |

**Returns:** *boolean*

___

###  jobGetInfoSend

▸ **jobGetInfoSend**(`jobID?`: [rrUint64](utils.rruint64.md)): *boolean*

*Defined in [types.d.ts:109](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L109)*

**`description`** You should call jobSetFilter() first to get only jobs with that you need to reduce network traffic. 1.Retrieves the job detail of job with {ID} jobID. If jobID is 0, then it updates all jobs that match the filter. 2. Retrieves _MinInfo of all jobs.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`jobID?` | [rrUint64](utils.rruint64.md) | the JobID of a specific Job you want to fetch from the server - HANGS WHEN USED  |

**Returns:** *boolean*

___

###  jobModify

▸ **jobModify**(`jobID`: [rrUint64](utils.rruint64.md)[], `settings`: [_SettingsOnly](job._settingsonly.md), `changeFlags`: [_SettingsOnly](job._settingsonly.md)): *boolean*

*Defined in [types.d.ts:127](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L127)*

**`description`** jobIDs is a list with JobIDs of jobs that you want to change. You need to call rrJob.getClass_SettingsOnly() to get a _SettingsOnly class. This function uses two _SettingsOnly classes. The settings parameter is the one with all the new values you want to set. The changeFlags tells RR which parameters you want to change. E.g. if you want to change the user name for all jobs, but all jobs should keep their sequence start-end. To let RR know that you want to change this value, just assign a value to them. (bool values to true, integer to 1, strings to e.g. "1".) If the function returns false, then please check errorMessage().

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`jobID` | [rrUint64](utils.rruint64.md)[] | A JobID Array which describes the jobs you want to modify |
`settings` | [_SettingsOnly](job._settingsonly.md) | The new properties for the specified jobs |
`changeFlags` | [_SettingsOnly](job._settingsonly.md) | Defines what should be changed in the specified jobs (e.g.: username, but not job sequence) |

**Returns:** *boolean*

true if the operation succeeded

___

###  jobSendCommand

▸ **jobSendCommand**(`jobIDs`: [rrUint64](utils.rruint64.md)[], `commandID`: number, `parameter`: number): *boolean*

*Defined in [types.d.ts:118](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L118)*

**`description`** jobIDs is a list with JobIDs of jobs that you want to send a command to. Please check errorMessage() if the function returns false.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`jobIDs` | [rrUint64](utils.rruint64.md)[] | A JobID Array which describes the jobs you want to send a command to |
`commandID` | number | The _logMessage enum which describes the command you want to send the jobs |
`parameter` | number | Additional Parameter for the jobSendCommand function |

**Returns:** *boolean*

true if the operation succeeded

___

###  jobSetFilter

▸ **jobSetFilter**(`jobUserName?`: undefined | string, `project?`: undefined | string, `renderApp?`: undefined | string, `jobContains?`: undefined | string, `filterID?`: undefined | number): *void*

*Defined in [types.d.ts:97](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L97)*

**`description`** jobSetFilter() controls which jobs are send from the rrServer. You should always use this if you have a lot of jobs in the queue to reduce network traffic, rrServer workload and python memory usage. Filter is a bit mask of enumeration _filterIDs values. Use | to combine multiple filters.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`jobUserName?` | undefined \| string | User name of the searched job |
`project?` | undefined \| string | Name of the whole Project |
`renderApp?` | undefined \| string | Name of the renderApp which is used |
`jobContains?` | undefined \| string | Substring of the searched Jobname |
`filterID?` | undefined \| number | a _filterID property which mimiks a bit mask - NOT YET IMPLEMENTED IN NODE ADDON  |

**Returns:** *void*

___

###  jobSubmitNew

▸ **jobSubmitNew**(`newJob`: [_JobBasics](job._jobbasics.md), `overrideParameter`: string): *boolean*

*Defined in [types.d.ts:135](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L135)*

**`description`** Submits a new job to the rrServer. We recommend that you use .xml files and use the rrSubmitterconsole. As the rrSubmitterconsole does many checks and conversions. Use this function only if you know all required settings for your jobs (e.g. imageFileNameVariables for Maya jobs) See RR/SDK/external/submit.py for an example script.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`newJob` | [_JobBasics](job._jobbasics.md) | a _JobBasics object which defines the job you want to add to rrServer |
`overrideParameter` | string | Additional parameters which should be passed to RR when submitted |

**Returns:** *boolean*

true if the operation succeeded

___

###  lastUpdateJobs_OurTime

▸ **lastUpdateJobs_OurTime**(): *Date*

*Defined in [types.d.ts:147](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L147)*

**`description`** Returns the time this machine had had when jobGetInfoBasic() or jobGetInfoSend() was called.

**Returns:** *Date*

The time the rrServer had when jobGetInfoBasic() or jobGetInfoSend() was called.

___

###  lastUpdateJobs_ServerTime

▸ **lastUpdateJobs_ServerTime**(): *Date*

*Defined in [types.d.ts:141](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L141)*

**`description`** Returns the time the rrServer had when jobGetInfoBasic() or jobGetInfoSend() was called. If it was copied before the job list was retrieved, then it can be used to check which was changed.

**Returns:** *Date*

The time the rrServer had when jobGetInfoBasic() or jobGetInfoSend() was called.

___

###  setLogin

▸ **setLogin**(`user`: string, `password`: string): *void*

*Defined in [types.d.ts:59](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L59)*

**`description`** Sets the login to retrieve any data from the rrServer. This is not required if you have setup a Intranet Whitelist in rrConfig, tab rrLogins.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`user` | string | The Username you want to log into |
`password` | string | the password of the specified user  |

**Returns:** *void*

___

###  setServer

▸ **setServer**(`ip`: string, `port`: number): *boolean*

*Defined in [types.d.ts:52](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L52)*

**`description`** Sets the server IP or name for all TCP connections.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`ip` | string | The rrServer IP |
`port` | number | The rrServer port |

**Returns:** *boolean*

boolean

___

###  userGet

▸ **userGet**(`input`: string): *boolean*

*Defined in [types.d.ts:171](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L171)*

**`description`** Gets all or only a specified user. The result of this request is filled into the .user parameter.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`input` | string | IMPORTANT: Needs a non-zero String |

**Returns:** *boolean*

true if the operation succeeded - stores all Users in tcp.users

___

###  userModify

▸ **userModify**(`user`: [rrUserSettings](libnoderr2.rrusersettings.md)): *boolean*

*Defined in [types.d.ts:178](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L178)*

**`description`** After you retrieved a _rrTCPuser class and changed a few values, you have to send that user back to the rrServer/rrConfig. If the password is empty, then it will not be changed by the rrServer. Returns false if there was an error. Use userWasPartialFail() (NOT YET IMPLEMENTED IN NODE ADDON) to know if all settings have been applied. The rrServer sends the user class back with the current values.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`user` | [rrUserSettings](libnoderr2.rrusersettings.md) | The modified user Object |

**Returns:** *boolean*

true if the operation succeeded

___

###  userNew

▸ **userNew**(`user`: [rrUserSettings](libnoderr2.rrusersettings.md)): *boolean*

*Defined in [types.d.ts:185](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L185)*

**`description`** After you got a new user via getNewUserPreset(), you have to send it to the rrServer/rrConfig. Returns false if there was an error. Use userWasPartialFail() (NOT YET IMPLEMENTED IN NODE ADDON) to know if all settings have been applied. The rrServer sends the user class back with the current values.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`user` | [rrUserSettings](libnoderr2.rrusersettings.md) | The new user which should be added to the rrServer |

**Returns:** *boolean*

true if the operation succeeded