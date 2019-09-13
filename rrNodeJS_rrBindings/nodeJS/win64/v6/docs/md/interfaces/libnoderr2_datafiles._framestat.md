**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_frameStat](libnoderr2_datafiles._framestat.md)

# Interface: _frameStat

## Hierarchy

* **_frameStat**

## Index

### Properties

* [averageValue](libnoderr2_datafiles._framestat.md#averagevalue)
* [client](libnoderr2_datafiles._framestat.md#client)
* [frameNrJob](libnoderr2_datafiles._framestat.md#framenrjob)
* [logFileStart](libnoderr2_datafiles._framestat.md#logfilestart)
* [logFileStartFrame](libnoderr2_datafiles._framestat.md#logfilestartframe)
* [renderTime5Sec](libnoderr2_datafiles._framestat.md#rendertime5sec)

### Methods

* [part](libnoderr2_datafiles._framestat.md#part)
* [partMax](libnoderr2_datafiles._framestat.md#partmax)

## Properties

###  averageValue

• **averageValue**: *number*

*Defined in [types.d.ts:867](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L867)*

**`description`** Sometimes the client is not able to get exact values per frames. In this case it collects the data of the whole frame segment and averages the values.

**`returns`** The frame segment contains of averageValue frames.

___

###  client

• **client**: *string*

*Defined in [types.d.ts:861](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L861)*

**`returns`** Name of the client.

___

###  frameNrJob

• **frameNrJob**: *number*

*Defined in [types.d.ts:856](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L856)*

**`returns`** The frame number of the job.

___

###  logFileStart

• **logFileStart**: *Date*

*Defined in [types.d.ts:841](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L841)*

**`returns`** The time when the render logfile was started. It is the same time as in the filename.

___

###  logFileStartFrame

• **logFileStartFrame**: *number*

*Defined in [types.d.ts:846](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L846)*

**`returns`** The first frame of the render log. It is the same frame number as in the filename.

___

###  renderTime5Sec

• **renderTime5Sec**: *number*

*Defined in [types.d.ts:851](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L851)*

**`returns`** The render time of the frame in seconds, divided by 5.

## Methods

###  part

▸ **part**(): *[_frameStat_part](libnoderr2_datafiles._framestat_part.md)*

*Defined in [types.d.ts:873](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L873)*

**`description`** Stats are collected multiple times while a frame is rendered. If a frame takes for example 10 minutes to render, then each of the 5 part represents 2 minute of the render.

**Returns:** *[_frameStat_part](libnoderr2_datafiles._framestat_part.md)*

___

###  partMax

▸ **partMax**(): *number*

*Defined in [types.d.ts:878](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L878)*

**Returns:** *number*

Max number of parts for each frame (5).