#ifndef _SC_OPC_DA_I_OPC_ITEM_PROPERTY_H_CK_2014_03_10
#define _SC_OPC_DA_I_OPC_ITEM_PROPERTY_H_CK_2014_03_10

//����ǰNode��ItemId
#define NODE_ITEM_ID	"$NODE_ITEM_ID$"

//Item���ԣ���μ���OPC DA 2.05A��Э��
interface IOpcItemProperty
{
	virtual void Release() = 0;
	//��������
	virtual VARTYPE GetDataType() const = 0;
	//����Id
	virtual DWORD	GetPropertyId() const = 0;
	//����
	virtual const char* GetDescription() const = 0;

	//Item Id
	virtual const char* GetItemId() const = 0;
	//��ֵ
	virtual BOOL	GetValue( VARIANT* pValue ) const = 0;
};

interface IOpcItemPropList
{
	virtual void Release() = 0;

	//Item Property����
	virtual DWORD	GetCount() const = 0;
	//ָ����Item Property
	virtual const	IOpcItemProperty* Get( DWORD dwIndex ) const = 0;
};

#endif	//_SC_OPC_DA_I_OPC_ITEM_PROPERTY_H_CK_2014_03_10