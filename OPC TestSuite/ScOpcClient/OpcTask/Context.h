// Context.h: interface for the Context class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTEXT_H__BAF76B6E_C45C_404B_B872_BF3E932EF249__INCLUDED_)
#define AFX_CONTEXT_H__BAF76B6E_C45C_404B_B872_BF3E932EF249__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IOpcTask.h"

typedef vector<IOpcTask*> TASK_LIST;
typedef map<CString, IOpcTask*> TASK_MAP;

class Context
{
public:
	Context();
	virtual ~Context();

	virtual BOOL Unserialize( CArchive& ar, CString& strErrMsg );
	
	HRESULT	RunAllTasks();
	void	Stop();
	void	ClearAllTask();

	BOOL	TasksInRunning();
private:
	HRESULT _AddTask( IOpcTask* pTask );
	HRESULT _ValidateTask( IOpcTask* pTask );
	void	_FindTaskByType( IOpcTask* pEndTask, Opc_Task_Type type, vector<IOpcTask*>& taskList );
private:
	TASK_LIST::iterator	_FindStartTask( IOpcTask* pSpecTask );
	TASK_LIST::iterator _FindEndTask( TASK_LIST::iterator itStart, IOpcTask* pEndTask );
	
	BOOL	_HaveConnect( IOpcTask* pSpecTask );
	BOOL	_HaveGroup( IOpcTask* pSpecTask );
private:
	TASK_LIST	m_StandardTasks;
	TASK_MAP	m_StandardTaskMaps;
	TASK_LIST	m_Tasks;

	IOpcTask*	m_DisconnTask;
};

#endif // !defined(AFX_CONTEXT_H__BAF76B6E_C45C_404B_B872_BF3E932EF249__INCLUDED_)
