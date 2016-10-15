#include "StdAfx.h"
#include "SimpleEventCenter.h"


SimpleEventCenter::SimpleEventCenter(void)
{
}


SimpleEventCenter::~SimpleEventCenter(void)
{
}

void SimpleEventCenter::Release()
{
	delete this;
}

BOOL SimpleEventCenter::Start()
{
	OpcEventCategory category( simple_category, OPC_SIMPLE_EVENT, "Simple Category" );
	g_ScOpcAeSvr.AddCategory( simple_category, category );

	StartThread();

	return TRUE;
}

void SimpleEventCenter::Stop()
{
	StopThread();
}

UINT SimpleEventCenter::Run()
{
	while( WaitForSingleObject(m_hQuitEvent, 1000) == WAIT_TIMEOUT )
	{
		vector<DWORD> dwAreaIds;
		string strSource;
		AreaBuilder::ChooseSource( dwAreaIds, strSource );

		IOpcSimpleEvent* pEvent = CreateSimpleEvent( strSource.c_str(), simple_category, 3, dwAreaIds.size(), &dwAreaIds[0] );
		pEvent->SetMessage( "Simple Event" );

		g_ScOpcAeSvr.ReportEvent( pEvent );
		pEvent->Release();
	}

	return 0;
}
