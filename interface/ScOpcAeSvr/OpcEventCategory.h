// OpcEventCategorys.h: interface for the OpcEventCategorys class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPCEVENTCATEGORYS_H__05C75820_EDD9_4384_BF02_587AE5D0062B__INCLUDED_)
#define AFX_OPCEVENTCATEGORYS_H__05C75820_EDD9_4384_BF02_587AE5D0062B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SC_OPC_AE_CLASS OpcEventAttribute
{
public:
	OpcEventAttribute();
	OpcEventAttribute( DWORD dwId, VARTYPE vt, LPCTSTR desc );
	~OpcEventAttribute();

	OpcEventAttribute( const OpcEventAttribute& attribute );
	OpcEventAttribute& operator = ( const OpcEventAttribute& right );

	DWORD	GetId() const;
	LPCTSTR GetDescription() const;
	VARTYPE GetDataType() const;
private:
	void* m_pData;
};

/*2.5.3 Event Categories define groupings of events supported by an OPCEventserver. 
	Examples of event categories might include “Process Events”, “System Events”, or “Batch Events”. 
	Event categories maybe defined for all event types, i.e. Simple, Tracking, and Condition-Related. 
	However, a particular event category can include events of only one type. 
	A given Source (e.g. “System”or “FIC101”) may generate events for multiple event categories. 
	Names of event categories must be unique with in the event server. 
	The definition of event categories is server specific and is outside the scope of this specification. 
	A list of recommended event categories for each event type is provided in Appendix B.
	The name of the event category is included in every event notification. 
	Event subscriptions maybe filtered based on event category. */

#define INVALID_CATEGORY_ID 0xFFFFFFFF

class SC_OPC_AE_CLASS OpcEventCategory
{
public:
	OpcEventCategory();
	OpcEventCategory( DWORD dwId, DWORD dwEventType, LPCTSTR pDesc );
	~OpcEventCategory();

	OpcEventCategory( const OpcEventCategory& category );
	OpcEventCategory& operator = ( const OpcEventCategory& right );
	
	DWORD GetId() const;
	DWORD GetEventType() const;
	LPCTSTR GetDescription() const;

	//仅当dwEventType为OPC_CONDITION_EVENT，Condition相关字段有效
	void	AddCondition( const OpcCondition& pCondition );	//将全部指针改为引用，控制生命周期
	DWORD	GetConditionCount() const;
	BOOL	GetCondition( DWORD dwIndex, OpcCondition& pCondition ) const;

	void	AddAttribute( const OpcEventAttribute& pAttr );
	DWORD	GetAttributeCount() const;
	BOOL	GetAttribute( DWORD dwIndex, OpcEventAttribute& pAttr ) const;
private:
	void*	m_pData;
};

#endif // !defined(AFX_OPCEVENTCATEGORYS_H__05C75820_EDD9_4384_BF02_587AE5D0062B__INCLUDED_)
