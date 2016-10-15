// TaskLogFile.cpp: implementation of the TaskLogFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scopcclient.h"
#include "TaskLogFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define TASK_TRACE_SYMBOL		"[ScOpcClient]"
#define TASK_TRACE_ERR_SYMBOL	"[ScOpcClient]::Error"
#define TASK_TRACE_BEGIN		"开始执行"
#define TASK_TRACE_FINISH		"执行结束"
#define TASK_TRACE_SPAN			"运行时间"

TaskLogFile::TaskLogFile()
{

}

TaskLogFile::~TaskLogFile()
{

}

void TaskLogFile::BeginTrace( const CString& strTaskName, const CString& strMsg )
{
	_TraceTask( strTaskName, TASK_TRACE_BEGIN, strMsg );
}

void TaskLogFile::EndTrace( const CString& strTaskName, const CString& strMsg )
{
	_TraceTask( strTaskName, TASK_TRACE_FINISH, strMsg );	
}

void TaskLogFile::TraceSpan( const CString& strTaskName, DWORD dwSpanTicks )
{
	CString strSpanTicks;
	strSpanTicks.Format( "%d(ms)", dwSpanTicks );

	_TraceTask( strTaskName, TASK_TRACE_SPAN, strSpanTicks );	
}

void TaskLogFile::_TraceTask( const CString& strTaskName, const CString& strStep,  const CString& strMsg )
{
// 	SYSTEMTIME stNow;
// 	GetSystemTime( &stNow );
// 	CString strTime;
// 	strTime.Format( "%d-%d-%d-%d:%d:%d:%d", 
// 		stNow.wYear, stNow.wMonth, stNow.wDay, stNow.wHour, stNow.wMinute, stNow.wSecond, stNow.wMilliseconds );
	
	CString strTraceMsg;
	strTraceMsg.Format( "%s\t%s\t%s\t%s\n", TASK_TRACE_SYMBOL, strTaskName, strStep, strMsg );
	OutputDebugString( strTraceMsg );	
}

void TaskLogFile::TraceError( const CString& strErrMsg )
{
	CString strTraceMsg;
	strTraceMsg.Format( "%s %s", TASK_TRACE_ERR_SYMBOL, strErrMsg );
	OutputDebugString( strTraceMsg );
}

