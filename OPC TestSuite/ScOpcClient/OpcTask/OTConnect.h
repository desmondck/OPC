// OTConnect.h: interface for the OTConnect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTCONNECT_H__A575A6FF_4415_4DEB_A11B_CAB0B44B6B08__INCLUDED_)
#define AFX_OTCONNECT_H__A575A6FF_4415_4DEB_A11B_CAB0B44B6B08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OpcTask.h"

class OTConnect : public OpcTask
{
public:
	OTConnect();
	virtual ~OTConnect();

	//Override IOpcTask
	virtual HRESULT	DoRun();
	virtual IOpcTask* CreateInstance();
protected:
	virtual HRESULT DoUnserialize( TaskFileReader& taskFileReader );
private:
	ServerInfo	m_SvrInfo;
};

#endif // !defined(AFX_OTCONNECT_H__A575A6FF_4415_4DEB_A11B_CAB0B44B6B08__INCLUDED_)
