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

	//����
	virtual DWORD	GetCount() const = 0;			
	//ָ����
	virtual const IOpcNode*	Get( DWORD dwIndex ) const = 0;

	virtual const IOpcNode* Find( LPCTSTR strName ) const = 0;
};

//Browser�еĽڵ����
interface IOpcNode
{
	virtual void Release() = 0;
	//����
	virtual const char* GetName() const = 0;				
	//��������
	virtual VARTYPE		GetDataType() const = 0;			
	//��дȨ��
	virtual DWORD		GetAccessRight() const = 0;

	//�ڵ��Ӧ��Item Property
	virtual const IOpcItemPropList* GetItemProperties() const = 0;

	//�ӽڵ�
	virtual const IOpcNodeList*	GetChildNodes() const = 0;
};

//�����ṩ�˸��ڵ��Set��������Ҫ���ڽ���������⣺
//	1. ʹ������OpcNode������⣬Factory���ṩ��Create�������Թ���Richer���󣬿ͻ��˿ɵ��ø÷���ʹ��������
//	2. �ӳٰ����⣺�ṩ��Set������IOpcItemProperty��IOpcNode�ӿڶ��������ڴ���ʱǿ�ư󶨵������ϣ�ͬʱ����˲㼶�������⣨�����ͣ�
//	3. ��̬�޸����⣺һ���漰��̬�޸�ʱ�����ӽڵ㡢���Ա仯ʱ�������������
interface IOpcNodeRicher : IOpcNode
{
	virtual void SetItemProperty( IOpcItemProperty* pProperty, BOOL bAutoRelease ) = 0;
	virtual void SetItemProperties( IOpcItemPropList* pItemProps, BOOL bAutoRelease ) = 0;

	virtual void SetChildNode( IOpcNode* pNode, BOOL bAutoRelease ) = 0;
	virtual void SetChildNodes( IOpcNodeList* pChildNodes, BOOL bAutoRelease ) = 0;
};

#endif	//_SC_OPC_DA_I_OPC_NODE_H_CK_2014_03_10