# Microsoft Developer Studio Project File - Name="ScOpcClient" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ScOpcClient - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ScOpcClient.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ScOpcClient.mak" CFG="ScOpcClient - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ScOpcClient - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ScOpcClient - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ScOpcClient - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "..\..\~Release\ScOpcClient"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /ZI /Od /I "interface" /I "WithOpcSvr" /I "../include" /I "C:\Program Files\Microsoft SDK\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /incremental:yes /pdb:"../../../pdb/ScOpcClient.pdb" /debug /machine:I386 /out:"../../../out/ScOpcClient.exe" /libpath:"C:\Program Files\Microsoft SDK\lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ScOpcClient - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "..\..\~Debug\ScOpcClient"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "interface" /I "WithOpcSvr" /I "../include" /I "C:\Program Files\Microsoft SDK\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /pdb:"../../../pdb/ScOpcClient.pdb" /debug /machine:I386 /out:"../../../out/ScOpcClient.exe" /libpath:"C:\Program Files\Microsoft SDK\lib"
# SUBTRACT LINK32 /pdbtype:<none>

!ENDIF 

# Begin Target

# Name "ScOpcClient - Win32 Release"
# Name "ScOpcClient - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "OpcTask"

# PROP Default_Filter ""
# Begin Group "OPCSyncIO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OpcTask\OTIOPCSyncIORead.cpp
# End Source File
# Begin Source File

SOURCE=.\OpcTask\OTIOPCSyncIOWrite.cpp
# End Source File
# End Group
# Begin Group "OPCServer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OpcTask\OTAddGroup.cpp
# End Source File
# End Group
# Begin Group "OPCAsyncIO2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OpcTask\OTAsyncIo2Read.cpp
# End Source File
# Begin Source File

SOURCE=.\OpcTask\OTAsyncIO2Write.cpp
# End Source File
# End Group
# Begin Group "OPCItemMgt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OpcTask\OTIOPCItemMgtAddItems.cpp
# End Source File
# Begin Source File

SOURCE=.\OpcTask\OTIOPCItemMgtRemoveItems.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\OpcTask\Context.cpp
# End Source File
# Begin Source File

SOURCE=.\OpcTask\OpcTask.cpp
# End Source File
# Begin Source File

SOURCE=.\OpcTask\OTConnect.cpp
# End Source File
# Begin Source File

SOURCE=.\OpcTask\OTDisconnect.cpp
# End Source File
# Begin Source File

SOURCE=.\OpcTask\TaskFileReader.cpp
# End Source File
# End Group
# Begin Group "WithOpcSvr"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WithOpcSvr\ConnectionPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\WithOpcSvr\OpcGroupProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\WithOpcSvr\OpcItem.cpp
# End Source File
# Begin Source File

SOURCE=.\WithOpcSvr\OpcServerProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\WithOpcSvr\OPCSvrHelper.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemAttrDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemPropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ScOpcClient.cpp
# End Source File
# Begin Source File

SOURCE=.\ScOpcClient.rc
# End Source File
# Begin Source File

SOURCE=.\ScOpcClientDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ScOpcClientView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TaskLogFile.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\WithOpcSvr\ConnectionPoint.h
# End Source File
# Begin Source File

SOURCE=.\OpcTask\Context.h
# End Source File
# Begin Source File

SOURCE=.\ErrorDefine.h
# End Source File
# Begin Source File

SOURCE=.\ErrorHelper.h
# End Source File
# Begin Source File

SOURCE=.\IdGenerator.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OpcItem.h
# End Source File
# Begin Source File

SOURCE=.\WithOpcSvr\OpcServerProxy.h
# End Source File
# Begin Source File

SOURCE=.\OpcTask\OpcTask.h
# End Source File
# Begin Source File

SOURCE=.\OpcTask\OTAsyncIo2Read.h
# End Source File
# Begin Source File

SOURCE=.\OpcTask\OTAsyncIO2Write.h
# End Source File
# Begin Source File

SOURCE=.\OpcTask\OTDisconnect.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScOpcClient.h
# End Source File
# Begin Source File

SOURCE=.\ScOpcClientDoc.h
# End Source File
# Begin Source File

SOURCE=.\ScOpcClientView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\OpcTask\TaskFileMacroDef.h
# End Source File
# Begin Source File

SOURCE=.\TaskLogFile.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ScOpcClient.ico
# End Source File
# Begin Source File

SOURCE=.\res\ScOpcClient.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ScOpcClientDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Protocol"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\interface\OPCCOMN.H
# End Source File
# Begin Source File

SOURCE=.\interface\Opccomn_i.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\interface\OPCDA.H
# End Source File
# Begin Source File

SOURCE=.\interface\opcda_cats.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\interface\OPCDA_I.C
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\interface\opcenum_clsid.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\interface\OpcError.h
# End Source File
# Begin Source File

SOURCE=.\interface\OPCProps.h
# End Source File
# End Group
# Begin Group "CommuUtil"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\CommUtil\CoTaskMemory.cpp
# End Source File
# Begin Source File

SOURCE=..\include\LockHelper.h
# End Source File
# Begin Source File

SOURCE=..\CommUtil\StringHelper.cpp
# End Source File
# Begin Source File

SOURCE=..\CommUtil\VariantHelper.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\html1.htm
# End Source File
# End Target
# End Project
