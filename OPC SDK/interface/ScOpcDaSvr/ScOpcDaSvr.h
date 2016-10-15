//	Author: Wang, Chunjie
//	Date:	2013-10
//	Desc:	OPC DA服务器SDK，该SDK实现完整的《OPC DA 2.05A》协议

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

//用于描述连接到OPC DA服务器上的客户端连接信息
interface IOpcDaCltInfo
{
	//客户端标识，在客户端名称为指定情况下唯一标识当前客户端连接
	virtual DWORD	GetId() = 0;

	//客户端名称
	virtual LPCTSTR GetName() = 0;

	//Group数量
	virtual DWORD	GetGroupCount() = 0;

	//指定Group的名称
	virtual LPCTSTR	GetGroupName( DWORD dwGroupIndex ) = 0;

	//指定Group上订阅的位号数量
	virtual DWORD	GetItemCount( DWORD dwGroupIndex ) = 0;
};

interface IOpcDaCltInfoList
{
	virtual void Release() = 0;

	virtual DWORD GetClientCount() = 0;
	virtual IOpcDaCltInfo* GetClient( DWORD dwClientIndex ) = 0;
};



//Item ID关联的位号对象
//基于以下几点考虑，此处采用导出类，而非导出接口
//	1. 原有开发包为导出类，保持导出类可降低迁移成本。
//	2. 导出接口有如下两种实现方式：
//		a. 每个OPC服务器自己实现CTag类：
//			CTag实现在不同的OPC服务器上并无差异，为可复用代码，各自实现导致代码冗余，增加成本，且CTag为并发访问对象。
//		b. 由SDK实现CTag，并通过CreateTag创建对象
//			丧失了继承CTag的能力
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
	
	//生命周期由OPC SDK管理，外部无需调用AddRef/Release，此处为导出类折中的结果
	LONG AddRef();
	LONG Release();
	LONG RefCount();
private:
	void*	m_pData;
};

interface IOPCDACallback  
{
	// 描  述:	返回服务器的基本信息，参见《OPC DA 2.05A》中GetStatus
	// 参  数:
	//			@state			服务器运行状态，OPC_STATUS_RUNNING表示正常运行
	//			@dwBandWidth	带宽率，-1表示未知
	//			@wMajor			主版本号
	//			@wMinor			子版本号
	//			@wBuildNum		构建号
	//			@pVendor		供应商名称
	virtual void	GetStatus( OPCSERVERSTATE& state, DWORD& dwBandWidth, WORD& wMajor, WORD& wMinor, WORD& wBuildNum, char*& pVendor ) = 0;
	
	//Browser
	// 描  述:	参见《OPC DA 2.05A》中QueryOrganization
	virtual HRESULT QueryOrganization( OPCNAMESPACETYPE& nameSpaceType ) = 0;
	
	// 描  述:	获取当前Browser的版本号，和GetBrowser配合使用
	//			当GetBrowser中返回的Browser内发生变化时，递增Browser Version表明此次变化
	//			ScOpcDaSvr发现版本与之前的版本号不一致则重新调用GetBrowser
	// 返回值:	
	//			当前Browser的版本号
	virtual DWORD	GetBrowserVersion() = 0;
	
	// 描  述:	获取OPC服务器的Browser对象
	// 返回值:
	//			当前Browser对象的Root
	//			OPC_NS_FLAT:		Root下为平坦结构
	//			OPC_NS_HIERARCHIAL:	Root下为树状结构
	virtual const IOpcNode* GetBrowser( TCHAR& cSeparator ) = 0;
	
	// 描  述:	获得修正后的Update Rate
	//			每当客户端执行AddGroup时，调用此接口修正Update Rate
	//			参见《OPC DA 2.05A》中AddGroup中Request\Revise Rate
	// 参  数:
	//			@dwRequestRate	客户端请求的更新速率
	// 返回值:
	//			修正后的更新频率
	virtual DWORD	GetUpdateRate( DWORD dwRequestRate ) = 0;
	
