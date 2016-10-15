#pragma once

#include <WTypes.h>

interface IOpcAreaNode
{
public:
	virtual void	Release() = 0;

	virtual DWORD	GetId() const = 0;
	virtual LPCTSTR GetName() const = 0;

	virtual void AddChild( IOpcAreaNode* pChild, BOOL bAutoRelease ) = 0;
	virtual DWORD	GetChildCount() const = 0;
	virtual const IOpcAreaNode* GetChild( DWORD dwIndex ) const = 0;

	virtual void AddSource( const LPCTSTR& source ) = 0;
	virtual DWORD	GetSourceCount() const = 0;
	virtual LPCTSTR	GetSource( DWORD dwIndex ) const = 0;

	virtual void SetReserveData( DWORD dwData ) = 0;
	virtual DWORD GetReserveData() const = 0;
};