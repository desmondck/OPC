#pragma once

#include "IOpcEvent.h"
#include "IOpcAreaNode.h"

#ifdef _ScOpcAeSvr_Imp_
#define OPC_AE_API extern "C" __declspec(dllexport)
#else
#define OPC_AE_API extern "C" __declspec(dllimport)
#endif

OPC_AE_API IOpcSimpleEvent* CreateSimpleEvent( LPCTSTR strSource, DWORD dwCategory, DWORD dwSeverity, 
	DWORD dwAreaDepth, DWORD* pdwAreaIds );

OPC_AE_API IOpcTrackingEvent* CreateTrackingEvent( LPCTSTR strSource, DWORD dwCategory, DWORD dwSeverity, 
	DWORD dwAreaDepth, DWORD* pdwAreaIds, LPCTSTR pszActorId );

OPC_AE_API IOpcConditionEvent* CreateConditionEvent( LPCTSTR strSource, DWORD dwCategory, DWORD dwSeverity, 
	DWORD dwAreaDepth, DWORD* pdwAreaIds, 
	LPCTSTR strCondName, LPCTSTR strSubCondName );

OPC_AE_API IOpcAreaNode* CreateOpcAreaNode( DWORD dwId, LPCTSTR name );