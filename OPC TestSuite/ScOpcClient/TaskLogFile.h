// TaskLogFile.h: interface for the TaskLogFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKLOGFILE_H__A323A9FB_BE49_4631_A732_186B171E8A27__INCLUDED_)
#define AFX_TASKLOGFILE_H__A323A9FB_BE49_4631_A732_186B171E8A27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TaskLogFile  
{
public:
	static void BeginTrace( const CString& strTaskName, const CString& strMsg );
	static void EndTrace( const CString& strTaskName,  const CString& strMsg );
	static void TraceSpan( const CString& strTaskName,  DWORD dwMilliSeconds );
	static void TraceError( const CString& strErrMsg );

private:
	TaskLogFile();
	virtual ~TaskLogFile();
	static void _TraceTask( const CString& strTaskName, const CString& strStep, const CString& strMsg );
};

#endif // !defined(AFX_TASKLOGFILE_H__A323A9FB_BE49_4631_A732_186B171E8A27__INCLUDED_)
