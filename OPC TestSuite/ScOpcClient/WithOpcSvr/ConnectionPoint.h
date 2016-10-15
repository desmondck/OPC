//**************************************************************************
//
//  Copyright (c) FactorySoft, INC. 1996-1998, All Rights Reserved
//
//**************************************************************************
//
//  Filename   :  ConnectionPoint.h
//  $Author    :  Jim Hansen
//
//  Description:  Callback class for OPC Data Access 2.0
//
//
//**************************************************************************
#ifndef CONNECTIONPOINT_HPP
#define CONNECTIONPOINT_HPP

#include "OPCWrap.h"    // wrapper classes around the OPC interface

#include "IShutdownHandler.h"
#include "IUpdateDataHandler.h"

extern CComModule _Module;

#include <atlcom.h>

class COPCLink;

class OPCCallback :
   public IOPCDataCallback,
   public CComObjectRootEx<CComMultiThreadModel>
{
public:
	OPCCallback() { m_pUpdateDataHandler = NULL; }
	virtual  ~OPCCallback(){}

BEGIN_COM_MAP(OPCCallback)
   COM_INTERFACE_ENTRY(IOPCDataCallback)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(OPCCallback)

	// The OPC Callback functions
	STDMETHODIMP OnDataChange( DWORD Transid, OPCHANDLE grphandle, HRESULT masterquality, HRESULT mastererror, DWORD count, 
							OPCHANDLE* clienthandles, VARIANT* values, WORD* quality, FILETIME* time, HRESULT* errors );
	STDMETHODIMP OnReadComplete( DWORD Transid, OPCHANDLE grphandle, HRESULT masterquality, HRESULT mastererror, DWORD count, 
							OPCHANDLE* clienthandles, VARIANT* values, WORD* quality, FILETIME* time, HRESULT* errors );
	STDMETHODIMP OnWriteComplete( DWORD Transid, OPCHANDLE grphandle, HRESULT mastererr, DWORD count, 
							OPCHANDLE* clienthandles, HRESULT* errors );
	STDMETHODIMP OnCancelComplete( DWORD transid, OPCHANDLE grphandle );

public:
	void SetCallbackObject( IUpdateDataHandler* pUpdateData );

private:
	IUpdateDataHandler* m_pUpdateDataHandler;
};

typedef CComObject<OPCCallback> OPCCallbackObject;

//**************************************************************************
class OPCShutdown :
   public IOPCShutdown,
   public CComObjectRootEx<CComMultiThreadModel>
{
public:
	OPCShutdown() { m_pShutdownHandler = NULL; }
	virtual  ~OPCShutdown(){}

BEGIN_COM_MAP(OPCShutdown)
   COM_INTERFACE_ENTRY(IOPCShutdown)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(OPCShutdown)

   // The OPC Callback function
   STDMETHODIMP ShutdownRequest(LPCWSTR szReason);

public:
	void SetCallbackObject( IShutdownHandler* pShutdown );
private:
   IShutdownHandler* m_pShutdownHandler;
};

typedef CComObject<OPCShutdown> OPCShutdownObject;

#endif	//CONNECTIONPOINT_HPP