# OPC
Design and implement OPC DA Server(2.05A) and OPC AE Server(1.10)

前后共三年独立承担了某国内控制公司的OPC的设计、实现工作。
刚接手时，公司采用第三方的OPC开发包，而该工具包的vendor已倒闭，问题无法修复、性能、规模上都无法满足业务发展的诉求。
我在闲暇时分析、设计并实现了一套OPC DA开发框架及一套OPC AE开发框架，最终做为产品正式交付。
这两组框架及基于框架的原型实现可100%的通过OPC基金会提供的兼容性测试框架。

除此之外，本人还设计了一套独立的自动化测试程序，包括OPC DA和OPC AE两部分。
其中，OPC DA的测试框架是基于DSL，当然该DSL是OPC定制的，简单但却很实用。

由于OPC DA和OPC AE的框架是做为产品交付的，基于版权问题，我不能将实现放上来，但interface已上传，可资借鉴。
框架的使用方式在test中，可供参考。
测试框架是独立的、非产品代码，可从本git源获取，如若对各位有所帮助也算是自己对这个曾经付诸努力行业的一点交代。

##OPC DA Server(2.05A)
```
class CTag
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

class ScOpcDaSvr
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
```
##OPC AE Server
```
interface IOpcAeCallback
{
	virtual const IOpcAreaNode* GetBrowser( DWORD& dwVersion, TCHAR& cSeparator ) = 0;

	//参见IOPCEventServer:: CreateEventSubscription
	virtual DWORD ReviseMaxSize( DWORD dwMaxSize ) const = 0;
	virtual DWORD ReviseBufTime( DWORD dwBufferTime ) const = 0;

	//OPC客户端执行报警确认
	virtual HRESULT ClientAlarmAck( DWORD dwCount, IOpcConditionEvent** ppEvents, LPCTSTR pszAckId, LPCTSTR pszComment, HRESULT* pErrors ) = 0;
};

class SC_OPC_AE_CLASS ScOpcAeSvr
{
public:
	ScOpcAeSvr();
	~ScOpcAeSvr();
	
	void SetProductInfo( LPCTSTR strVendor, WORD wMajorVersion, WORD wMinorVersion, WORD wBuildNumber );
	void SetState( OPCEVENTSERVERSTATE dwServerState );

	//准备工作
	void SetMaxClient( DWORD dwMaxCltCount );		//支持最大客户端的连接个数, 0表示无限制
	void SetMaxEventCount( DWORD dwMaxEventCount );	//推送报警/事件上限，0表示无限制
	void SetReportable( BOOL bReportable );
	void SetCallback( IOpcAeCallback* pCallback );

	//Category
	void AddCategory( DWORD dwCategoryId, const OpcEventCategory& category );
	void RemoveCategory( DWORD dwCategoryId );
	void RemoveAllCategory();

	//服务器启动/停止
	BOOL StartServer( HINSTANCE hInstance, CLSID* pCLSID );
	BOOL StopServer();
	FILETIME GetStartTime();
	
	//服务器注册/反注册
	HRESULT RegisterServer();
	HRESULT UnregisterServer();
	
	//服务器使用状态
	DWORD ServerInUse();

	HRESULT ReportEvent( IOpcSimpleEvent* pEvent );

	IOpcConditionEvent*	FindEvent( DWORD dwAreaDepth, DWORD* pdwAreaIds, LPCTSTR strSource, LPCTSTR strCondName );
	
	void RemoveEvent( DWORD dwAreaDepth, DWORD* pdwAreaIds, LPCTSTR strSource, LPCTSTR strCondName );
	void RemoveEvents( DWORD dwAreaDepth, DWORD* pdwAreaIds, LPCTSTR strSource );

	void RemoveAllEvents();
private:
	void*	m_pData;
};
```
