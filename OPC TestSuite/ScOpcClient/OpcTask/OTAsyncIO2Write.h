// OTAsyncIO2Write.h: interface for the OTAsyncIO2Write class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTASYNCIO2WRITE_H__9353DE8C_8AEC_4687_A935_425696FA41E3__INCLUDED_)
#define AFX_OTASYNCIO2WRITE_H__9353DE8C_8AEC_4687_A935_425696FA41E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class OTAsyncIO2Write : public OpcTask  
{
public:
	OTAsyncIO2Write();
	virtual ~OTAsyncIO2Write();
	
	virtual IOpcTask*	CreateInstance();
private:
	virtual HRESULT		DoUnserialize( TaskFileReader& taskFileReader );
	virtual HRESULT		DoRun();
private:
	vector<VARIANT>	m_vDataValues;
	GROUP_ITEMS_MAP	m_GroupToItems;
	
	DWORD m_dwValueIndex;
};

#endif // !defined(AFX_OTASYNCIO2WRITE_H__9353DE8C_8AEC_4687_A935_425696FA41E3__INCLUDED_)
