#pragma once
#include "DemoDriver.h"

class OpcDaDemoSvr : public IOPCDACallback
{
public:
	OpcDaDemoSvr(void);
	~OpcDaDemoSvr(void);

public:
	BOOL Start();
	void Stop();
	void RegServer();
	void UnregServer();
	DWORD ServerInUse();
	IOpcDaCltInfoList*	GetClientInfoList();

public:	//IOPCDACallback
	void	GetStatus( OPCSERVERSTATE& state, DWORD& dwBandWidth, WORD& wMajor, 
					WORD& wMinor, WORD& wBuildNum, char*& pVendor ) override;
	HRESULT QueryOrganization( OPCNAMESPACETYPE& nameSpaceType ) override;
	DWORD	GetBrowserVersion() override;
	const IOpcNode* GetBrowser( TCHAR& cSeparator ) override;
	DWORD	GetUpdateRate( DWORD dwRequestRate ) override;
	HRESULT Subscribe( DWORD dwCount, const char** pItemIDs, const char** pAccessPaths, CTag** ppTags, HRESULT* pErrors ) override;
	HRESULT Unsubscribe( DWORD dwCount, CTag** ppTags ) override;
	HRESULT ReadTags( DWORD dwCount, CTag** ppTags, VARIANT* pItemValues, HRESULT* ppErrors ) override;	
	HRESULT WriteTags( DWORD dwCount, CTag** ppTags, VARIANT* pItemValues, HRESULT* ppErrors ) override;

private:
	ScOpcDaSvr	m_ScOpcDaSvr;

	DemoDriver m_DemoDriver;

	string	m_strVendor;
};

