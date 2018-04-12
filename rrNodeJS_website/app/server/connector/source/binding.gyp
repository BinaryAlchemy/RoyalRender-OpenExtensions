{
  "targets": [
    {
      "target_name": "jsRR",
      'cflags': ['-fPIC', "-std=c++0x", "-pipe", "-ffunction-sections", "-fdata-sections", "-Wno-invalid-offsetof" ],
      'defines': [ "QT_CORE_LIB", "QT_WEBKIT", "rrConsoleApp", "defrrTestJoblistConsole", "QT_NO_DEBUG", "QT_SHARED" ],
      "sources":
      [
      	"src/main.cc",
      	"src/tcp.cpp",
      	"src/commands.cpp",
      	"src/user.cpp",
      	"../../shared/RR_CRC.cpp",
		"../../shared/RR_DataTypes_Databuffer.cpp",
		"../../shared/RR_DataTypes_other.cpp",
		"../../shared_SDK/RR_DataTypes_other_SDK.cpp",
		"../../shared_SDK/RR_files_SDK.cpp",
		"../../shared/RR_TCP_Joblist.cpp",
		"../../shared/RR_network.cpp",
		"../../shared_SDK/RR_DataTypes_jobs_SDK.cpp",
		"../../shared/RR_DataTypes_tcpdata.cpp",
		"../../shared/RR_DataTypes_user.cpp",
		"../../shared/RR_DataTypes_client.cpp",
		"../../shared/RR_ExceptionHandler.cpp",
		"../../test/rrTestJoblistConsole-build-desktop-Qt_4_8_1_in_PATH__System__Release/GeneratedLx64/release/moc_RR_network.cpp"
	  ],
	  'include_dirs':
	  [
	  	"../../shared",
	  	"../../shared_SDK",
	  	"/usr/include/qt4",
	  	"/usr/include/qt4/QtCore"
	  ],
	  'libraries':
	  [
	  	"-lssl -lcrypto -lQtCore -lpthread"
	  ]
    }
  ]
}