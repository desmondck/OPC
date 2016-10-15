#ifndef _SC_OPC_DA_I_OPC_ITEM_PROPERTY_H_CK_2014_03_10
#define _SC_OPC_DA_I_OPC_ITEM_PROPERTY_H_CK_2014_03_10

//代表当前Node的ItemId
#define NODE_ITEM_ID	"$NODE_ITEM_ID$"

//Item属性，请参见《OPC DA 2.05A》协议
interface IOpcItemProperty
{
	virtual void Release() = 0;
	//数据类型
	virtual VARTYPE GetDataType() const = 0;
	//属性Id
	virtual DWORD	GetPropertyId() const = 0;
	//描述
	virtual const char* GetDescription() const = 0;

	//Item Id
	virtual const char* GetItemId() const = 0;
	//数值
	virtual BOOL	GetValue( VARIANT* pValue ) const = 0;
};

interface IOpcItemPropList
{
	virtual void Release() = 0;

	//Item Property总数
	virtual DWORD	GetCount() const = 0;
	//指定的Item Property
	virtual const	IOpcItemProperty* Get( DWORD dwIndex ) const = 0;
};

#endif	//_SC_OPC_DA_I_OPC_ITEM_PROPERTY_H_CK_2014_03_10