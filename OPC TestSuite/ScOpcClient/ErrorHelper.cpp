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
	
	m_TaskErrMsgs[E_TASK_NO_FOUND]			= "ָ�����񲻴���";
	m_TaskErrMsgs[E_TASK_INVALID_PARAM]		= "������Ч����";
	m_TaskErrMsgs[E_TASK_CONN_FAILED]		= "���ӷ�����ʧ��!";
	m_TaskErrMsgs[E_TASK_HAS_CONNECTED]		= "�����ѽ��������������ͬһ�����������������!";
	m_TaskErrMsgs[E_TASK_SVR_UNSPECIFIED]	= "δָ��OPC��������������ָ��OPC������!";
	m_TaskErrMsgs[E_TASK_DISCON_SVR_FIRST]	= "OPC�����������Ѵ��ڣ����ȶϿ�ԭ������!";
	m_TaskErrMsgs[E_TASK_DUPLICATE_NAME]	= "ָ�������Ѵ��ڣ����������!";
	m_TaskErrMsgs[E_TASK_ERR_TASK]			= "����������ô�������������!";
	m_TaskErrMsgs[E_TASK_NO_GROUP]			= "���������һ����!";
	m_TaskErrMsgs[E_TASK_SREAD_NO_SOURCE]	= "δָ��\"����Դ\"����";
	m_TaskErrMsgs[E_TASK_INVALID_ALL_SYM]	= "\"ȫ��\"�����ڴ���������Ч";
	m_TaskErrMsgs[E_TASK_WRITE_INVALID_DATA]= "\"����ֵ\"��������!";
	m_TaskErrMsgs[E_FAIL]					= "δָ������";
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