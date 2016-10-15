//	Author: Wang, Chunjie
//	Date:	2013-10
//	Desc:	OPC DA������SDK����SDKʵ�������ġ�OPC DA 2.05A��Э��

#if !defined(AFX_SCOPCDASVR_H__8BE028C2_0593_4DD8_AEF2_EE9C215F0592__INCLUDED_)
#define AFX_SCOPCDASVR_H__8BE028C2_0593_4DD8_AEF2_EE9C215F0592__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wtypes.h"
#include "OPCProps.h"
#include "OPCDA_3.00.h"
#include "OPCError_3.00.h"

#include "ScOpcDaObjectFactory.h"

//�����������ӵ�OPC DA�������ϵĿͻ���������Ϣ
interface IOpcDaCltInfo
{
	//�ͻ��˱�ʶ���ڿͻ�������Ϊָ�������Ψһ��ʶ��ǰ�ͻ�������
	virtual DWORD	GetId() = 0;

	//�ͻ�������
	virtual LPCTSTR GetName() = 0;

	//Group����
	virtual DWORD	GetGroupCount() = 0;

	//ָ��Group������
	virtual LPCTSTR	GetGroupName( DWORD dwGroupIndex ) = 0;

	//ָ��Group�϶��ĵ�λ������
	virtual DWORD	GetItemCount( DWORD dwGroupIndex ) = 0;
};

interface IOpcDaCltInfoList
{
	virtual void Release() = 0;

	virtual DWORD GetClientCount() = 0;
	virtual IOpcDaCltInfo* GetClient( DWORD dwClientIndex ) = 0;
};



//Item ID������λ�Ŷ���
//�������¼��㿼�ǣ��˴����õ����࣬���ǵ����ӿ�
//	1. ԭ�п�����Ϊ�����࣬���ֵ�����ɽ���Ǩ�Ƴɱ���
//	2. �����ӿ�����������ʵ�ַ�ʽ��
//		a. ÿ��OPC�������Լ�ʵ��CTag�ࣺ
//			CTagʵ���ڲ�ͬ��OPC�������ϲ��޲��죬Ϊ�ɸ��ô��룬����ʵ�ֵ��´������࣬���ӳɱ�����CTagΪ�������ʶ���
//		b. ��SDKʵ��CTag����ͨ��CreateTag��������
//			ɥʧ�˼̳�CTag������
class SC_OPC_DA_EXT_CLASS CTag
{
public:
	CTag();
	virtual	~CTag();
	
	void	SetVQT( const VARIANT* pValue, const WORD* pwQuality, const FILETIME* pFileTIme );
	HRESULT GetVQT( VARIANT* pValue, WORD* pwQuality, FILETIME* pFileTIme, VARTYPE vtRequest = VT_EMPTY );

	void SetValueLimits( double dbLowLimit, double dbHighLimit );
	BOOL GetValueLimits( double& dbLowLimit, double& dbHighLimit );
	
	void SetAccessRights( DWORD accessRights );
	DWORD GetAccessRights();
	
	void	SetDataType( VARTYPE vtDataType );
	VARTYPE	GetDataType();
	
	//����������OPC SDK�����ⲿ�������AddRef/Release���˴�Ϊ���������еĽ��
	LONG AddRef();
	LONG Release();
	LONG RefCount();
private:
	void*	m_pData;
};

interface IOPCDACallback  
{
	// ��  ��:	���ط������Ļ�����Ϣ���μ���OPC DA 2.05A����GetStatus
	// ��  ��:
	//			@state			����������״̬��OPC_STATUS_RUNNING��ʾ��������
	//			@dwBandWidth	�����ʣ�-1��ʾδ֪
	//			@wMajor			���汾��
	//			@wMinor			�Ӱ汾��
	//			@wBuildNum		������
	//			@pVendor		��Ӧ������
	virtual void	GetStatus( OPCSERVERSTATE& state, DWORD& dwBandWidth, WORD& wMajor, WORD& wMinor, WORD& wBuildNum, char*& pVendor ) = 0;
	
	//Browser
	// ��  ��:	�μ���OPC DA 2.05A����QueryOrganization
	virtual HRESULT QueryOrganization( OPCNAMESPACETYPE& nameSpaceType ) = 0;
	
	// ��  ��:	��ȡ��ǰBrowser�İ汾�ţ���GetBrowser���ʹ��
	//			��GetBrowser�з��ص�Browser�ڷ����仯ʱ������Browser Version�����˴α仯
	//			ScOpcDaSvr���ְ汾��֮ǰ�İ汾�Ų�һ�������µ���GetBrowser
	// ����ֵ:	
	//			��ǰBrowser�İ汾��
	virtual DWORD	GetBrowserVersion() = 0;
	
	// ��  ��:	��ȡOPC��������Browser����
	// ����ֵ:
	//			��ǰBrowser�����Root
	//			OPC_NS_FLAT:		Root��Ϊƽ̹�ṹ
	//			OPC_NS_HIERARCHIAL:	Root��Ϊ��״�ṹ
	virtual const IOpcNode* GetBrowser( TCHAR& cSeparator ) = 0;
	
