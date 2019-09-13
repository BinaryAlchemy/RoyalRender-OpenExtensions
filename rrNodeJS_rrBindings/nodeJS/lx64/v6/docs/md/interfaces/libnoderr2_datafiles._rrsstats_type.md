**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_rrsStats_type](libnoderr2_datafiles._rrsstats_type.md)

# Interface: _rrsStats_type

## Hierarchy

* **_rrsStats_type**

## Index

### Properties

* [av_frame_time](libnoderr2_datafiles._rrsstats_type.md#av_frame_time)
* [avclientTemperature](libnoderr2_datafiles._rrsstats_type.md#avclienttemperature)
* [client_rendering](libnoderr2_datafiles._rrsstats_type.md#client_rendering)
* [clients_disabled](libnoderr2_datafiles._rrsstats_type.md#clients_disabled)
* [clients_free](libnoderr2_datafiles._rrsstats_type.md#clients_free)
* [clients_needed](libnoderr2_datafiles._rrsstats_type.md#clients_needed)
* [cpuMachine](libnoderr2_datafiles._rrsstats_type.md#cpumachine)
* [cpuProcess](libnoderr2_datafiles._rrsstats_type.md#cpuprocess)
* [framesPer90s](libnoderr2_datafiles._rrsstats_type.md#framesper90s)
* [frames_to_do](libnoderr2_datafiles._rrsstats_type.md#frames_to_do)
* [jobBufferMemUsageJobs](libnoderr2_datafiles._rrsstats_type.md#jobbuffermemusagejobs)
* [jobs_rendering](libnoderr2_datafiles._rrsstats_type.md#jobs_rendering)
* [jobs_total](libnoderr2_datafiles._rrsstats_type.md#jobs_total)
* [jobs_unfinished](libnoderr2_datafiles._rrsstats_type.md#jobs_unfinished)
* [memUsageMachine](libnoderr2_datafiles._rrsstats_type.md#memusagemachine)
* [memUsageProcess](libnoderr2_datafiles._rrsstats_type.md#memusageprocess)
* [serverTemperature](libnoderr2_datafiles._rrsstats_type.md#servertemperature)
* [slot_used](libnoderr2_datafiles._rrsstats_type.md#slot_used)
* [tCPMemUsageData](libnoderr2_datafiles._rrsstats_type.md#tcpmemusagedata)
* [tCPMemUsageDataCompressed](libnoderr2_datafiles._rrsstats_type.md#tcpmemusagedatacompressed)
* [tCPMemUsageSocket](libnoderr2_datafiles._rrsstats_type.md#tcpmemusagesocket)

## Properties

###  av_frame_time

• **av_frame_time**: *number*

*Defined in [types.d.ts:669](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L669)*

**`description`** Average frame time of all jobs.

___

###  avclientTemperature

• **avclientTemperature**: *number*

*Defined in [types.d.ts:619](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L619)*

**`description`** Average temperature of the first HDD of all rrClients.

___

###  client_rendering

• **client_rendering**: *number*

*Defined in [types.d.ts:594](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L594)*

**`description`** Number of clients rendering.

___

###  clients_disabled

• **clients_disabled**: *number*

*Defined in [types.d.ts:599](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L599)*

**`description`** Number of disabled clients.

___

###  clients_free

• **clients_free**: *number*

*Defined in [types.d.ts:589](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L589)*

**`description`** Number of free clients.

___

###  clients_needed

• **clients_needed**: *number*

*Defined in [types.d.ts:579](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L579)*

**`description`** A estimate how many clients would be needed to start all unassigned frame segments.

___

###  cpuMachine

• **cpuMachine**: *number*

*Defined in [types.d.ts:609](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L609)*

**`description`** CPU usage of the machine (0-100%).

___

###  cpuProcess

• **cpuProcess**: *number*

*Defined in [types.d.ts:604](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L604)*

**`description`** CPU usage of the rrServer app (0-100%).

___

###  framesPer90s

• **framesPer90s**: *number*

*Defined in [types.d.ts:584](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L584)*

**`description`** Number of frames rendered during this time segment (90seconds, 30 minutes or 6hours depending on the stats type).

___

###  frames_to_do

• **frames_to_do**: *number*

*Defined in [types.d.ts:674](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L674)*

**`description`** Summed frames to be rendered from all jobs.

___

###  jobBufferMemUsageJobs

• **jobBufferMemUsageJobs**: *number*

*Defined in [types.d.ts:659](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L659)*

**`description`** Memory usage for all job data.

___

###  jobs_rendering

• **jobs_rendering**: *number*

*Defined in [types.d.ts:629](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L629)*

**`description`** Number of jobs rendering.

___

###  jobs_total

• **jobs_total**: *number*

*Defined in [types.d.ts:634](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L634)*

**`description`** Total number of jobs.

___

###  jobs_unfinished

• **jobs_unfinished**: *number*

*Defined in [types.d.ts:624](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L624)*

**`description`** Number of unfinished jobs.

___

###  memUsageMachine

• **memUsageMachine**: *number*

*Defined in [types.d.ts:639](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L639)*

**`description`** Memory usage of the rrServer machine.

___

###  memUsageProcess

• **memUsageProcess**: *number*

*Defined in [types.d.ts:644](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L644)*

**`description`** Memory usage of the rrServer application.

___

###  serverTemperature

• **serverTemperature**: *number*

*Defined in [types.d.ts:614](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L614)*

**`description`** Temperature of the first HDD in the rrServer machine.

___

###  slot_used

• **slot_used**: *boolean*

*Defined in [types.d.ts:574](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L574)*

**`description`** Is this data valid? If not, then this data is crap or from any other day/time.

___

###  tCPMemUsageData

• **tCPMemUsageData**: *number*

*Defined in [types.d.ts:654](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L654)*

**`description`** Memory usage of the 2nd rrServers TCP socket buffer.

___

###  tCPMemUsageDataCompressed

• **tCPMemUsageDataCompressed**: *number*

*Defined in [types.d.ts:664](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L664)*

**`description`** Max memory for a TCP socket buffer after compression.

___

###  tCPMemUsageSocket

• **tCPMemUsageSocket**: *number*

*Defined in [types.d.ts:649](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L649)*

**`description`** Memory usage of the 1st rrServers TCP socket buffer.