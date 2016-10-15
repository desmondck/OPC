#include "StdAfx.h"
#include "TrackingEventCenter.h"


TrackingEventCenter::TrackingEventCenter(void)
{
}


TrackingEventCenter::~TrackingEventCenter(void)
{
}

void TrackingEventCenter::Release()
{
	delete this;
}

BOOL TrackingEventCenter::Start()
{
	OpcEventCategory category( tracking_category, OPC_TRACKING_EVENT, "Tracking Category" );
	g_ScOpcAeSvr.AddCategory( tracking_category, category );

	StartThread();

	return TRUE;
}

void TrackingEventCenter::Stop()
{
	StopThread();
}

UINT TrackingEventCenter::Run()
{
	while( WaitForSingleObject(m_hQuitEvent, 1000) == WAIT_TIMEOUT )
	{
		vector<DWORD> dwAreaIds;
		string strSource;
		AreaBuilder::ChooseSource( dwAreaIds, strSource );

		IOpcTrackingEvent* pEvent = CreateTrackingEvent( strSource.c_str(), tracking_category, 200, 
													dwAreaIds.size(), &(dwAreaIds[0]), "Wang, Chunjie" );
		pEvent->SetMessage( "Tracking Item" );
		g_ScOpcAeSvr.ReportEvent( pEvent );
		pEvent->Release();
	}

	return 0;
}