	// ��  ��:	����������Update Rate
	//			ÿ���ͻ���ִ��AddGroupʱ�����ô˽ӿ�����Update Rate
	//			�μ���OPC DA 2.05A����AddGroup��Request\Revise Rate
	// ��  ��:
	//			@dwRequestRate	�ͻ�������ĸ�������
	// ����ֵ:
	//			������ĸ���Ƶ��
	virtual DWORD	GetUpdateRate( DWORD dwRequestRate ) = 0;
	
	//Tags
	// ��  ��:	λ�Ŷ��ģ��μ���OPC DA 2.05A����AddItems
	// ��  ��:
	//			@dwCount		λ������
	//			@pItemIDs		λ�ŵ�Item ID���飬Item ID��Browser��λ�Žṹ����
	//			@pAccessPaths	�μ�Э�飬��������¿ɺ��Ըò���
	//			[out]@ppTags	���������ÿ��Item ID���Ķ�Ӧ��CTag����
	//			[out]@pErrors	ÿ��Item ID�Ķ��������S_*����ɹ���E_*����ʧ��
	// ����ֵ:
	//			S_OK	ȫ���ɹ�
	//			S_FALSE	���ֳɹ�
	//			E_*		ȫ��ʧ��
	virtual HRESULT Subscribe( DWORD dwCount, const char** pItemIDs, const char** pAccessPaths, CTag** ppTags, HRESULT* pErrors ) = 0;
	
	// ��  ��:	λ�ŷ����ģ��μ���OPC DA 2.05A����RemoveItems
	// ��  ��:
	//			@dwCount	λ������
	//			@ppTags		λ�Ŷ����б�	
	// ����ֵ:
	//			S_OK	ȫ���ɹ�
	//			S_FALSE	���ֳɹ�
	//			E_*		ȫ��ʧ��	
	virtual HRESULT Unsubscribe( DWORD dwCount, CTag** ppTags ) = 0;

	//��δʹ��
	virtual HRESULT ReadTags( DWORD dwCount, CTag** ppTags, VARIANT* pItemValues, HRESULT* ppErrors ) = 0;	
	
	// ��  ��:	λ�Ŷ��ģ��μ���OPC DA 2.05A����AddItems
	// ��  ��:
	//			@dwCount		λ������
	//			@ppTags			λ�Ŷ����б�
	//			@pItemValues	дֵ�����б�
	//			[out]@pErrors	ÿ��Item ID�Ķ��������S_*����ɹ���E_*����ʧ��
	// ����ֵ:
	//			S_OK	ȫ���ɹ�
	//			S_FALSE	���ֳɹ�
	//			E_*		ȫ��ʧ��	
	virtual HRESULT WriteTags( DWORD dwCount, CTag** ppTags, VARIANT* pItemValues, HRESULT* ppErrors ) = 0;
};

class SC_OPC_DA_EXT_CLASS ScOpcDaSvr
{
public:
	ScOpcDaSvr();
	~ScOpcDaSvr();

	// ��  ��:	��Ȩ���ƣ�����ͻ��˶��ĵ�λ��������Ĭ��Ϊ������
	// ��  ��: 
	//		@dwMaxTagCount λ�Ŷ����������ޣ�0����������
	void SetMaxTagCount( DWORD dwMaxTagCount );

	// ��  ��:	����OPC�ص�����
	// ��  ��: 
	//		@pCallback �ص�����ָ��
	void SetCallback( IOPCDACallback* pCallback );

	// ��  ��:	����OPC����
	// ��  ��: 
	//		@hInstance	��ǰģ���Instance
	//		@pCLSID		OPC��������UUID
	// ����ֵ:
	//		TRUE	�����ɹ�
	//		FALSE	����ʧ��
	HRESULT StartServer( HINSTANCE hInstance, CLSID* pCLSID );
	
	// ��  ��:	ֹͣOPC����	
	void StopServer();
	
	// ��  ��:	��ȡ������������ʱ��	
	FILETIME GetStartTime();

	// ��  ��:	������ע��
	// ����ֵ:
	//		S_*	ע��ɹ�
	//		E_* ע��ʧ��
	HRESULT RegisterServer();
	
	// ��  ��:	��������ע��
	// ����ֵ:
	//		S_*	��ע��ɹ�
	//		E_* ��ע��ʧ��
	HRESULT UnregisterServer();
	
	// ��  ��:	�������Ƿ�ʹ��
	// ����ֵ:
	//		��ǰ���ӵĿͻ��˸���
	DWORD ServerInUse();

	// ��  ��:	��ȡ��ǰ�ͻ��˵Ķ�����Ϣ
	// ����ֵ:
	//		���ӿͻ����б�
	IOpcDaCltInfoList*	GetClientInfoList();
};

// Make a US English LCID
#define  ENG_LCID  MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),SORT_DEFAULT)

#endif // !defined(AFX_SCOPCDASVR_H__8BE028C2_0593_4DD8_AEF2_EE9C215F0592__INCLUDED_)
