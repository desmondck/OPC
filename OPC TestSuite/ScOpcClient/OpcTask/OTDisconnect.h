// OTDisconnect.h: interface for the OTDisconnect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTDISCONNECT_H__5DE28E6B_9239_4094_B2DF_848F4AA6B65F__INCLUDED_)
#define AFX_OTDISCONNECT_H__5DE28E6B_9239_4094_B2DF_848F4AA6B65F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OpcTask.h"

class OTDisconnect : public OpcTask  
{
public:
	OTDisconnect();
	virtual ~OTDisconnect();
	
	virtual HRESULT	DoRun();
	virtual IOpcTask* CreateInstance();
protected:
	virtual HRESULT DoUnserialize( TaskFileReader& taskFileReader );
};

#endif // !defined(AFX_OTDISCONNECT_H__5DE28E6B_9239_4094_B2DF_848F4AA6B65F__INCLUDED_)
