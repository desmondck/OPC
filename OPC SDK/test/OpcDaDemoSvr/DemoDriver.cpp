#include "StdAfx.h"
#include "DemoDriver.h"

#define VAR_TYPE_STRING( x ) #x

#define ADD_TAG_BY_TYPE( vtDataType )	\
{										\
	CTag* pTag = new CTag();			\
	pTag->SetDataType( vtDataType );	\
										\
	VARIANT variant;					\
	ZeroMemory( &variant, sizeof(variant) );		\
	variant.vt = pTag->GetDataType();	\
	WORD wQuality = OPC_QUALITY_GOOD;	\
	FILETIME ftNow;						\
	CoFileTimeNow( &ftNow );			\
	pTag->SetVQT( &variant, &wQuality, &ftNow );	\
										\
	string tagName = "Tag_";			\
	tagName.append( #vtDataType );		\
										\
	m_AllTags[tagName] = pTag;			\
}

DemoDriver::DemoDriver(void)
{
	_InitTags();

	StartThread();
}


DemoDriver::~DemoDriver(void)
{
	StopThread();

	CSLockType lock(m_CSLock);

	for_each( m_AllTags.begin(), m_AllTags.end(), [&]( const pair<string, CTag*>& element )
	{
		delete element.second;
	});
	m_AllTags.clear();
}

void DemoDriver::GetBrowser( IOpcNodeRicher* pCurrentNode )
{
	CSLockType lock(m_CSLock);

	OpcNodeListBuilder builder;
	for_each( m_AllTags.begin(), m_AllTags.end(), [&]( const pair<string, CTag*>& element )
	{
		const string& strTagName = element.first;
		CTag* pTag = element.second;

		IOpcNodeRicher* pTagNode = CreateOpcNodeRicher( strTagName.c_str(), VT_EMPTY, 0 );

		IOpcNodeRicher* pFieldNode = CreateOpcNodeRicher("value", pTag->GetDataType(), pTag->GetAccessRights());
		if( strTagName.compare("Tag_VT_I4") == 0 )
		{
			OpcItemPropListBuilder propBuilder;

			string strPropItemId = "Tag_VT_BOOL/value";
			propBuilder.Add( CreateItemProperty(501, "item prop with item id", VT_BOOL, strPropItemId.c_str(), nullptr), TRUE );
			
			VARIANT vValue;
			vValue.vt = VT_R4;
			vValue.fltVal = 66.66f;
			propBuilder.Add( CreateItemProperty(502, "item prop test", VT_R4, nullptr, &vValue), TRUE );

			pFieldNode->SetItemProperties( propBuilder.Detach(), TRUE );
		}
		pTagNode->SetChildNode( pFieldNode, TRUE );

		builder.Add( pTagNode, TRUE );
	});

	pCurrentNode->SetChildNodes( builder.Detach(), TRUE );
}

void DemoDriver::_InitTags()
{
	ADD_TAG_BY_TYPE( VT_BOOL );
	ADD_TAG_BY_TYPE( VT_I1 );
	ADD_TAG_BY_TYPE( VT_I2 );
	ADD_TAG_BY_TYPE( VT_I4 );
	ADD_TAG_BY_TYPE( VT_R4 );
	ADD_TAG_BY_TYPE( VT_R8 );
	ADD_TAG_BY_TYPE( VT_DATE );
	ADD_TAG_BY_TYPE( VT_BSTR );
	ADD_TAG_BY_TYPE( VT_UI1 );
	ADD_TAG_BY_TYPE( VT_UI2 );
	ADD_TAG_BY_TYPE( VT_UI4 );
}

HRESULT DemoDriver::Subscribe( DWORD dwCount, const char** pItemIDs, CTag** ppTags, HRESULT* pErrors )
{
	CSLockType lock(m_CSLock);

	for( auto i = 0; i < dwCount; ++i )
	{
		string strTagName = pItemIDs[i];
		int index = strTagName.rfind( SEPERATOR_CHAR );
		strTagName.erase( index );
		ALL_TAG_MAP::iterator it = m_AllTags.find( strTagName );
		if( it == m_AllTags.end() )
		{
			pErrors[i] = E_FAIL;
			continue;
		}

		pErrors[i]	= S_OK;
		ppTags[i]	= it->second;
	}

	return S_OK;
}

HRESULT DemoDriver::Unsubscribe( DWORD dwCount, CTag** ppTags )
{
	return S_OK;
}

HRESULT DemoDriver::WriteTags( DWORD dwCount, CTag** ppTags, VARIANT* pItemValues, HRESULT* ppErrors )
{
	CSLockType lock(m_CSLock);

	for( auto i = 0; i < dwCount; ++i )
	{
		CTag* pTag = ppTags[i];
		if( pTag == nullptr )
			continue;

		FILETIME ftNow;
		CoFileTimeNow( &ftNow );
		WORD wQuality = OPC_QUALITY_GOOD;
		pTag->SetVQT( pItemValues + i, &wQuality, &ftNow );
		ppErrors[i] = S_OK;
	}

	return S_OK;
}

UINT DemoDriver::Run()
{
	while( WaitForSingleObject(m_hQuitEvent, 3000) == WAIT_TIMEOUT )
	{
		//临时用一下这个线程

		
	}

	return 0;
}
