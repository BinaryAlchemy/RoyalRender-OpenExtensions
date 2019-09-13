**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [rrGlobal](../modules/rrglobal.md) › [_EPluginReturn](rrglobal._epluginreturn.md)

# Interface: _EPluginReturn

## Hierarchy

* **_EPluginReturn**

## Index

### Properties

* [rAbsolutePathsRequired](rrglobal._epluginreturn.md#rabsolutepathsrequired)
* [rCError](rrglobal._epluginreturn.md#rcerror)
* [rDataError](rrglobal._epluginreturn.md#rdataerror)
* [rDebugCompile](rrglobal._epluginreturn.md#rdebugcompile)
* [rFileBuffertoSmall](rrglobal._epluginreturn.md#rfilebuffertosmall)
* [rFileFailedToOpen](rrglobal._epluginreturn.md#rfilefailedtoopen)
* [rFileFailedToSave](rrglobal._epluginreturn.md#rfilefailedtosave)
* [rFileNotFound](rrglobal._epluginreturn.md#rfilenotfound)
* [rFileSizeToSmall](rrglobal._epluginreturn.md#rfilesizetosmall)
* [rImageDimensionsToLarge](rrglobal._epluginreturn.md#rimagedimensionstolarge)
* [rIsPlaceHolderFile](rrglobal._epluginreturn.md#risplaceholderfile)
* [rLoadEndOfFileOnly](rrglobal._epluginreturn.md#rloadendoffileonly)
* [rMemError](rrglobal._epluginreturn.md#rmemerror)
* [rNoImageDimensions](rrglobal._epluginreturn.md#rnoimagedimensions)
* [rNoImageOutput](rrglobal._epluginreturn.md#rnoimageoutput)
* [rNoPluginforFileType](rrglobal._epluginreturn.md#rnopluginforfiletype)
* [rOtherError](rrglobal._epluginreturn.md#rothererror)
* [rPluginFileMissing](rrglobal._epluginreturn.md#rpluginfilemissing)
* [rPluginLoadError](rrglobal._epluginreturn.md#rpluginloaderror)
* [rPythonError](rrglobal._epluginreturn.md#rpythonerror)
* [rRRDataVersionConflict](rrglobal._epluginreturn.md#rrrdataversionconflict)
* [rRequireFullLoad](rrglobal._epluginreturn.md#rrequirefullload)
* [rSuccessful](rrglobal._epluginreturn.md#rsuccessful)
* [rSuccessfulIgnoreNoJobs](rrglobal._epluginreturn.md#rsuccessfulignorenojobs)
* [rSuccessfulRetryLoad](rrglobal._epluginreturn.md#rsuccessfulretryload)
* [rUnknownError](rrglobal._epluginreturn.md#runknownerror)
* [rUnsupportedFormat](rrglobal._epluginreturn.md#runsupportedformat)
* [rWrongFileSize](rrglobal._epluginreturn.md#rwrongfilesize)

## Properties

###  rAbsolutePathsRequired

• **rAbsolutePathsRequired**: *number*

*Defined in [types.d.ts:1320](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1320)*

**`description`** The scene parser was not able to create a job as some scene settings do not use an absolute path. And this plugin was not able to resolve the relative path OR it will not be possible to render the scene with relative paths.

___

###  rCError

• **rCError**: *number*

*Defined in [types.d.ts:1272](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1272)*

___

###  rDataError

• **rDataError**: *number*

*Defined in [types.d.ts:1292](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1292)*

**`description`** The data of the file seems to be broken.

___

###  rDebugCompile

• **rDebugCompile**: *number*

*Defined in [types.d.ts:1302](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1302)*

___

###  rFileBuffertoSmall

• **rFileBuffertoSmall**: *number*

*Defined in [types.d.ts:1310](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1310)*

___

###  rFileFailedToOpen

• **rFileFailedToOpen**: *number*

*Defined in [types.d.ts:1265](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1265)*

**`description`** Failed to open the file.

___

###  rFileFailedToSave

• **rFileFailedToSave**: *number*

*Defined in [types.d.ts:1304](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1304)*

___

###  rFileNotFound

• **rFileNotFound**: *number*

*Defined in [types.d.ts:1260](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1260)*

**`description`** File to read was not found.

___

###  rFileSizeToSmall

• **rFileSizeToSmall**: *number*

*Defined in [types.d.ts:1301](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1301)*

**`description`** The file size is smaller than it should be. Indicates that the file was not completely written.

___

###  rImageDimensionsToLarge

• **rImageDimensionsToLarge**: *number*

*Defined in [types.d.ts:1293](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1293)*

___

###  rIsPlaceHolderFile

• **rIsPlaceHolderFile**: *number*

*Defined in [types.d.ts:1303](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1303)*

___

###  rLoadEndOfFileOnly

• **rLoadEndOfFileOnly**: *number*

*Defined in [types.d.ts:1321](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1321)*

___

###  rMemError

• **rMemError**: *number*

*Defined in [types.d.ts:1273](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1273)*

___

###  rNoImageDimensions

• **rNoImageDimensions**: *number*

*Defined in [types.d.ts:1287](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1287)*

___

###  rNoImageOutput

• **rNoImageOutput**: *number*

*Defined in [types.d.ts:1315](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1315)*

**`description`** No image output set in scene file.

___

###  rNoPluginforFileType

• **rNoPluginforFileType**: *number*

*Defined in [types.d.ts:1295](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1295)*

___

###  rOtherError

• **rOtherError**: *number*

*Defined in [types.d.ts:1285](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1285)*

**`description`** Any other error.

___

###  rPluginFileMissing

• **rPluginFileMissing**: *number*

*Defined in [types.d.ts:1274](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1274)*

___

###  rPluginLoadError

• **rPluginLoadError**: *number*

*Defined in [types.d.ts:1275](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1275)*

___

###  rPythonError

• **rPythonError**: *number*

*Defined in [types.d.ts:1296](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1296)*

___

###  rRRDataVersionConflict

• **rRRDataVersionConflict**: *number*

*Defined in [types.d.ts:1271](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1271)*

___

###  rRequireFullLoad

• **rRequireFullLoad**: *number*

*Defined in [types.d.ts:1294](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1294)*

___

###  rSuccessful

• **rSuccessful**: *number*

*Defined in [types.d.ts:1255](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1255)*

**`description`** Successful execution.

___

###  rSuccessfulIgnoreNoJobs

• **rSuccessfulIgnoreNoJobs**: *number*

*Defined in [types.d.ts:1280](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1280)*

**`description`** The execution was successful, but the plugin has not created a job. And this should not be seen as an error.

___

###  rSuccessfulRetryLoad

• **rSuccessfulRetryLoad**: *number*

*Defined in [types.d.ts:1309](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1309)*

**`description`** The execution was not an error. But the main app should execute this plugin again.

___

###  rUnknownError

• **rUnknownError**: *number*

*Defined in [types.d.ts:1250](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1250)*

**`description`** The default value if nothing was set.

___

###  rUnsupportedFormat

• **rUnsupportedFormat**: *number*

*Defined in [types.d.ts:1270](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1270)*

**`description`** This plugin does not support this file format. In such a case the next plugin that can open this file extension is executed.

___

###  rWrongFileSize

• **rWrongFileSize**: *number*

*Defined in [types.d.ts:1286](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/win64/v6/types.d.ts#L1286)*