	//Tags
	// 描  述:	位号订阅，参见《OPC DA 2.05A》中AddItems
	// 参  数:
	//			@dwCount		位号数量
	//			@pItemIDs		位号的Item ID数组，Item ID由Browser的位号结构决定
	//			@pAccessPaths	参见协议，正常情况下可忽略该参数
	//			[out]@ppTags	输出参数，每个Item ID订阅对应的CTag对象
	//			[out]@pErrors	每个Item ID的订阅情况，S_*代表成功，E_*代表失败
	// 返回值:
	//			S_OK	全部成功
	//			S_FALSE	部分成功
	//			E_*		全部失败
	virtual HRESULT Subscribe( DWORD dwCount, const char** pItemIDs, const char** pAccessPaths, CTag** ppTags, HRESULT* pErrors ) = 0;
	
	// 描  述:	位号反订阅，参见《OPC DA 2.05A》中RemoveItems
	// 参  数:
	//			@dwCount	位号数量
	//			@ppTags		位号对象列表	
	// 返回值:
	//			S_OK	全部成功
	//			S_FALSE	部分成功
	//			E_*		全部失败	
	virtual HRESULT Unsubscribe( DWORD dwCount, CTag** ppTags ) = 0;

	//暂未使用
	virtual HRESULT ReadTags( DWORD dwCount, CTag** ppTags, VARIANT* pItemValues, HRESULT* ppErrors ) = 0;	
	
	// 描  述:	位号订阅，参见《OPC DA 2.05A》中AddItems
	// 参  数:
	//			@dwCount		位号数量
	//			@ppTags			位号对象列表
	//			@pItemValues	写值内容列表
	//			[out]@pErrors	每个Item ID的订阅情况，S_*代表成功，E_*代表失败
	// 返回值:
	//			S_OK	全部成功
	//			S_FALSE	部分成功
	//			E_*		全部失败	
	virtual HRESULT WriteTags( DWORD dwCount, CTag** ppTags, VARIANT* pItemValues, HRESULT* ppErrors ) = 0;
};

class SC_OPC_DA_EXT_CLASS ScOpcDaSvr
{
public:
	ScOpcDaSvr();
	~ScOpcDaSvr();

	// 描  述:	授权控制，允许客户端订阅的位号总数。默认为无限制
	// 参  数: 
	//		@dwMaxTagCount 位号订阅数量上限，0代表无限制
	void SetMaxTagCount( DWORD dwMaxTagCount );

	// 描  述:	设置OPC回调对象
	// 参  数: 
	//		@pCallback 回调对象指针
	void SetCallback( IOPCDACallback* pCallback );

	// 描  述:	启动OPC服务
	// 参  数: 
	//		@hInstance	当前模块的Instance
	//		@pCLSID		OPC服务器的UUID
	// 返回值:
	//		TRUE	启动成功
	//		FALSE	启动失败
	HRESULT StartServer( HINSTANCE hInstance, CLSID* pCLSID );
	
	// 描  述:	停止OPC服务	
	void StopServer();
	
	// 描  述:	获取服务器的启动时间	
	FILETIME GetStartTime();

	// 描  述:	服务器注册
	// 返回值:
	//		S_*	注册成功
	//		E_* 注册失败
	HRESULT RegisterServer();
	
	// 描  述:	服务器反注册
	// 返回值:
	//		S_*	反注册成功
	//		E_* 反注册失败
	HRESULT UnregisterServer();
	
	// 描  述:	服务器是否被使用
	// 返回值:
	//		当前连接的客户端个数
	DWORD ServerInUse();

	// 描  述:	获取当前客户端的订阅信息
	// 返回值:
	//		连接客户端列表
	IOpcDaCltInfoList*	GetClientInfoList();
};

// Make a US English LCID
#define  ENG_LCID  MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),SORT_DEFAULT)

#endif // !defined(AFX_SCOPCDASVR_H__8BE028C2_0593_4DD8_AEF2_EE9C215F0592__INCLUDED_)
