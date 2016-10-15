#pragma once

#include <WTypes.h>

#define OPC_AE_MIN_SEVERITY	1
#define OPC_AE_MAX_SEVERITY	1000

interface IOpcSimpleEvent
{
	virtual void Addref() = 0;
	virtual void Release() = 0;

	virtual void Clone( IOpcSimpleEvent** ppCloneEvent ) = 0;

	//Source
	virtual LPCTSTR	GetSource() const = 0;
	virtual LPCTSTR GetFullSource() const = 0;
	//Event Type
	virtual DWORD	GetEventType() const = 0;
	//Category
	virtual DWORD	GetCategoryId() const = 0;

	//Severity
	virtual void	SetSeverity( DWORD severity ) = 0;
	virtual DWORD	GetSeverity() const = 0;

	//Time
	virtual void	SetTime( FILETIME ftTime ) = 0;
	virtual FILETIME GetTime() const = 0;

	//Message
	virtual void	SetMessage( LPCTSTR pMessage ) = 0;
	//LPCTSTR GetMessage() const = 0;	处于并发安全考虑，注释此项

	//Area
	virtual void	GetAreaPath( DWORD& dwDepth, DWORD*& pdwAreaIds ) const = 0;
	virtual BOOL	HasArea() const = 0;
	virtual LPCTSTR GetAreaName() const = 0;

	//用户自定义项
	virtual void	SetAttribute( DWORD dwId, const VARIANT& vValue ) = 0;
	virtual BOOL	GetAttribute( DWORD dwId, VARIANT& vValue ) = 0;
	virtual void	ClearAttribute( DWORD dwId ) = 0;
	virtual void	ClearAttributes() = 0;

	//扩展项 - 便于客户端处理 
	virtual void	SetReserveData( DWORD dwData ) = 0;
	virtual DWORD	GetReserveData() const = 0;

	virtual void	ClearChangeMask() = 0;
	virtual void	Distill( ONEVENTSTRUCT& oneEvent ) = 0;
	virtual DWORD	GetCookie() const = 0;
};

interface IOpcTrackingEvent : public IOpcSimpleEvent
{
	virtual LPCTSTR GetActor() const = 0;
};

interface IOpcConditionEvent : public IOpcSimpleEvent
{
	//Condition
	virtual LPCTSTR GetCondition() const = 0;

	//Subcondition
	virtual void	SetSubCondition( LPCTSTR pszSubcondition ) = 0;
	virtual BOOL	IsSubCondition( LPCTSTR pszSubcondition ) = 0;

	//Quality
	virtual void	SetQuality(WORD quality) = 0;
	virtual WORD	GetQuality() const = 0;

	//Active - Inactive
	virtual void	SetActive( BOOL bActive = TRUE, const FILETIME* pftTime = NULL ) = 0;
	virtual BOOL	IsActive() const = 0;
	virtual FILETIME GetLastActiveTime() const = 0;
	virtual FILETIME GetLastInactiveTime() const = 0;

	//Enable
	virtual void	SetEnable( BOOL bEnable ) = 0;
	virtual BOOL	IsEnable() const = 0;

	//State
	virtual WORD	GetState() const = 0;

	//Ack
	virtual void		SetAckRequired( BOOL bReqAck ) = 0;
	virtual BOOL		IsAckRequired() const = 0; 
	virtual HRESULT		SetAck( LPCTSTR pszActor, LPCTSTR pszComment, const FILETIME* pAckTime ) = 0;
	virtual BOOL		IsAcked() const = 0;
	virtual FILETIME	GetLastAckTime() const = 0;
	virtual LPCTSTR		GetAckActor() const = 0;
	virtual LPCTSTR		GetAckComment() const = 0;
	virtual void		CancelAck() = 0;

	virtual HRESULT GetConditionState( DWORD dwNumEventAttrs, DWORD* pdwAttributeIDs, OPCCONDITIONSTATE** ppConditionState ) = 0;
};