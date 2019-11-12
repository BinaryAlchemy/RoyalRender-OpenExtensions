[rrBindingsDocs](../README.md) › [rrGlobal](../modules/rrglobal.md) › [_EClientCommand](rrglobal._eclientcommand.md)

# Interface: _EClientCommand

## Hierarchy

* **_EClientCommand**

## Index

### Properties

* [cAbortAfterFrame](rrglobal._eclientcommand.md#cabortafterframe)
* [cAbortAfterFrameDisable](rrglobal._eclientcommand.md#cabortafterframedisable)
* [cAbortDisable](rrglobal._eclientcommand.md#cabortdisable)
* [cAbortUNKNOWN](rrglobal._eclientcommand.md#cabortunknown)
* [cAllowLittle](rrglobal._eclientcommand.md#callowlittle)
* [cCommandLine](rrglobal._eclientcommand.md#ccommandline)
* [cConfigSearchForApplications](rrglobal._eclientcommand.md#cconfigsearchforapplications)
* [cConfigSearchForApplicationsDeleteOld](rrglobal._eclientcommand.md#cconfigsearchforapplicationsdeleteold)
* [cDevDebug](rrglobal._eclientcommand.md#cdevdebug)
* [cDisable](rrglobal._eclientcommand.md#cdisable)
* [cDoSpeedTest](rrglobal._eclientcommand.md#cdospeedtest)
* [cEnable](rrglobal._eclientcommand.md#cenable)
* [cForbitLittle](rrglobal._eclientcommand.md#cforbitlittle)
* [cIgnoreCPU](rrglobal._eclientcommand.md#cignorecpu)
* [cIgnoreWorking](rrglobal._eclientcommand.md#cignoreworking)
* [cReloadAllConfig](rrglobal._eclientcommand.md#creloadallconfig)
* [cReloadClientConfig](rrglobal._eclientcommand.md#creloadclientconfig)
* [cReloadGlobalConfig](rrglobal._eclientcommand.md#creloadglobalconfig)
* [cReloadUserConfig](rrglobal._eclientcommand.md#creloaduserconfig)
* [cReserveCPUInteractive](rrglobal._eclientcommand.md#creservecpuinteractive)
* [cResetIdleTime](rrglobal._eclientcommand.md#cresetidletime)
* [cRestartClientExe](rrglobal._eclientcommand.md#crestartclientexe)
* [cRestartMachine](rrglobal._eclientcommand.md#crestartmachine)
* [cRestartMachineForce](rrglobal._eclientcommand.md#crestartmachineforce)
* [cShowProcessTree](rrglobal._eclientcommand.md#cshowprocesstree)
* [cShutdownClient](rrglobal._eclientcommand.md#cshutdownclient)
* [cShutdownClientAndService](rrglobal._eclientcommand.md#cshutdownclientandservice)
* [cShutdownMachine](rrglobal._eclientcommand.md#cshutdownmachine)
* [cShutdownMachineForce](rrglobal._eclientcommand.md#cshutdownmachineforce)
* [cTimeSync](rrglobal._eclientcommand.md#ctimesync)
* [cUpdateServiceCfg](rrglobal._eclientcommand.md#cupdateservicecfg)
* [cUseCPUInteractive](rrglobal._eclientcommand.md#cusecpuinteractive)
* [cUseWorking](rrglobal._eclientcommand.md#cuseworking)
* [cWOL](rrglobal._eclientcommand.md#cwol)

## Properties

###  cAbortAfterFrame

• **cAbortAfterFrame**: *number*

*Defined in [types.d.ts:1122](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1122)*

___

###  cAbortAfterFrameDisable

• **cAbortAfterFrameDisable**: *number*

*Defined in [types.d.ts:1123](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1123)*

___

###  cAbortDisable

• **cAbortDisable**: *number*

*Defined in [types.d.ts:1107](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1107)*

___

###  cAbortUNKNOWN

• **cAbortUNKNOWN**: *number*

*Defined in [types.d.ts:1094](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1094)*

___

###  cAllowLittle

• **cAllowLittle**: *number*

*Defined in [types.d.ts:1097](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1097)*

___

###  cCommandLine

• **cCommandLine**: *number*

*Defined in [types.d.ts:1128](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1128)*

**`description`** Requires to set the param string of the clientSendCommand function. The client will create a batch file RR_LocalData/_command.bat. It executes the command and writes the output into RR_LocalData/_command.txt. If you want to keep your log output, you should redirect it into a file via your commandline. For example: myCommand 1>/fileserver/share/MyCommand_<LocalHost>.txt   2>/fileserver/share/MyCommand_<LocalHost>_error.txt myCommand 1>/fileserver/share/MyCommand_<LocalHost>.txt   2>&1 You can use all variables (like <LocalHost>) from  render configs, as long as they are not job specific. The command buffer can only take up to 500 letters.

___

###  cConfigSearchForApplications

• **cConfigSearchForApplications**: *number*

*Defined in [types.d.ts:1117](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1117)*

___

###  cConfigSearchForApplicationsDeleteOld

• **cConfigSearchForApplicationsDeleteOld**: *number*

*Defined in [types.d.ts:1118](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1118)*

___

###  cDevDebug

• **cDevDebug**: *number*

*Defined in [types.d.ts:1130](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1130)*

___

###  cDisable

• **cDisable**: *number*

*Defined in [types.d.ts:1096](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1096)*

___

###  cDoSpeedTest

• **cDoSpeedTest**: *number*

*Defined in [types.d.ts:1124](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1124)*

___

###  cEnable

• **cEnable**: *number*

*Defined in [types.d.ts:1095](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1095)*

___

###  cForbitLittle

• **cForbitLittle**: *number*

*Defined in [types.d.ts:1098](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1098)*

___

###  cIgnoreCPU

• **cIgnoreCPU**: *number*

*Defined in [types.d.ts:1108](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1108)*

___

###  cIgnoreWorking

• **cIgnoreWorking**: *number*

*Defined in [types.d.ts:1100](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1100)*

___

###  cReloadAllConfig

• **cReloadAllConfig**: *number*

*Defined in [types.d.ts:1115](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1115)*

___

###  cReloadClientConfig

• **cReloadClientConfig**: *number*

*Defined in [types.d.ts:1112](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1112)*

___

###  cReloadGlobalConfig

• **cReloadGlobalConfig**: *number*

*Defined in [types.d.ts:1114](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1114)*

___

###  cReloadUserConfig

• **cReloadUserConfig**: *number*

*Defined in [types.d.ts:1113](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1113)*

___

###  cReserveCPUInteractive

• **cReserveCPUInteractive**: *number*

*Defined in [types.d.ts:1109](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1109)*

___

###  cResetIdleTime

• **cResetIdleTime**: *number*

*Defined in [types.d.ts:1129](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1129)*

___

###  cRestartClientExe

• **cRestartClientExe**: *number*

*Defined in [types.d.ts:1101](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1101)*

___

###  cRestartMachine

• **cRestartMachine**: *number*

*Defined in [types.d.ts:1103](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1103)*

___

###  cRestartMachineForce

• **cRestartMachineForce**: *number*

*Defined in [types.d.ts:1104](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1104)*

___

###  cShowProcessTree

• **cShowProcessTree**: *number*

*Defined in [types.d.ts:1121](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1121)*

___

###  cShutdownClient

• **cShutdownClient**: *number*

*Defined in [types.d.ts:1119](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1119)*

___

###  cShutdownClientAndService

• **cShutdownClientAndService**: *number*

*Defined in [types.d.ts:1111](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1111)*

___

###  cShutdownMachine

• **cShutdownMachine**: *number*

*Defined in [types.d.ts:1105](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1105)*

___

###  cShutdownMachineForce

• **cShutdownMachineForce**: *number*

*Defined in [types.d.ts:1106](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1106)*

___

###  cTimeSync

• **cTimeSync**: *number*

*Defined in [types.d.ts:1120](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1120)*

___

###  cUpdateServiceCfg

• **cUpdateServiceCfg**: *number*

*Defined in [types.d.ts:1116](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1116)*

___

###  cUseCPUInteractive

• **cUseCPUInteractive**: *number*

*Defined in [types.d.ts:1110](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1110)*

___

###  cUseWorking

• **cUseWorking**: *number*

*Defined in [types.d.ts:1099](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1099)*

___

###  cWOL

• **cWOL**: *number*

*Defined in [types.d.ts:1102](https://github.com/Novalis15/RoyalRender-OpenExtensions/blob/f77b7d8/rrNodeJS_rrBindings/nodeJS/win64/v6/types.d.ts#L1102)*
