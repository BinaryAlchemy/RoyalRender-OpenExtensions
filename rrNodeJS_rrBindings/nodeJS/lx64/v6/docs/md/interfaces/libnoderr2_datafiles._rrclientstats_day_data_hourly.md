**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [libNodeRR2_datafiles](../modules/libnoderr2_datafiles.md) › [_rrClientStats_day_data_hourly](libnoderr2_datafiles._rrclientstats_day_data_hourly.md)

# Interface: _rrClientStats_day_data_hourly

## Hierarchy

* **_rrClientStats_day_data_hourly**

## Index

### Methods

* [jobThread](libnoderr2_datafiles._rrclientstats_day_data_hourly.md#jobthread)
* [jobThreadMax](libnoderr2_datafiles._rrclientstats_day_data_hourly.md#jobthreadmax)

## Methods

###  jobThread

▸ **jobThread**(`idx`: number): *[_rrClientStats_day_data_hourly_jobthread](libnoderr2_datafiles._rrclientstats_day_data_hourly_jobthread.md)*

*Defined in [types.d.ts:791](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L791)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`idx` | number | Index of the job thread you want to fetch. |

**Returns:** *[_rrClientStats_day_data_hourly_jobthread](libnoderr2_datafiles._rrclientstats_day_data_hourly_jobthread.md)*

The data for each job thread.

___

###  jobThreadMax

▸ **jobThreadMax**(): *number*

*Defined in [types.d.ts:796](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L796)*

**Returns:** *number*

The number of job threads the client was running in this hour.