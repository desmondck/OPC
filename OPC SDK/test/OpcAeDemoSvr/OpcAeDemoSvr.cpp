#include "StdAfx.h"
#include "OpcAeDemoSvr.h"

#include "SimpleEventCenter.h"
#include "TrackingEventCenter.h"
#include "ConditionEventCenter.h"

ScOpcAeSvr	g_ScOpcAeSvr;

// {6AE9F03B-825F-41BD-8F0C-88EE93688E15}
static GUID CLSID_OPCServer = 
{ 0x6ae9f03b, 0x825f, 0x41bd, { 0x8f, 0xc, 0x88, 0xee, 0x93, 0x68, 0x8e, 0x15 } };


OpcAeDemoSvr::OpcAeDemoSvr(void) : m_strVendor("Wang, Chunjie")
{
}


OpcAeDemoSvr::~OpcAeDemoSvr(void)
{
}

void OpcAeDemoSvr::RegServer()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	HRESULT hr = g_ScOpcAeSvr.StartServer(hInstance, &CLSID_OPCServer);
	if( FAILED(hr) )
		return;

	hr = g_ScOpcAeSvr.RegisterServer();
}

void OpcAeDemoSvr::UnregServer()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	if( FAILED(g_ScOpcAeSvr.StartServer(hInstance, &CLSID_OPCServer)) )
		return;

	HRESULT hr = g_ScOpcAeSvr.UnregisterServer();
}

BOOL OpcAeDemoSvr::Start()
{
	AreaBuilder::GetBrowser();

	g_ScOpcAeSvr.SetProductInfo( m_strVendor.c_str(), 1, 1, 1 );
	g_ScOpcAeSvr.SetCallback( this );
	HRESULT hr = g_ScOpcAeSvr.StartServer( GetModuleHandle(NULL), &CLSID_OPCServer );

	m_EventCenters.push_back( new SimpleEventCenter() );
	m_EventCenters.push_back( new TrackingEventCenter() );
	m_EventCenters.push_back( new ConditionEventCenter() );
	for_each( m_EventCenters.begin(), m_EventCenters.end(), [&](IAlarmEventCenter* pCenter)
	{
		pCenter->Start();
	});

	return SUCCEEDED(hr);
}

void OpcAeDemoSvr::Stop()
{
	for_each( m_EventCenters.begin(), m_EventCenters.end(), [&](IAlarmEventCenter* pCenter)
	{
		pCenter->Stop();
		pCenter->Release();
	});
	m_EventCenters.clear();

	g_ScOpcAeSvr.StopServer();
}

DWORD OpcAeDemoSvr::ServerInUse()
{
	return g_ScOpcAeSvr.ServerInUse();
}

/////////////////////////////////IOpcAeCallback/////////////////////////////////////////
const IOpcAreaNode* OpcAeDemoSvr::GetBrowser( DWORD& dwVersion, TCHAR& cSeparator )
{
	dwVersion = 0;
	cSeparator = '/';
	return AreaBuilder::GetBrowser();
}

DWORD OpcAeDemoSvr::ReviseMaxSize( DWORD dwMaxSize ) const 
{
	return 0;
}

DWORD OpcAeDemoSvr::ReviseBufTime( DWORD dwBufferTime ) const 
{
	return 0;
}

HRESULT OpcAeDemoSvr::ClientAlarmAck( DWORD dwCount, IOpcConditionEvent** ppEvents, LPCTSTR pszAckId, LPCTSTR pszComment, HRESULT* pErrors )
{
	return E_NOTIMPL;
}
