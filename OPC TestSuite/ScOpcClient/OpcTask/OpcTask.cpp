// OpcTask.cpp: implementation of the OpcTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpcTask.h"

#include <process.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

unsigned int WINAPI Task_ThreadProc( void* pParam )
{
	CoInitializeEx( NULL, COINIT_MULTITHREADED );
	OpcTask* pTask = (OpcTask*)pParam;
	HRESULT hr = pTask->DoIndependRunProc();
	CoUninitialize();

	return -1;
}

DWORD OpcTask::m_TaskIdGenerator = 0;

OpcTask::OpcTask( Opc_Task_Type type, const CString& taskName )
: m_Type(type), m_TaskName(taskName), m_hThread(NULL), m_hStopEvent(NULL)
{
	m_TaskId = ++m_TaskIdGenerator;

	m_hStopEvent	= CreateEvent( NULL, TRUE, FALSE, NULL );	//标记Stop请求(挂起表明请求Stop)
	m_hFinishEvent	= CreateEvent( NULL, TRUE, TRUE, NULL );	//标记任务状态(挂起表明已完成)
}

OpcTask::~OpcTask()
{
	CloseHandle( m_hStopEvent );
	CloseHandle( m_hFinishEvent );
}

HRESULT OpcTask::Unserialize( TaskFileReader& taskFileReader )
{
	taskFileReader.ReadRunConfig( m_TaskRunCfg );

	return DoUnserialize( taskFileReader );
}

HRESULT OpcTask::Run()
{
	ResetEvent( m_hFinishEvent );

	//延迟规定时间
	if( WaitForSingleObject( m_hStopEvent, m_TaskRunCfg.DelayMSEL ) != WAIT_TIMEOUT )
	{
		SetEvent( m_hFinishEvent );
		return S_OK;
	}

	if( m_TaskRunCfg.AsyncRun )	//独立运行
	{
		m_hThread = (HANDLE)_beginthreadex( NULL, 0, Task_ThreadProc, this, 0, NULL );
		return S_OK;
	}
	
	HRESULT hr = S_OK;
	for( int i = 0; i < m_TaskRunCfg.RunTimes; ++i )
	{
		hr = DoRun();
		if( FAILED(hr) )
			break;

		if( WaitForSingleObject( m_hStopEvent, m_TaskRunCfg.Interval ) != WAIT_TIMEOUT )
			break;
	}

	SetEvent( m_hFinishEvent );
	return hr;
}

HRESULT OpcTask::DoIndependRunProc()
{
	HRESULT hr = S_OK;
	DWORD dwTimes = 0;
	while( WaitForSingleObject( m_hStopEvent, m_TaskRunCfg.Interval ) == WAIT_TIMEOUT )
	{
		hr = DoRun();
		if( FAILED(hr) )
			break;

		if( ++dwTimes >= m_TaskRunCfg.RunTimes )
			break;
	}

	SetEvent( m_hFinishEvent );
	return hr;
}

void OpcTask::Stop()
{
	SetEvent( m_hStopEvent );
	WaitForSingleObject( m_hFinishEvent, INFINITE );
	CloseHandle( m_hThread );
	m_hThread = NULL;
	ResetEvent( m_hStopEvent );
}

BOOL OpcTask::InRunning()
{
	return WaitForSingleObject( m_hFinishEvent, 0 ) == WAIT_TIMEOUT;
}

HRESULT OpcTask::_UnserializeGroupItems( TaskFileReader& taskFileReader, GROUP_ITEMS_MAP& groupItems )
{
	OneTaskParam oneParam;
	while( taskFileReader.ReadParamLine( oneParam ) )
	{
		//组名
		if( oneParam.ParamName.Compare(SYMBOL_GROUP_NAME) != 0 || oneParam.ParamValues.size() != 1 )
			return E_TASK_INVALID_PARAM;
		CString strGroupName = oneParam.ParamValues[0];
		
		//位号列表
		taskFileReader.ReadParamLine( oneParam );
		if( oneParam.ParamName.Compare(SYMBOL_ITEM_NAME) != 0 || oneParam.ParamValues.size() == 0 )
			return E_TASK_INVALID_PARAM;
		
		groupItems[strGroupName] = oneParam.ParamValues;
	}
	
	return S_OK;	
}

HRESULT OpcTask::_UnserializeVariants( TaskFileReader& taskFileReader, vector<VARIANT>& vDataValues )
{
	OneTaskParam oneParam;
	if( !taskFileReader.ReadParamLine(oneParam) 
		|| oneParam.ParamName.Compare( SYMBOL_DATA_VALUE ) != 0 
		|| oneParam.ParamValues.size() == 0 )
		return E_TASK_WRITE_INVALID_DATA;
	
	for( int i = 0; i < oneParam.ParamValues.size(); ++i )
	{
		VARIANT vValue;
		if( !_GetDataValueInfo( oneParam.ParamValues[i], vValue ) )
			return E_TASK_WRITE_INVALID_DATA;
		
		vDataValues.push_back( vValue );
	}
	
	return S_OK;
}

BOOL OpcTask::_GetDataValueInfo( const CString& strDataInfo, VARIANT& vValue )
{
	VARTYPE vtDataType;
	CString strValue;
	
	int index = strDataInfo.ReverseFind( SUB_SEP_LEFT );
	if( index < 0 )
	{
		vtDataType = VT_R4;
		strValue = strDataInfo;
	}
	else
	{
		CString strVT = strDataInfo.Mid( index + 1 );
		strVT.Remove( SUB_SEP_RIGHT );
		if( !VariantHelper::VarTypeFromString( strVT, vtDataType ) )
			return FALSE;
		
		strValue= strDataInfo.Left( index );		
	}
	
	return VariantHelper::VariantFromString( vtDataType, strValue, vValue );
}