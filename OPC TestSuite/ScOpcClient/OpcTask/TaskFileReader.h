// TaskFileReader.h: interface for the TaskFileReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKFILEREADER_H__454B1C8F_1E92_4D41_85D0_42ECD1BBB3EE__INCLUDED_)
#define AFX_TASKFILEREADER_H__454B1C8F_1E92_4D41_85D0_42ECD1BBB3EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct TaskRunConfig
{
	DWORD	DelayMSEL;		//延迟时间
	DWORD	Interval;		//运行间隔
	DWORD	RunTimes;		//运行次数
	BOOL	AsyncRun;		//独立运行
	
	TaskRunConfig() : DelayMSEL(0), Interval(0), RunTimes(1), AsyncRun(FALSE)
	{
	}
};

struct OneTaskParam
{
	CString ParamName;
	vector<CString> ParamValues;
};

class TaskFileReader  
{
public:
	TaskFileReader( CArchive* pArchive );
	virtual ~TaskFileReader();

	BOOL ReadTaskName( CString& strName );
	void ReadRunConfig( TaskRunConfig& taskRunCfg );
	BOOL ReadParamLine( OneTaskParam& oneTaskParam );
private:
	BOOL _ReadValidString( CString& strValidString );
	BOOL _IsTaskName( const CString& strTaskName );
	BOOL _IsTaskParam( const CString& strTaskParam );
	BOOL _FillOneTaskParam( const CString& strParam, OneTaskParam& oneTaskParam );
	void _SplitTrimedString( const CString& strSource, CString cSeparator, vector<CString>& strList );
	BOOL _IsComments( const CString& strReadLine );
private:
	CArchive*	m_pArchive;

	CString		m_strTaskName;
	OneTaskParam*	m_pBufOneParam;
};

#endif // !defined(AFX_TASKFILEREADER_H__454B1C8F_1E92_4D41_85D0_42ECD1BBB3EE__INCLUDED_)
