#include "StdAfx.h"
#include "AreaBuilder.h"
#include "OpcAeObjFactory.h"
#include "time.h"

IOpcAreaNode*	AreaBuilder::m_pAreaRoot = nullptr;

IOpcAreaNode* AreaBuilder::GetBrowser()
{
	return_if( m_pAreaRoot, m_pAreaRoot );

	m_pAreaRoot = CreateOpcAreaNode( 0, _T("root") );

	//一级节点
	for( auto i = 0; i < 2; ++i )
	{
		char AreaName[32] = { 0 };
		sprintf_s( AreaName, "Ctrl Domain %d", i );
		IOpcAreaNode* pAreaNode = CreateOpcAreaNode( i, AreaName );

		//二级节点
		for( auto k = 0; k < 2; ++k )
		{
			char SubAreaName[32] = { 0 };
			sprintf_s( SubAreaName, "Ctrl Station %d", k );
			IOpcAreaNode* pSubAreaNode = CreateOpcAreaNode( k, SubAreaName );

			//Source
			for( auto m = 0; m < 3; ++m )
			{
				char TagName[32] = { 0 };
				sprintf_s( TagName, "Tag %d", m );
				pSubAreaNode->AddSource( TagName );
			}

			pAreaNode->AddChild( pSubAreaNode, TRUE );
		}

		m_pAreaRoot->AddChild( pAreaNode, TRUE );
	}

	IOpcAreaNode* pAreaNode = CreateOpcAreaNode( 5, "" );
	m_pAreaRoot->AddChild( pAreaNode, TRUE );

	return m_pAreaRoot;
}

void AreaBuilder::ChooseSource( vector<DWORD>& dwAreaIds, string& strSource )
{
	srand( (unsigned)time( NULL ) );

	DWORD dwAreaIndex = rand() % 2;
	const IOpcAreaNode* pAreaNode = m_pAreaRoot->GetChild( dwAreaIndex );
	dwAreaIds.push_back( dwAreaIndex );

	DWORD dwSubAreaIndex = rand() % 2;
	const IOpcAreaNode* pSubAreaNode = pAreaNode->GetChild( dwSubAreaIndex );
	dwAreaIds.push_back( dwSubAreaIndex );

	DWORD dwSourceIndex = rand() % 3;
	strSource = pSubAreaNode->GetSource( dwSourceIndex );
}
