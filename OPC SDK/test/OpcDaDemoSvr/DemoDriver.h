#pragma once

#include <map>
using namespace std;

#include "SimpleThread.h"

#include "StlExtend.h"
#include "LockHelper.h"
typedef LockHelper<CCriticalSectionLock> CSLockType;

typedef map<string, CTag*, StringIgnoreLess> ALL_TAG_MAP;

//单驱动，演示目的，不做接口抽象
class DemoDriver : public SimpleThread
{
public:
	DemoDriver(void);
	~DemoDriver(void);

	void GetBrowser( IOpcNodeRicher* pCurrentNode );

	HRESULT Subscribe( DWORD dwCount, const char** pItemIDs, CTag** ppTags, HRESULT* pErrors );
	HRESULT Unsubscribe( DWORD dwCount, CTag** ppTags );
	HRESULT WriteTags( DWORD dwCount, CTag** ppTags, VARIANT* pItemValues, HRESULT* ppErrors );

public:
	UINT Run() override;
private:
	void _InitTags();
private:
	ALL_TAG_MAP	m_AllTags;

	CCriticalSectionLock	m_CSLock;
};

