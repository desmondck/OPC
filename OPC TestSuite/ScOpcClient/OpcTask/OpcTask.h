// OpcTask.h: interface for the OpcTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPCTASK_H__AF5B4487_5AA0_420E_83B4_6C634BB2DDEC__INCLUDED_)
#define AFX_OPCTASK_H__AF5B4487_5AA0_420E_83B4_6C634BB2DDEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IOpcTask.h"
#include "TaskFileReader.h"

class OpcTask : public IOpcTask  
{
public:
	OpcTask( Opc_Task_Type type, const CString& taskName );
	virtual ~OpcTask();

	virtual HRESULT Unserialize( TaskFileReader& taskFileReader );

	virtual CString	GetTaskName() { return m_TaskName; }
	virtual Opc_Task_Type GetTaskType() { return m_Type; }
	virtual DWORD	GetTaskId() { return m_TaskId; }

	virtual HRESULT	Run();
	virtual void	Stop();
	virtual	BOOL	InRunning();
protected:
	virtual HRESULT DoUnserialize( TaskFileReader& taskFileReader ) = 0;
	virtual IOpcTask*	CreateInstance() = 0;
	virtual HRESULT	DoRun() = 0;
protected:
	HRESULT _UnserializeGroupItems( TaskFileReader& taskFileReader, GROUP_ITEMS_MAP& groupItems );
	HRESULT	_UnserializeVariants( TaskFileReader& taskFileReader, vector<VARIANT>& vDataValues );
	BOOL	_GetDataValueInfo( const CString& strDataInfo, VARIANT& vValue );
public:
	HRESULT DoIndependRunProc();
private:
	Opc_Task_Type m_Type;
	CString	m_TaskName;

	DWORD	m_TaskId;
	static	DWORD m_TaskIdGenerator;

	HANDLE	m_hThread;
	HANDLE	m_hStopEvent;
	HANDLE	m_hFinishEvent;

	TaskRunConfig	m_TaskRunCfg;
};

#endif // !defined(AFX_OPCTASK_H__AF5B4487_5AA0_420E_83B4_6C634BB2DDEC__INCLUDED_)
