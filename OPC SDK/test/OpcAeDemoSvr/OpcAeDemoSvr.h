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

	//�μ�IOPCEventServer:: CreateEventSubscription
	DWORD ReviseMaxSize( DWORD dwMaxSize ) const override;
	DWORD ReviseBufTime( DWORD dwBufferTime ) const override;

	//OPC�ͻ���ִ�б���ȷ��
	HRESULT ClientAlarmAck( DWORD dwCount, IOpcConditionEvent** ppEvents, LPCTSTR pszAckId, LPCTSTR pszComment, HRESULT* pErrors ) override;

private:
	string		m_strVendor;

	vector<IAlarmEventCenter*>	m_EventCenters;
};

