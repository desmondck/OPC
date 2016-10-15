//	Author: Wang, Chunjie
//	Date:	2015-3
//	Desc:	���󹤳�

#if !defined(AFX_SCOPCDAOBJECTFACTORY_H__INCLUDED_)
#define AFX_SCOPCDAOBJECTFACTORY_H__INCLUDED_

#include "wtypes.h"

#include "IOpcNode.h"
#include "IOpcItemProperty.h"

#ifndef _SC_OPC_DA_SVR_IMP_
	#define SC_OPC_DA_EXT_CLASS __declspec(dllimport)
	#define SC_OPC_DA_API extern "C" __declspec(dllimport)
#else
	#define SC_OPC_DA_EXT_CLASS __declspec(dllexport)
	#define SC_OPC_DA_API extern "C" __declspec(dllexport)
#endif

//��ͨ�����½ӿڡ������ഴ������ʵ�ֵ�IOpcItemProperty��IOpcItemPropList�ӿڶ���
//ע�⣺Ҳ�����սӿ�Լ������ʵ��IOpcItemProperty��IOpcItemPropList�ӿ�
SC_OPC_DA_API IOpcItemProperty* CreateItemProperty( DWORD dwId, const char* pDesc, VARTYPE vt, 
													const char* pItemId, const VARIANT* pValue );

class SC_OPC_DA_EXT_CLASS OpcItemPropListBuilder
{
public:
	OpcItemPropListBuilder();
	~OpcItemPropListBuilder();

	void	Add( IOpcItemProperty* pProp, BOOL bAutoRelease );
	IOpcItemPropList* Detach();

private:
	void* m_pData;
};

//��ͨ�����½ӿڡ������ഴ������ʵ�ֵ�IOpcNode��IOpcNodeList�ӿڶ���
//ע�⣺Ҳ�����սӿ�Լ������ʵ��IOpcNode��IOpcNodeList�ӿ�
SC_OPC_DA_API IOpcNode* CreateOpcNode( const char* pName, VARTYPE vt, DWORD dwAccessRight );
SC_OPC_DA_API IOpcNodeRicher* CreateOpcNodeRicher( const char* pName, VARTYPE vt, DWORD dwAccessRight );

class SC_OPC_DA_EXT_CLASS OpcNodeListBuilder
{
public:
	OpcNodeListBuilder();
	~OpcNodeListBuilder();

	void	Add( IOpcNode* pChildNode, BOOL bAutoRelease );
	IOpcNodeList* Detach();

private:
	void* m_pData;
};

#endif // !defined(AFX_SCOPCDAOBJECTFACTORY_H__INCLUDED_)
