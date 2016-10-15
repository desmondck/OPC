#ifndef _SC_OPC_DA_I_OPC_NODE_H_CK_2014_03_10
#define _SC_OPC_DA_I_OPC_NODE_H_CK_2014_03_10

#ifndef interface
	#define interface struct
#endif

#include "IOpcItemProperty.h"

interface IOpcNode;
interface IOpcNodeList
{
	virtual void Release() = 0;

	//数量
	virtual DWORD	GetCount() const = 0;			
	//指定项
	virtual const IOpcNode*	Get( DWORD dwIndex ) const = 0;

	virtual const IOpcNode* Find( LPCTSTR strName ) const = 0;
};

//Browser中的节点对象
interface IOpcNode
{
	virtual void Release() = 0;
	//名称
	virtual const char* GetName() const = 0;				
	//数据类型
	virtual VARTYPE		GetDataType() const = 0;			
	//读写权限
	virtual DWORD		GetAccessRight() const = 0;

	//节点对应的Item Property
	virtual const IOpcItemPropList* GetItemProperties() const = 0;

	//子节点
	virtual const IOpcNodeList*	GetChildNodes() const = 0;
};

//该类提供了富节点的Set方法，主要用于解决如下问题：
//	1. 使用内置OpcNode类的问题，Factory中提供了Create方法可以构造Richer对象，客户端可调用该方法使用内置类
//	2. 延迟绑定问题：提供了Set方法后，IOpcItemProperty和IOpcNode接口对象无需在创建时强制绑定到对象上，同时解决了层级构建问题（不解释）
//	3. 组态修改问题：一旦涉及组态修改时，如子节点、属性变化时，可以灵活设置
interface IOpcNodeRicher : IOpcNode
{
	virtual void SetItemProperty( IOpcItemProperty* pProperty, BOOL bAutoRelease ) = 0;
	virtual void SetItemProperties( IOpcItemPropList* pItemProps, BOOL bAutoRelease ) = 0;

	virtual void SetChildNode( IOpcNode* pNode, BOOL bAutoRelease ) = 0;
	virtual void SetChildNodes( IOpcNodeList* pChildNodes, BOOL bAutoRelease ) = 0;
};

#endif	//_SC_OPC_DA_I_OPC_NODE_H_CK_2014_03_10