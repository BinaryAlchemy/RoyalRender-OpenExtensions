[rrBindingsDocs](../README.md) › [rrGlobal](../modules/rrglobal.md) › [_ELogLvL](rrglobal._eloglvl.md)

# Interface: _ELogLvL

## Hierarchy

* **_ELogLvL**

## Index

### Properties

* [critical](rrglobal._eloglvl.md#critical)
* [debug](rrglobal._eloglvl.md#debug)
* [error](rrglobal._eloglvl.md#error)
* [info](rrglobal._eloglvl.md#info)
* [progress](rrglobal._eloglvl.md#progress)
* [warning](rrglobal._eloglvl.md#warning)

## Properties

###  critical

• **critical**: *number*

*Defined in [types.d.ts:1161](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1161)*

**`description`** Critical messages will force the RR application to restart or terminate themselves.

___

###  debug

• **debug**: *number*

*Defined in [types.d.ts:1186](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1186)*

**`description`** Debug messages are ignored by default. They are shown if you have called debugEnable() or the RR application is not running in debug mode.

___

###  error

• **error**: *number*

*Defined in [types.d.ts:1166](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1166)*

**`description`** Error messages are important for the execution of RR and should never fail. All RR error messages are collected in a seperate error log RR/sub/log/_ERROR.txt for the rrAdmin and/or rrSupport to fix issues.

___

###  info

• **info**: *number*

*Defined in [types.d.ts:1176](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1176)*

**`description`** default messages (At the moment there is no difference to "progress" besides for the message box).

___

###  progress

• **progress**: *number*

*Defined in [types.d.ts:1181](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1181)*

**`description`** default messages (At the moment there is no difference to "info" besides for the message box).

___

###  warning

• **warning**: *number*

*Defined in [types.d.ts:1171](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1171)*

**`description`** Warning messages will have a "WRN - " in front to identify them faster in logfiles.
