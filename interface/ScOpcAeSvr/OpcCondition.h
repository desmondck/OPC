// OpcConditions.h: interface for the OpcConditions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPCCONDITIONS_H__21AF38AC_D6C5_4056_8299_EA4F7E8716D8__INCLUDED_)
#define AFX_OPCCONDITIONS_H__21AF38AC_D6C5_4056_8299_EA4F7E8716D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*	2.4.3 Attributes of OPCSubConditions 
	Name: 
		The name assigned to the sub-condition, e.g. ¡°HighAlarm¡± for a sub-condition of ¡°LevelAlarm¡±. 
		In the case of a single-state alarm,the sub-condition name is the same as the associated condition name. 
		The name of the sub-condition must be unique within its associated condition.
	Definition: 
		An expression which defines the sub-state represented bythe sub-condition (see Condition Definitions below).
	Severity: 
		The severity of any event notifications generated on behalf of this sub-condition (see Severity below). 
		Note that different sub-conditions of the same condition may have different severity levels. 
	Description:
		The text string to be included in any event notification generated on behalf of this sub-condition. */
class SC_OPC_AE_CLASS OpcSubcondition
{
public:
	OpcSubcondition();
	OpcSubcondition( const char* pName, const char* pMessage, const char* pDefinition, DWORD dwSeverity );
	~OpcSubcondition();

	OpcSubcondition( const OpcSubcondition& subcondition );
	OpcSubcondition& operator = ( const OpcSubcondition& subcondition );

	void SetName( LPCTSTR pName );
	void SetDefinition( LPCTSTR pDefinition );
	void SetMessage( LPCTSTR pMessage );
	void SetSeverity( DWORD dwSeverity );
	
	LPCTSTR GetName() const;
	LPCTSTR GetDefinition() const;
	LPCTSTR GetMessage() const;
	DWORD GetSeverity() const ;

	void	SetReserveData( DWORD dwData );
	DWORD	GetReserveData() const;
private:
	void* m_pData;
};

class SC_OPC_AE_CLASS OpcCondition
{
public:
	OpcCondition();
	~OpcCondition();

	OpcCondition( const OpcCondition& condition );
	OpcCondition& operator = ( const OpcCondition& subcondition );

	//Name: The name of a condition must be unique within the event server. 
	void SetName( LPCTSTR pName );
	LPCTSTR GetName() const;

	void	AddSubcondition( const OpcSubcondition& pSubcondition );
	DWORD	GetSubconditionCount() const;
	BOOL	GetSubcondition( DWORD dwIndex, OpcSubcondition& pSubcondition ) const;

	void	SetReserveData( DWORD dwData );
	DWORD	GetReserveData() const;
private:
	void*	m_pData;
};

#endif // !defined(AFX_OPCCONDITIONS_H__21AF38AC_D6C5_4056_8299_EA4F7E8716D8__INCLUDED_)
