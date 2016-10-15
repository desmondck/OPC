// IOpcTask.h: interface for the IOpcTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOPCTASK_H__0E986B45_7ED4_4301_AD48_2C71972C78D8__INCLUDED_)
#define AFX_IOPCTASK_H__0E986B45_7ED4_4301_AD48_2C71972C78D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
using namespace std;

#include "TaskFileReader.h"

enum Opc_Task_Type
{
	OT_Connect,
	OT_Disconnect,
	OT_AddGroup,
	OT_RemoveGroup,
	//IOPCItemMgt
	OT_IOPCItemMgt_AddItems,
	OT_IOPCItemMgt_RemoveItems,
	//IOPCSyncIO
	OT_IOPCSyncIO_Read,
	OT_IOPCSyncIO_Write,
	//IOPCAsyncIO2
	OT_IOPCAsyncIO2_Read,
	OT_IOPCAsyncIO2_Write,
};

interface IPermanent
{
	virtual HRESULT Unserialize( TaskFileReader& ar ) = 0;
};

interface IOpcTask : public IPermanent
{
	virtual CString	GetTaskName() = 0;
	virtual Opc_Task_Type GetTaskType() = 0;
	virtual DWORD	GetTaskId() = 0;
	
	virtual HRESULT	Run() = 0;
	virtual void	Stop() = 0;
	virtual	BOOL	InRunning() = 0;

	virtual IOpcTask* CreateInstance() = 0;

	virtual ~IOpcTask() {}
};

#endif // !defined(AFX_IOPCTASK_H__0E986B45_7ED4_4301_AD48_2C71972C78D8__INCLUDED_)
