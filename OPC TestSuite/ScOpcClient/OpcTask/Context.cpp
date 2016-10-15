// Context.cpp: implementation of the Context class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Context.h"

#include "OTConnect.h"
#include "OTDisconnect.h"
#include "OTAddGroup.h"
#include "OTIOPCItemMgtAddItems.h"
#include "OTIOPCSyncIOWrite.h"
#include "OTAsyncIO2Write.h"
#include "OTAsyncIo2Read.h"
#include "OTIOPCSyncIORead.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

Context::Context()
{
	m_DisconnTask = new OTDisconnect();

	m_StandardTasks.push_back( new OTConnect() );
	m_StandardTasks.push_back( new OTAddGroup() );
	m_StandardTasks.push_back( new OTIOPCItemMgtAddItems() );
	m_StandardTasks.push_back( new OTIOPCSyncIOWrite() );
	m_StandardTasks.push_back( new OTAsyncIO2Write() );
	m_StandardTasks.push_back( new OTAsyncIo2Read() );
	m_StandardTasks.push_back( new OTDisconnect() );
	m_StandardTasks.push_back( new OTIOPCSyncIORead() );
	
	for( int i = 0; i < m_StandardTasks.size(); ++i )
	{
		IOpcTask* pTask = m_StandardTasks[i];
		m_StandardTaskMaps[pTask->GetTaskName()] = pTask;
	}
}

Context::~Context()
{
	delete m_DisconnTask;
	m_DisconnTask = NULL;

	m_StandardTaskMaps.clear();
	for( int i = 0; i < m_StandardTasks.size(); ++i )
		delete m_StandardTasks[i];
	m_StandardTasks.clear();
}

BOOL Context::Unserialize( CArchive& ar, CString& strErrMsg  )
{
	TaskFileReader taskFileReader( &ar );

	HRESULT hr = S_OK;	

	//依次反序列化任务
	CString strTaskName;
	while( taskFileReader.ReadTaskName( strTaskName ) )
	{
		TASK_MAP::iterator it = m_StandardTaskMaps.find( strTaskName );
		if( it == m_StandardTaskMaps.end() )
		{
			ClearAllTask();
			hr = E_TASK_NO_FOUND;	//任务名称无效
			break;
		}

		IOpcTask* pNewTask = it->second->CreateInstance();
		hr = pNewTask->Unserialize( taskFileReader );
		if( FAILED(hr) )
		{
			ClearAllTask();
			delete pNewTask;
			break;
		}

		hr = _AddTask(pNewTask);
		if( FAILED( hr ) )				//添加任务失败
		{
			ClearAllTask();
			break;
		}
	}
	
	if( FAILED(hr) )
	{
		ErrorHelper::GetErrorMessage( hr, strErrMsg );
		strErrMsg = strTaskName + ":" + strErrMsg;
	}

	return hr;
}

HRESULT Context::_AddTask( IOpcTask* pTask )
{
	if( pTask == NULL )
		return E_FAIL;

	//首先加到任务列表中
	m_Tasks.push_back( pTask );
	
	HRESULT hr = _ValidateTask( pTask );
	if( FAILED(hr) )	//校验失败
		m_Tasks.pop_back();
	
	return hr;
}

HRESULT Context::_ValidateTask( IOpcTask* pTask )
{
	switch( pTask->GetTaskType() )
	{
	case OT_Connect:	return _HaveConnect( pTask ) ? E_TASK_HAS_CONNECTED : S_OK;
	case OT_AddGroup:	return _HaveConnect( pTask ) ? S_OK : E_TASK_SVR_UNSPECIFIED;
	case OT_IOPCItemMgt_AddItems:	
	case OT_IOPCSyncIO_Read:	//IO操作必须存在Group
	case OT_IOPCSyncIO_Write:
	case OT_IOPCAsyncIO2_Read:
	case OT_IOPCAsyncIO2_Write:
		return _HaveGroup( pTask ) ? S_OK : E_TASK_NO_GROUP;
	case OT_Disconnect:	return _HaveConnect( pTask ) ? S_OK : E_TASK_SVR_UNSPECIFIED;
	}

	return E_FAIL;
}

BOOL Context::_HaveGroup( IOpcTask* pSpecTask )
{
	vector<IOpcTask*> addGroups;
	_FindTaskByType( pSpecTask, OT_AddGroup, addGroups );
	
	vector<IOpcTask*> removeGroups;
	_FindTaskByType( pSpecTask, OT_RemoveGroup, removeGroups );

	return (addGroups.size() - removeGroups.size()) > 0;
}

BOOL Context::_HaveConnect( IOpcTask* pSpecTask )
{
	return _FindStartTask( pSpecTask ) != m_Tasks.end();
}

//在当前任务的上下文中，查找指定类型的任务
void Context::_FindTaskByType( IOpcTask* pEndTask, Opc_Task_Type type, vector<IOpcTask*>& taskList )
{
	for( TASK_LIST::iterator it = _FindStartTask(pEndTask); it != m_Tasks.end(); ++it )
	{
		IOpcTask* pTask = *it;
		if( pTask == pEndTask )
			return;
		
		if( pTask->GetTaskType() == type )
			taskList.push_back( pTask );
	}
	
	if( it == m_Tasks.end() )	//pEndTask无效
		taskList.clear();
}

//找到当前任务的起始任务(最近的Connect任务)
TASK_LIST::iterator Context::_FindStartTask( IOpcTask* pSpecTask )
{
	TASK_LIST::iterator itFound = m_Tasks.end();
	for( TASK_LIST::iterator it = m_Tasks.begin(); it != m_Tasks.end(); ++it )
	{
		IOpcTask* pTask = *it;
		if( pTask == pSpecTask )
			break;

		if( pTask->GetTaskType() == OT_Disconnect )
			itFound = m_Tasks.end();	//连接已断开
		
		if( pTask->GetTaskType() == OT_Connect )
			itFound = it;
	}

	return itFound;
}

TASK_LIST::iterator Context::_FindEndTask( TASK_LIST::iterator itStart, IOpcTask* pEndTask )
{
	for( TASK_LIST::iterator it = itStart; it != m_Tasks.end(); ++it )
	{
		if( *it == pEndTask )
			break;
	}

	return it;
}

HRESULT Context::RunAllTasks()
{
	HRESULT hr = S_OK;
	for( TASK_LIST::iterator it = m_Tasks.begin(); it != m_Tasks.end(); ++it )
	{
		HRESULT hr = (*it)->Run();
		if( FAILED(hr) )
			break;
	}
	
	return hr;
}

void Context::Stop()
{
	for( TASK_LIST::iterator it = m_Tasks.begin(); it != m_Tasks.end(); ++it )
		(*it)->Stop();

	m_DisconnTask->Run();
}

BOOL Context::TasksInRunning()
{
	for( TASK_LIST::iterator it = m_Tasks.begin(); it != m_Tasks.end(); ++it )
	{
		if( (*it)->InRunning() )
			return TRUE;
	}	

	return FALSE;
}

void Context::ClearAllTask()
{
	for( TASK_LIST::iterator it = m_Tasks.begin(); it != m_Tasks.end(); ++it )
		delete *it;

	m_Tasks.clear();
}

