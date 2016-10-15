// OTAddGroup.h: interface for the OTAddGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTADDGROUP_H__3161534B_F01A_4ED7_9D9C_D5BED477EEC6__INCLUDED_)
#define AFX_OTADDGROUP_H__3161534B_F01A_4ED7_9D9C_D5BED477EEC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OpcTask.h"
#include "OpcGroupProxy.h"

class OTAddGroup : public OpcTask  
{
public:
	OTAddGroup();
	virtual ~OTAddGroup();

	virtual IOpcTask* CreateInstance();
protected:
	virtual HRESULT DoUnserialize( TaskFileReader& taskFileReader );
	virtual HRESULT	DoRun();	
private:
	vector<GroupState>	m_Groups;
};

#endif // !defined(AFX_OTADDGROUP_H__3161534B_F01A_4ED7_9D9C_D5BED477EEC6__INCLUDED_)
