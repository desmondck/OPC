#pragma once

#include <vector>
using namespace std;

#include "IAlarmEventCenter.h"

class OpcAeDemoSvr : public IOpcAeCallback
{
public:
	OpcAeDemoSvr(void);
	~OpcAeDemoSvr(void);

	void RegServer();
	void UnregServer();

	BOOL Start();
	void Stop();

	DWORD ServerInUse();

public:
	const IOpcAreaNode* GetBrowser( DWORD& dwVersion, TCHAR& cSeparator ) override;

	//参见IOPCEventServer:: CreateEventSubscription
	DWORD ReviseMaxSize( DWORD dwMaxSize ) const override;
	DWORD ReviseBufTime( DWORD dwBufferTime ) const override;

	//OPC客户端执行报警确认
	HRESULT ClientAlarmAck( DWORD dwCount, IOpcConditionEvent** ppEvents, LPCTSTR pszAckId, LPCTSTR pszComment, HRESULT* pErrors ) override;

private:
	string		m_strVendor;

	vector<IAlarmEventCenter*>	m_EventCenters;
};

