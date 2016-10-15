#include "StdAfx.h"
#include "OpcDaDemoSvr.h"

// Also put this GUID into the OPCServer.rgs file
// {474ADE1F-6E84-4DCF-9139-DE06EC6D9C89}
static GUID CLSID_OPCServer = 
{ 0x474ade1f, 0x6e84, 0x4dcf, { 0x91, 0x39, 0xde, 0x6, 0xec, 0x6d, 0x9c, 0x89 } };

OpcDaDemoSvr::OpcDaDemoSvr(void) : m_strVendor("Wang, Chunjie")
{
}

OpcDaDemoSvr::~OpcDaDemoSvr(void)
{
}

DWORD OpcDaDemoSvr::ServerInUse()
{
	return m_ScOpcDaSvr.ServerInUse();
}

IOpcDaCltInfoList* OpcDaDemoSvr::GetClientInfoList()
{
	return m_ScOpcDaSvr.GetClientInfoList();
}

void OpcDaDemoSvr::RegServer()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	HRESULT hr = m_ScOpcDaSvr.StartServer(hInstance, &CLSID_OPCServer);
	if( FAILED(hr) )
		return;

	hr = m_ScOpcDaSvr.RegisterServer();
}

void OpcDaDemoSvr::UnregServer()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	if( FAILED(m_ScOpcDaSvr.StartServer(hInstance, &CLSID_OPCServer)) )
		return;

	HRESULT hr = m_ScOpcDaSvr.UnregisterServer();
}


BOOL OpcDaDemoSvr::Start()
{
	//m_ScOpcDaSvr.SetMaxTagCount( 5 );
	m_ScOpcDaSvr.SetCallback( this );
	HRESULT hr = m_ScOpcDaSvr.StartServer( GetModuleHandle(NULL), &CLSID_OPCServer );

	return TRUE;
}

void OpcDaDemoSvr::Stop()
{
	m_ScOpcDaSvr.StopServer();
}

void OpcDaDemoSvr::GetStatus( OPCSERVERSTATE& state, DWORD& dwBandWidth, WORD& wMajor, WORD& wMinor, 
							WORD& wBuildNum, char*& pVendor )
{
	state	= OPC_STATUS_RUNNING;
	wMajor	= 1;
	wMajor	= 1;
	wBuildNum = 1;
	pVendor	= (char*)m_strVendor.c_str();
}

HRESULT OpcDaDemoSvr::QueryOrganization( OPCNAMESPACETYPE& nameSpaceType )
{
	nameSpaceType = OPC_NS_HIERARCHIAL;

	return S_OK;
}

DWORD OpcDaDemoSvr::GetBrowserVersion()
{
	return 0;
}

const IOpcNode* OpcDaDemoSvr::GetBrowser( TCHAR& cSeparator )
{
	cSeparator = SEPERATOR_CHAR;
	IOpcNodeRicher* pRootNode = CreateOpcNodeRicher( "root", VT_EMPTY, 0 );
	m_DemoDriver.GetBrowser( pRootNode );
	
	return pRootNode;
}

DWORD OpcDaDemoSvr::GetUpdateRate( DWORD dwRequestRate )
{
	return 500;
}

HRESULT OpcDaDemoSvr::Subscribe( DWORD dwCount, const char** pItemIDs, const char** pAccessPaths, CTag** ppTags, HRESULT* pErrors )
{
	return m_DemoDriver.Subscribe( dwCount, pItemIDs, ppTags, pErrors );
}

HRESULT OpcDaDemoSvr::Unsubscribe( DWORD dwCount, CTag** ppTags )
{
	return m_DemoDriver.Unsubscribe( dwCount, ppTags );
}

HRESULT OpcDaDemoSvr::ReadTags( DWORD dwCount, CTag** ppTags, VARIANT* pItemValues, HRESULT* ppErrors )
{
	return E_NOTIMPL;
}

HRESULT OpcDaDemoSvr::WriteTags( DWORD dwCount, CTag** ppTags, VARIANT* pItemValues, HRESULT* ppErrors )
{
	return m_DemoDriver.WriteTags( dwCount, ppTags, pItemValues, ppErrors );
}



