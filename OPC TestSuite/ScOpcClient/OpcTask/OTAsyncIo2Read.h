// OTAsyncIo2Read.h: interface for the OTAsyncIo2Read class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTASYNCIO2READ_H__BA451896_2AA9_4F01_B576_702109048833__INCLUDED_)
#define AFX_OTASYNCIO2READ_H__BA451896_2AA9_4F01_B576_702109048833__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class OTAsyncIo2Read : public OpcTask  
{
public:
	OTAsyncIo2Read();
	virtual ~OTAsyncIo2Read();

	virtual IOpcTask*	CreateInstance();
private:
	virtual HRESULT		DoUnserialize( TaskFileReader& taskFileReader );
	virtual HRESULT		DoRun();
private:
	GROUP_ITEMS_MAP	m_GroupToItems;
};

#endif // !defined(AFX_OTASYNCIO2READ_H__BA451896_2AA9_4F01_B576_702109048833__INCLUDED_)
