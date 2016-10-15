#include "StdAfx.h"
#include "ConditionEventCenter.h"


ConditionEventCenter::ConditionEventCenter(void) 
{
	m_CondNames.push_back( "L" );
	m_CondNames.push_back( "LL" );
	m_CondNames.push_back( "LLL" );
	m_CondNames.push_back( "H" );
	m_CondNames.push_back( "HH" );
	m_CondNames.push_back( "HHH" );
}


ConditionEventCenter::~ConditionEventCenter(void)
{
}

void ConditionEventCenter::Release()
{
	delete this;
}

BOOL ConditionEventCenter::Start()
{
	OpcEventCategory category( condition_category, OPC_CONDITION_EVENT, "Condition Category" );
	
	for_each( m_CondNames.begin(), m_CondNames.end(), [&](const string& name)
	{
		_AddCondition( category, name );
	});

	g_ScOpcAeSvr.AddCategory( condition_category, category );

	StartThread();

	return TRUE;
}

void ConditionEventCenter::Stop()
{
	StopThread();
}

UINT ConditionEventCenter::Run()
{
	while( WaitForSingleObject(m_hQuitEvent, 1000) == WAIT_TIMEOUT )
	{
		vector<DWORD> dwAreaIds;
		string strSource;
		AreaBuilder::ChooseSource( dwAreaIds, strSource );

		int index = rand() % m_CondNames.size();
		string condName = m_CondNames[index];

		IOpcConditionEvent* pEvent = g_ScOpcAeSvr.FindEvent( dwAreaIds.size(), &(dwAreaIds[0]), strSource.c_str(), condName.c_str() );
		if( pEvent )
		{
			pEvent->SetActive( !pEvent->IsActive() );
		}
		else
		{
			pEvent = CreateConditionEvent( strSource.c_str(), condition_category, rand() % 1000 + 1, 
											dwAreaIds.size(), &(dwAreaIds[0]), condName.c_str(), condName.c_str() );
			pEvent->SetActive( TRUE );
		}

		g_ScOpcAeSvr.ReportEvent( pEvent );
		pEvent->Release();

	}

	return 0;
}

void ConditionEventCenter::_AddCondition( OpcEventCategory& category, const string& name )
{
	OpcCondition condition;
	condition.SetName( name.c_str() );

	OpcSubcondition subcondition;
	subcondition.SetName( name.c_str() );
	subcondition.SetSeverity( 101 );
	subcondition.SetMessage( "message content" );
	subcondition.SetDefinition( "def content" );
	condition.AddSubcondition( subcondition );

	category.AddCondition( condition );
}
