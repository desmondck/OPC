// TaskFileReader.cpp: implementation of the TaskFileReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskFileReader.h"
#include "TaskFileMacroDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

TaskFileReader::TaskFileReader( CArchive* pArchive ) : m_pArchive(pArchive), m_pBufOneParam(NULL)
{
}

TaskFileReader::~TaskFileReader()
{
	m_pArchive = NULL;
	m_strTaskName.Empty();
}

BOOL TaskFileReader::ReadTaskName( CString& strName )
{
	if( !m_strTaskName.IsEmpty() )
	{
		strName = m_strTaskName;
		m_strTaskName.Empty();

		return TRUE;
	}

	//已无有效参数行，直接返回
	CString strParam;
	if( !_ReadValidString(strParam) || !_IsTaskName(strParam) )
		return FALSE;

	strName = strParam;
	return TRUE;
}

void TaskFileReader::ReadRunConfig( TaskRunConfig& taskRunCfg )
{
	//不存在有效的参数行，即采用默认配置
	OneTaskParam oneParam;
	if( !ReadParamLine( oneParam ) )
		return;	
	
	//非RUN_CFG_SYMBOL参数行，采用默认配置
	if( oneParam.ParamName.Compare(RUN_CFG_SYMBOL) != 0 )
	{
		m_pBufOneParam = new OneTaskParam();
		m_pBufOneParam->ParamName	= oneParam.ParamName;
		m_pBufOneParam->ParamValues	= oneParam.ParamValues;

		return;
	}

	//合法有效的RUN_CFG_SYMBOL参数字段，填充并返回
	if( oneParam.ParamValues.size() == 4 )
	{
		taskRunCfg.DelayMSEL	= atoi(oneParam.ParamValues[0]);	//延迟时间
		taskRunCfg.RunTimes		= atoi(oneParam.ParamValues[1]);	//运行次数
		taskRunCfg.Interval		= atoi(oneParam.ParamValues[2]);	//运行间隔
		taskRunCfg.AsyncRun		= atoi(oneParam.ParamValues[3]);	//并发运行
	}
}

BOOL TaskFileReader::ReadParamLine( OneTaskParam& oneTaskParam )
{
	oneTaskParam.ParamName.Empty();
	oneTaskParam.ParamValues.clear();
	//存在缓存行
	if( m_pBufOneParam )
	{
		oneTaskParam = *m_pBufOneParam;
		delete m_pBufOneParam;
		m_pBufOneParam = NULL;

		return TRUE;
	}

	//已到新任务的起点，需首先读取新任务
	if( !m_strTaskName.IsEmpty() )
		return FALSE;	

	//已无有效参数行，直接返回
	CString strParam;
	if( !_ReadValidString(strParam) )
		return FALSE;

	//有效参数行
	if( _IsTaskParam( strParam ) )
		return _FillOneTaskParam( strParam, oneTaskParam );

	//新任务
	if( _IsTaskName( strParam ) )	
		m_strTaskName = strParam;
	return FALSE;
}

BOOL TaskFileReader::_ReadValidString( CString& strValidString )
{
	BOOL bInComments = FALSE;
	while( TRUE )
	{
		if( !m_pArchive->ReadString( strValidString ) )
			return FALSE;	//文件读取结束

		if( bInComments )	//注释内容
		{
			if( strValidString.Find( COMMENTS_SYMBOL_RIGHT ) >= 0 )
				bInComments = FALSE;	//注释已结束

			continue;
		}


		strValidString.TrimRight();
		if( strValidString.IsEmpty() )
			continue;		//空行

		if( strValidString.Find( COMMENTS_SYMBOL ) >= 0 )
			continue;		//注释行

		if( strValidString.Find( COMMENTS_SYMBOL_LEFT ) >= 0 )
		{
			if( strValidString.Find( COMMENTS_SYMBOL_RIGHT ) < 0 )
				bInComments = TRUE;
			continue;
		}

		return TRUE;	//存在有效行数据，返回
	}
}

BOOL TaskFileReader::_IsTaskName( const CString& strTaskName )
{
	return strTaskName.Find( TASK_PARAM_SYMBOL ) < 0;
}

BOOL TaskFileReader::_IsTaskParam( const CString& strTaskParam )
{
	return strTaskParam.Find( TASK_PARAM_SYMBOL ) == 0;
}

BOOL TaskFileReader::_FillOneTaskParam( const CString& strParam, OneTaskParam& oneTaskParam )
{
	vector<CString> strList;
	_SplitTrimedString( strParam, NAME_SEPARATOR, strList );

	switch( strList.size() )
	{
	case 1:
		_SplitTrimedString( strParam, INSIDE_SEPARATOR, oneTaskParam.ParamValues );
		return TRUE;
	case 2:
		oneTaskParam.ParamName = strList[0];
		_SplitTrimedString( strList[1], INSIDE_SEPARATOR, oneTaskParam.ParamValues );
		return TRUE;		
	}

	return FALSE;
}

void TaskFileReader::_SplitTrimedString( const CString& strSource, CString cSeparator, vector<CString>& strList )
{
	strList.clear();
	if( strSource.IsEmpty() )
		return;
	
	CString strRemain = strSource;
	while( TRUE )
	{
		int index = strRemain.Find( cSeparator );
		if( index == -1 )
		{
			strRemain.TrimLeft();
			strRemain.TrimRight();
			strList.push_back( strRemain );
			return;
		}
		
		if( index != 0 )
		{
			CString strLeft = strRemain.Left( index );
			strLeft.TrimLeft();
			strLeft.TrimRight();

			if( !strLeft.IsEmpty() )
				strList.push_back( strLeft );
		}
		
		strRemain = strRemain.Mid( index + cSeparator.GetLength() );
	}
}
