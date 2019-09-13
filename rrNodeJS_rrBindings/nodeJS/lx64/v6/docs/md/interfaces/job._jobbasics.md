**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [Job](../modules/job.md) › [_JobBasics](job._jobbasics.md)

# Interface: _JobBasics

## Hierarchy

* **_JobBasics**

  * [_JobSend](job._jobsend.md)

## Index

### Properties

* [ID](job._jobbasics.md#id)
* [additionalCommandlineParam](job._jobbasics.md#additionalcommandlineparam)
* [camera](job._jobbasics.md#camera)
* [channel](job._jobbasics.md#channel)
* [imageDir](job._jobbasics.md#imagedir)
* [imageExtension](job._jobbasics.md#imageextension)
* [imageFileName](job._jobbasics.md#imagefilename)
* [imageFileNameVariables](job._jobbasics.md#imagefilenamevariables)
* [imageFormatOverride](job._jobbasics.md#imageformatoverride)
* [imageFramePadding](job._jobbasics.md#imageframepadding)
* [imageHeight](job._jobbasics.md#imageheight)
* [imageMulti](job._jobbasics.md#imagemulti)
* [imagePreNumberLetter](job._jobbasics.md#imageprenumberletter)
* [imageSingleOutputFile](job._jobbasics.md#imagesingleoutputfile)
* [imageStereoL](job._jobbasics.md#imagestereol)
* [imageStereoR](job._jobbasics.md#imagestereor)
* [imageWidth](job._jobbasics.md#imagewidth)
* [layer](job._jobbasics.md#layer)
* [localTexturesFile](job._jobbasics.md#localtexturesfile)
* [maxWaitForPreID](job._jobbasics.md#maxwaitforpreid)
* [preID](job._jobbasics.md#preid)
* [renderApp](job._jobbasics.md#renderapp)
* [requiredLicenses](job._jobbasics.md#requiredlicenses)
* [rrJobOS](job._jobbasics.md#rrjobos)
* [sceneDatabaseDir](job._jobbasics.md#scenedatabasedir)
* [sceneName](job._jobbasics.md#scenename)
* [sceneOS](job._jobbasics.md#sceneos)
* [seqEnd](job._jobbasics.md#seqend)
* [seqFileOffset](job._jobbasics.md#seqfileoffset)
* [seqFrameSet](job._jobbasics.md#seqframeset)
* [seqIsFloatFrames](job._jobbasics.md#seqisfloatframes)
* [seqStart](job._jobbasics.md#seqstart)
* [seqStep](job._jobbasics.md#seqstep)
* [shotgunID](job._jobbasics.md#shotgunid)
* [structureIDBasics](job._jobbasics.md#structureidbasics)
* [structureIDSend](job._jobbasics.md#structureidsend)
* [uiIsChecked](job._jobbasics.md#uiischecked)
* [variablesIDBasics](job._jobbasics.md#variablesidbasics)
* [variablesIDSend](job._jobbasics.md#variablesidsend)

### Methods

* [IDstr](job._jobbasics.md#idstr)
* [IDstrFull](job._jobbasics.md#idstrfull)
* [channelExtension](job._jobbasics.md#channelextension)
* [channelExtension_set](job._jobbasics.md#channelextension_set)
* [channelFileName](job._jobbasics.md#channelfilename)
* [channelFileName_set](job._jobbasics.md#channelfilename_set)
* [customGet_MaxIDs](job._jobbasics.md#customget_maxids)
* [customSet_Str](job._jobbasics.md#customset_str)
* [customSet_StrByID](job._jobbasics.md#customset_strbyid)
* [customSet_UserInfo](job._jobbasics.md#customset_userinfo)
* [custom_AllAsString](job._jobbasics.md#custom_allasstring)
* [custom_NameByID](job._jobbasics.md#custom_namebyid)
* [custom_Str](job._jobbasics.md#custom_str)
* [custom_StrByID](job._jobbasics.md#custom_strbyid)
* [custom_UserInfo](job._jobbasics.md#custom_userinfo)
* [custom_clearAll](job._jobbasics.md#custom_clearall)
* [sceneDisplayName](job._jobbasics.md#scenedisplayname)
* [splitImageFileInto_DirFileExt](job._jobbasics.md#splitimagefileinto_dirfileext)
* [waitForPreID](job._jobbasics.md#waitforpreid)
* [waitForPreID_set](job._jobbasics.md#waitforpreid_set)

## Properties

###  ID

• **ID**: *[rrUint64](utils.rruint64.md)*

*Defined in [types.d.ts:1489](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1489)*

**`description`** ID of the _JobBasics object.

___

###  additionalCommandlineParam

• **additionalCommandlineParam**: *string*

*Defined in [types.d.ts:1520](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1520)*

___

###  camera

• **camera**: *string*

*Defined in [types.d.ts:1443](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1443)*

___

###  channel

• **channel**: *string*

*Defined in [types.d.ts:1445](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1445)*

___

###  imageDir

• **imageDir**: *string*

*Defined in [types.d.ts:1455](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1455)*

**`description`** The Image Directory of the current Job.

___

###  imageExtension

• **imageExtension**: *string*

*Defined in [types.d.ts:1466](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1466)*

**`description`** The Output Render Extension Setting for the current Job (e.g.: .exr, ...).

___

###  imageFileName

• **imageFileName**: *string*

*Defined in [types.d.ts:1456](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1456)*

___

###  imageFileNameVariables

• **imageFileNameVariables**: *string*

*Defined in [types.d.ts:1461](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1461)*

**`description`** Some render jobs render multiple layers/passes at once. The render application requires these parts of the file name as variables. E.g. <layer>.

___

###  imageFormatOverride

• **imageFormatOverride**: *string*

*Defined in [types.d.ts:1481](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1481)*

**`description`** If used, then the image format is not the same as set in the scene. RR should override the image format at render time.

___

###  imageFramePadding

• **imageFramePadding**: *number*

*Defined in [types.d.ts:1468](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1468)*

___

###  imageHeight

• **imageHeight**: *number*

*Defined in [types.d.ts:1470](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1470)*

___

###  imageMulti

• **imageMulti**: *number*

*Defined in [types.d.ts:1476](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1476)*

**`description`** Number of tiles for a frame.

___

###  imagePreNumberLetter

• **imagePreNumberLetter**: *string*

*Defined in [types.d.ts:1467](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1467)*

___

###  imageSingleOutputFile

• **imageSingleOutputFile**: *boolean*

*Defined in [types.d.ts:1471](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1471)*

___

###  imageStereoL

• **imageStereoL**: *string*

*Defined in [types.d.ts:1482](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1482)*

___

###  imageStereoR

• **imageStereoR**: *string*

*Defined in [types.d.ts:1483](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1483)*

___

###  imageWidth

• **imageWidth**: *number*

*Defined in [types.d.ts:1469](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1469)*

___

###  layer

• **layer**: *string*

*Defined in [types.d.ts:1444](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1444)*

___

###  localTexturesFile

• **localTexturesFile**: *string*

*Defined in [types.d.ts:1484](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1484)*

___

###  maxWaitForPreID

• **maxWaitForPreID**: *number*

*Defined in [types.d.ts:1499](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1499)*

**`description`** maximum number of waitForPreIDs. See functions of _JobBasics.

___

###  preID

• **preID**: *number*

*Defined in [types.d.ts:1494](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1494)*

**`description`** This variable is used for jobs before submission only! Please see function IDpre() (NOT IMPLEMENTED IN NODE ADDON) if you want to get the variable once the job was send. A value between 0 and 255. Each job gets the Pre ID attached as small letter to the main ID. It is the the small letter at the end of the ID.

___

###  renderApp

• **renderApp**: *[_RenderAppBasic](job._renderappbasic.md)*

*Defined in [types.d.ts:1436](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1436)*

**`description`** Render application and Renderer information.

___

###  requiredLicenses

• **requiredLicenses**: *string*

*Defined in [types.d.ts:1450](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1450)*

**`description`** The requiredLicenses for the current Job (e.g.: ;/Arnold, ...).

___

###  rrJobOS

• **rrJobOS**: *number*

*Defined in [types.d.ts:1426](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1426)*

**`description`** OS of the texture paths inside this rrJob class. 1: Windows, 2: Linux, 3: OSX.

___

###  sceneDatabaseDir

• **sceneDatabaseDir**: *string*

*Defined in [types.d.ts:1442](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1442)*

**`description`** The Scene Database Directory of the current Job.

___

###  sceneName

• **sceneName**: *string*

*Defined in [types.d.ts:1437](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1437)*

___

###  sceneOS

• **sceneOS**: *number*

*Defined in [types.d.ts:1431](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1431)*

**`description`** OS the scene was created on (Texture paths inside the file). 1: Windows, 2: Linux, 3: OSX.

___

###  seqEnd

• **seqEnd**: *number*

*Defined in [types.d.ts:1507](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1507)*

___

###  seqFileOffset

• **seqFileOffset**: *number*

*Defined in [types.d.ts:1509](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1509)*

___

###  seqFrameSet

• **seqFrameSet**: *string*

*Defined in [types.d.ts:1514](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1514)*

**`description`** - not used -

___

###  seqIsFloatFrames

• **seqIsFloatFrames**: *boolean*

*Defined in [types.d.ts:1519](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1519)*

**`description`** - not used -

___

###  seqStart

• **seqStart**: *number*

*Defined in [types.d.ts:1506](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1506)*

___

###  seqStep

• **seqStep**: *number*

*Defined in [types.d.ts:1508](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1508)*

___

###  shotgunID

• **shotgunID**: *string*

*Defined in [types.d.ts:1505](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1505)*

**`description`** ShotgunID of the Scene/Sequence. Usually retrieved at submission by an onsubmission script.

___

###  structureIDBasics

• **structureIDBasics**: *number*

*Defined in [types.d.ts:1406](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1406)*

**`description`** MagicID/Version of the class.

___

###  structureIDSend

• **structureIDSend**: *number*

*Defined in [types.d.ts:1416](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1416)*

**`description`** MagicID/Version of the class.

___

###  uiIsChecked

• **uiIsChecked**: *boolean*

*Defined in [types.d.ts:1500](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1500)*

___

###  variablesIDBasics

• **variablesIDBasics**: *number*

*Defined in [types.d.ts:1411](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1411)*

**`description`** MagicID/Version of the class.

___

###  variablesIDSend

• **variablesIDSend**: *number*

*Defined in [types.d.ts:1421](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1421)*

**`description`** MagicID/Version of the class.

## Methods

###  IDstr

▸ **IDstr**(): *string*

*Defined in [types.d.ts:1566](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1566)*

**Returns:** *string*

Short ID of the job as human readable/rememberable string E.g. {D5Ca}. The ID string is a short version of the job ID. It could happen that two jobs have the same short ID. IDstrFull() does not have this issue.

___

###  IDstrFull

▸ **IDstrFull**(): *string*

*Defined in [types.d.ts:1572](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1572)*

**`description`** IDstr() only delivers a short version of the jobID. This can lead to repeating IDs. IDstrFull() delivers the full version of this ID, which will not lead to ID repetition.

**Returns:** *string*

the full short ID.

___

###  channelExtension

▸ **channelExtension**(`index`: number): *string*

*Defined in [types.d.ts:1547](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1547)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`index` | number | The index of the render channel you want to retrieve. Ranges from 0-100. |

**Returns:** *string*

The extension of the render channel.

___

###  channelExtension_set

▸ **channelExtension_set**(`index`: number, `value`: string): *void*

*Defined in [types.d.ts:1561](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1561)*

**`description`** Set the extension of the render channel.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`index` | number | The index of the render channel of which you want to change the extension. Ranges from 0-100. |
`value` | string | The new render channel Extension.  |

**Returns:** *void*

___

###  channelFileName

▸ **channelFileName**(`index`: number): *string*

*Defined in [types.d.ts:1541](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1541)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`index` | number | The index of the channel which should be fetched. Ranges from 0-100. |

**Returns:** *string*

The filename of the render Channel.

___

###  channelFileName_set

▸ **channelFileName_set**(`index`: number, `value`: string): *void*

*Defined in [types.d.ts:1554](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1554)*

**`description`** Set the filename of the render channel.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`index` | number | The index of the render channel of which you want to change the filename. Ranges from 0-100. |
`value` | string | The new filename of the render channel.  |

**Returns:** *void*

___

###  customGet_MaxIDs

▸ **customGet_MaxIDs**(): *number*

*Defined in [types.d.ts:1607](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1607)*

**Returns:** *number*

The number of custom data items.

___

###  customSet_Str

▸ **customSet_Str**(`name`: string, `value`: string): *void*

*Defined in [types.d.ts:1591](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1591)*

**`description`** Set custom data item. An empty value is not saved.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`name` | string | Name of the data item you want to save. If this name already exists, the item in the server will be overwritten or deleted (if value is empty). |
`value` | string | Value of the data item you want to save.  |

**Returns:** *void*

___

###  customSet_StrByID

▸ **customSet_StrByID**(`id`: number, `value`: string): *void*

*Defined in [types.d.ts:1620](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1620)*

**`description`** Set custom data item via its id.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`id` | number | The data item id. |
`value` | string | The new value for the respective data item.  |

**Returns:** *void*

___

###  customSet_UserInfo

▸ **customSet_UserInfo**(`info`: string): *void*

*Defined in [types.d.ts:1602](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1602)*

**`description`** Same as customSet_Str("UserInfo"). UserInfo is displayed in rrControl.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`info` | string | The new UserInfo.  |

**Returns:** *void*

___

###  custom_AllAsString

▸ **custom_AllAsString**(): *string*

*Defined in [types.d.ts:1631](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1631)*

**Returns:** *string*

A string with all custom data items set.

___

###  custom_NameByID

▸ **custom_NameByID**(`id`: number): *string*

*Defined in [types.d.ts:1626](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1626)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`id` | number | The data item id. |

**Returns:** *string*

Name of the data item via id.

___

###  custom_Str

▸ **custom_Str**(`name`: string): *string*

*Defined in [types.d.ts:1584](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1584)*

**`description`** You can save up to 5000 letters. If unicode letters are found in value, then the string takes twice its length in bytes. Reserved names are "UserInfo" and "EnvFile".

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`name` | string | Name of the data item of the job you want to retrieve. |

**Returns:** *string*

A custom data item of the job.

___

###  custom_StrByID

▸ **custom_StrByID**(`id`: number): *string*

*Defined in [types.d.ts:1613](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1613)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`id` | number | The data item id. |

**Returns:** *string*

Custom data item via its id.

___

###  custom_UserInfo

▸ **custom_UserInfo**(): *string*

*Defined in [types.d.ts:1596](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1596)*

**`description`** Same as custom_Str("UserInfo"). UserInfo is displayed in rrControl.

**Returns:** *string*

___

###  custom_clearAll

▸ **custom_clearAll**(): *void*

*Defined in [types.d.ts:1636](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1636)*

**`description`** Deletes all custom data items.

**Returns:** *void*

___

###  sceneDisplayName

▸ **sceneDisplayName**(): *string*

*Defined in [types.d.ts:1577](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1577)*

**`description`** Removes all extensions and variables from the scene file name and keeps only a few folders in front of the file name.

**Returns:** *string*

___

###  splitImageFileInto_DirFileExt

▸ **splitImageFileInto_DirFileExt**(`percentPadding`: boolean): *void*

*Defined in [types.d.ts:1641](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1641)*

**`description`** Splits the imageFileName into imageDir and imageExtension if those two are empty. If ImageDir or imageExtension have a value, then this variable is not changed. The same applies for splitting channelFileNames  into file and extension. If imageSingleOutputFile is set, then no imageExtension will be set as there is no frame number in between. If an image padding is recognized, then imageFramePadding is set as well. Supported frame number formats are: %04d (only if percentPadding is set) #### [####] .125. If the file extension indicates a video or audio file, then imageSingleOutputFile is set to True. Note: This function is always executed in rrSubmitter. But you can call it yourself to check the values afterwards.

**Parameters:**

Name | Type |
------ | ------ |
`percentPadding` | boolean |

**Returns:** *void*

___

###  waitForPreID

▸ **waitForPreID**(`index`: number): *number*

*Defined in [types.d.ts:1528](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1528)*

**`description`** This is only used for jobs at submission. Get the waitForPreID of this job. A job has up to 20 waitforIDs. When the job is received by the server, the server checks for other jobs send from the machine in the last 15 minutes. The server then gets the latest job with the same PreID as a WaitForPreID of this job, then this jobs waits for the other job. Index ranges from 0 to maxWaitForPreID. Maximum is 20.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`index` | number | ranges from 0 to maxWaitForPreID. Maximum is 20.  |

**Returns:** *number*

___

###  waitForPreID_set

▸ **waitForPreID_set**(`index`: number, `value`: number): *string*

*Defined in [types.d.ts:1535](https://github.com/Novalis15/rrBindings/blob/33d8d78/nodeJS/lx64/v6/types.d.ts#L1535)*

**`description`** Set the waitForPreID of this job. A job has up to 20 waitforIDs. You have to update maxWaitForPreID as well.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`index` | number | The index of the waitforID. ranges from 0 to maxWaitForPreID. Maximum is 20. |
`value` | number | The value for the waitforID respectively.  |

**Returns:** *string*