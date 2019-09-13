**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_rrClientStats_day](libnoderr2_datafiles._rrclientstats_day.md)

# Interface: _rrClientStats_day

## Hierarchy

* **_rrClientStats_day**

## Index

### Properties

* [day](libnoderr2_datafiles._rrclientstats_day.md#day)
* [daySet](libnoderr2_datafiles._rrclientstats_day.md#dayset)

### Methods

* [data](libnoderr2_datafiles._rrclientstats_day.md#data)
* [dataHourly](libnoderr2_datafiles._rrclientstats_day.md#datahourly)
* [dataHourlyMax](libnoderr2_datafiles._rrclientstats_day.md#datahourlymax)
* [dataMax](libnoderr2_datafiles._rrclientstats_day.md#datamax)

## Properties

###  day

• **day**: *number*

*Defined in [types.d.ts:706](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L706)*

**`description`** The current day in the default unix timestamp (days since Jan 1, 1970). Note: Most time functions return the time in seconds since 1970, so divide that value with /60/60/24.

___

###  daySet

• **daySet**: *boolean*

*Defined in [types.d.ts:701](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L701)*

**`description`** Contains this day any useful data? (e.g. if the client was not online that day, daySet is false).

## Methods

###  data

▸ **data**(`idx`: number): *[_rrClientStats_day_data](libnoderr2_datafiles._rrclientstats_day_data.md)*

*Defined in [types.d.ts:711](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L711)*

**`description`** This data is collected every 20 seconds. Index 0 are the first 20 seconds of the day, Index 1 the 20-40 seconds of the day, ...

**Parameters:**

Name | Type |
------ | ------ |
`idx` | number |

**Returns:** *[_rrClientStats_day_data](libnoderr2_datafiles._rrclientstats_day_data.md)*

___

###  dataHourly

▸ **dataHourly**(`idx`: number): *[_rrClientStats_day_data_hourly](libnoderr2_datafiles._rrclientstats_day_data_hourly.md)*

*Defined in [types.d.ts:721](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L721)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`idx` | number | 0 is the first hour of the day ( 00:00  - 01:00 ).  |

**Returns:** *[_rrClientStats_day_data_hourly](libnoderr2_datafiles._rrclientstats_day_data_hourly.md)*

___

###  dataHourlyMax

▸ **dataHourlyMax**(): *number*

*Defined in [types.d.ts:726](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L726)*

**`description`** The maximum number of values in the hourly array (24).

**Returns:** *number*

___

###  dataMax

▸ **dataMax**(): *number*

*Defined in [types.d.ts:716](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L716)*

**Returns:** *number*

The maximum number of values in the data array. (4320 for the current version, one data item every 20 seconds).