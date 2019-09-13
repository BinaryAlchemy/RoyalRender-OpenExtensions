**[rrBindingsDocs](../README.md)**

[Globals](../README.md) › [Job](../modules/job.md) › [_RenderAppBasic](job._renderappbasic.md)

# Interface: _RenderAppBasic

## Hierarchy

* **_RenderAppBasic**

## Index

### Properties

* [executeType](job._renderappbasic.md#executetype)
* [name](job._renderappbasic.md#name)
* [rendererConfigListID](job._renderappbasic.md#rendererconfiglistid)
* [rendererName](job._renderappbasic.md#renderername)
* [rendererVersion](job._renderappbasic.md#rendererversion)
* [type](job._renderappbasic.md#type)
* [version](job._renderappbasic.md#version)

### Methods

* [clearBasic](job._renderappbasic.md#clearbasic)
* [setVersionBoth](job._renderappbasic.md#setversionboth)
* [setVersionMinor](job._renderappbasic.md#setversionminor)
* [versionMinorDisplay](job._renderappbasic.md#versionminordisplay)

## Properties

###  executeType

• **executeType**: *number*

*Defined in [types.d.ts:2190](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2190)*

**`description`** Sets if this is an execute job and if, which type of execute job

**`see`** {@link http://www.royalrender.de/help8/index.html?modulerrGlobal.html}

___

###  name

• **name**: *string*

*Defined in [types.d.ts:2159](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2159)*

**`description`** Name of the render application (Maya, Nuke)

___

###  rendererConfigListID

• **rendererConfigListID**: *number*

*Defined in [types.d.ts:2184](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2184)*

**`description`** ID of the render config file.

___

###  rendererName

• **rendererName**: *string*

*Defined in [types.d.ts:2164](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2164)*

**`description`** Name of the renderer (Vray, Arnold)

___

###  rendererVersion

• **rendererVersion**: *string*

*Defined in [types.d.ts:2174](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2174)*

**`description`** Version of the renderer

___

###  type

• **type**: *string*

*Defined in [types.d.ts:2169](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2169)*

**`description`** Comp, 3D, Archive or Execute

___

###  version

• **version**: *number*

*Defined in [types.d.ts:2179](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2179)*

**`description`** Version of the render application

## Methods

###  clearBasic

▸ **clearBasic**(): *void*

*Defined in [types.d.ts:2212](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2212)*

**`description`** Clears all settings

**Returns:** *void*

___

###  setVersionBoth

▸ **setVersionBoth**(`ver`: string): *void*

*Defined in [types.d.ts:2201](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2201)*

**`description`** Set the minor and major version via a string. E.g. "2016.51"

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`ver` | string | new Version  |

**Returns:** *void*

___

###  setVersionMinor

▸ **setVersionMinor**(`ver`: string): *void*

*Defined in [types.d.ts:2207](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2207)*

**`description`** Set the minor version via a string. E.g. "031"

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`ver` | string | new Version  |

**Returns:** *void*

___

###  versionMinorDisplay

▸ **versionMinorDisplay**(): *string*

*Defined in [types.d.ts:2195](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L2195)*

**Returns:** *string*

The minor version of the render app