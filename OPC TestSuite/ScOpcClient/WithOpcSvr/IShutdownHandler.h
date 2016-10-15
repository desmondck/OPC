#if !defined(ISHUTDOWN_HANDLER_H)
#define ISHUTDOWN_HANDLER_H

interface IShutdownHandler  
{
	//接收到网络数据包
	virtual void ShutDown() = 0;
};

#endif 