// OPCSvrHelper.h: interface for the OPCSvrHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPCSVRHELPER_H__1B6EEEEC_30C4_4CB6_8AF0_E87EF5256281__INCLUDED_)
#define AFX_OPCSVRHELPER_H__1B6EEEEC_30C4_4CB6_8AF0_E87EF5256281__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OPCWrap.h"

#include <vector>
using namespace std;

#define OPC_PROTOCOL_10 10
#define OPC_PROTOCOL_20 20


struct OPCServerInfo
{
    CString     ProgID;
    CString     Name;
    CLSID       ClsID;
    OPCServerInfo( LPOLESTR progID, CString name, CLSID& clsid )
        : ProgID(progID), Name(name), ClsID(clsid) {}
};

class OPCSvrHelper  
{
public:
	static HRESULT EnumOpcServers( const CString& strSvrAddr, const CString& protocolVer, vector<OPCServerInfo>& opcSvrList );
	static HRESULT Connect( const CString& strSvrAddr, const CString& strSvrName, const CString& strProtVer, OPCServer& opcServer );

private:
	static BOOL _FindSvrClsID( const CString& strSvrAddr, const CString& strSvrName, const CString& strProtVer, CLSID& clsID );
	static BOOL _IsLocalServer( const CString& strSvrAddr );

private:
	OPCSvrHelper();
	virtual ~OPCSvrHelper();

};

#endif // !defined(AFX_OPCSVRHELPER_H__1B6EEEEC_30C4_4CB6_8AF0_E87EF5256281__INCLUDED_)
