#if !defined(IUPDATE_DATA_HANDLER_H)
#define IUPDATE_DATA_HANDLER_H

interface IUpdateDataHandler 
{
	virtual void UpdateData( HANDLE hClient, VARIANT& variant, WORD quality, FILETIME time ) = 0;
	virtual void UpdateData( DWORD dwCount, HANDLE* pClientHandles, VARIANT* pValues, WORD* pQualities, FILETIME* pTimes, HRESULT* pErrors ) = 0;
};

#endif 