// ErrorHelper.cpp: implementation of the ErrorHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scopcclient.h"
#include "ErrorHelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

ERR_MSG_MAP ErrorHelper::m_TaskErrMsgs;

void ErrorHelper::_Init()
{
	if( m_TaskErrMsgs.size() )
		return;
	
	m_TaskErrMsgs[E_TASK_NO_FOUND]			= "指定任务不存在";
	m_TaskErrMsgs[E_TASK_INVALID_PARAM]		= "包含无效参数";
	m_TaskErrMsgs[E_TASK_CONN_FAILED]		= "连接服务器失败!";
	m_TaskErrMsgs[E_TASK_HAS_CONNECTED]		= "连接已建立、不允许针对同一服务器建立多次连接!";
	m_TaskErrMsgs[E_TASK_SVR_UNSPECIFIED]	= "未指定OPC服务器，请首先指定OPC服务器!";
	m_TaskErrMsgs[E_TASK_DISCON_SVR_FIRST]	= "OPC服务器连接已存在，请先断开原有连接!";
	m_TaskErrMsgs[E_TASK_DUPLICATE_NAME]	= "指定组名已存在，请更换组名!";
	m_TaskErrMsgs[E_TASK_ERR_TASK]			= "任务参数配置错误，请重新配置!";
	m_TaskErrMsgs[E_TASK_NO_GROUP]			= "请至少添加一个组!";
	m_TaskErrMsgs[E_TASK_SREAD_NO_SOURCE]	= "未指定\"数据源\"参数";
	m_TaskErrMsgs[E_TASK_INVALID_ALL_SYM]	= "\"全部\"参数在此任务中无效";
	m_TaskErrMsgs[E_TASK_WRITE_INVALID_DATA]= "\"数据值\"参数有误!";
	m_TaskErrMsgs[E_FAIL]					= "未指定错误";
}


BOOL ErrorHelper::GetErrorMessage( HRESULT hr, CString& strErrMsg )
{
	_Init();

	ERR_MSG_MAP::iterator it = m_TaskErrMsgs.find( hr );
	if( it == m_TaskErrMsgs.end() )
		return FALSE;

	strErrMsg = it->second;
	return TRUE;
}