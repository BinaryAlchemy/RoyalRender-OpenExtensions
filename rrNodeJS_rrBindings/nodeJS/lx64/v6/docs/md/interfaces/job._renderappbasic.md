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

*Defined in [types.d.ts:2189](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2189)*

**`description`** Sets if this is an execute job and if, which type of execute job

**`see`** {@link http://www.royalrender.de/help8/index.html?modulerrGlobal.html}

___

###  name

• **name**: *string*

*Defined in [types.d.ts:2158](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2158)*

**`description`** Name of the render application (Maya, Nuke)

___

###  rendererConfigListID

• **rendererConfigListID**: *number*

*Defined in [types.d.ts:2183](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2183)*

**`description`** ID of the render config file.

___

###  rendererName

• **rendererName**: *string*

*Defined in [types.d.ts:2163](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2163)*

**`description`** Name of the renderer (Vray, Arnold)

___

###  rendererVersion

• **rendererVersion**: *string*

*Defined in [types.d.ts:2173](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2173)*

**`description`** Version of the renderer

___

###  type

• **type**: *string*

*Defined in [types.d.ts:2168](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2168)*

**`description`** Comp, 3D, Archive or Execute

___

###  version

• **version**: *number*

*Defined in [types.d.ts:2178](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2178)*

**`description`** Version of the render application

## Methods

###  clearBasic

▸ **clearBasic**(): *void*

*Defined in [types.d.ts:2211](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2211)*

**`description`** Clears all settings

**Returns:** *void*

___

###  setVersionBoth

▸ **setVersionBoth**(`ver`: string): *void*

*Defined in [types.d.ts:2200](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2200)*

**`description`** Set the minor and major version via a string. E.g. "2016.51"

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`ver` | string | new Version  |

**Returns:** *void*

___

###  setVersionMinor

▸ **setVersionMinor**(`ver`: string): *void*

*Defined in [types.d.ts:2206](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2206)*

**`description`** Set the minor version via a string. E.g. "031"

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`ver` | string | new Version  |

**Returns:** *void*

___

###  versionMinorDisplay

▸ **versionMinorDisplay**(): *string*

*Defined in [types.d.ts:2194](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/5ba4523/rrNodeJS_rrBindings/nodeJS/lx64/v6/types.d.ts#L2194)*

**Returns:** *string*

The minor version of the render app