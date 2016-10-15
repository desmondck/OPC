//Wang, Chunjie	2013-10-30	长岭
#ifndef __OPCPROPS_H
#define __OPCPROPS_H

/*	OPC Specific Property Set 1
The first 6 properties are 'special cases' in that they represent data that would exist with in the OPC Server 
if this item were added to an OPCGroup and do not represent properties of the 'real' tag record in the underlying system.
*/
#define OPC_PROP_CDT_ID        1
#define OPC_PROP_VALUE_ID      2
#define OPC_PROP_QUALITY_ID    3
#define OPC_PROP_TIME_ID       4
#define OPC_PROP_RIGHTS_ID     5
#define OPC_PROP_SCANRATE_ID   6

#define OPC_PROP_UNIT_ID       100
#define OPC_PROP_DESC_ID       101
#define OPC_PROP_HIEU_ID       102
#define OPC_PROP_LOEU_ID       103
#define OPC_PROP_HIRANGE_ID    104
#define OPC_PROP_LORANGE_ID    105
#define OPC_PROP_CLOSE_ID      106
#define OPC_PROP_OPEN_ID       107
#define OPC_PROP_TIMEZONE_ID   108

#define OPC_PROP_DEFDISP_ID	   200
#define OPC_PROP_FGC_ID        201
#define OPC_PROP_BGC_ID        202
#define OPC_PROP_BLINK_ID      203
#define OPC_PROP_BMP_ID        204
#define OPC_PROP_SND_ID        205
#define OPC_PROP_HTML_ID       206
#define OPC_PROP_AVI_ID        207

#define OPC_PROP_ALMSTAT_ID    301
#define OPC_PROP_ALMHELP_ID    302
#define OPC_PROP_ALMAREAS_ID   303
#define OPC_PROP_ALMPRIAREA_ID 304
#define OPC_PROP_ALMCOND_ID    305
#define OPC_PROP_ALMLIMIT_ID   306
#define OPC_PROP_ALMDB_ID      307
#define OPC_PROP_ALMHH_ID      308
#define OPC_PROP_ALMH_ID       309
#define OPC_PROP_ALML_ID       310
#define OPC_PROP_ALMLL_ID      311
#define OPC_PROP_ALMROC_ID     312
#define OPC_PROP_ALMDEV_ID     313

/*							PropertyID,				Description,				vtDataType	*/

//OPC Specific Properties
#define OPC_PROP_CDT		OPC_PROP_CDT_ID,		"Item Canonical Data Type",	VT_I2
#define OPC_PROP_VALUE      OPC_PROP_VALUE_ID,		"Item Value",				VT_R4	//此处类型无效，由具体类型最终指定
#define OPC_PROP_QUALITY    OPC_PROP_QUALITY_ID,	"Item Quality",				VT_I2
#define OPC_PROP_TIME       OPC_PROP_TIME_ID,		"Item Timestamp",			VT_DATE
#define OPC_PROP_RIGHTS     OPC_PROP_RIGHTS_ID,		"Item Access Rights",		VT_I4
#define OPC_PROP_SCANRATE   OPC_PROP_SCANRATE_ID,	"Server Scan Rate",			VT_R4

//Properties related to the Item Value. 
#define OPC_PROP_UNIT       OPC_PROP_UNIT_ID,		"EU Units",					VT_BSTR
#define OPC_PROP_DESC       OPC_PROP_DESC_ID,		"Item Description",			VT_BSTR 
#define OPC_PROP_HIEU       OPC_PROP_HIEU_ID,		"High EU",					VT_R8 
#define OPC_PROP_LOEU       OPC_PROP_LOEU_ID,		"Low EU",					VT_R8 
#define OPC_PROP_HIRANGE    OPC_PROP_HIRANGE_ID,	"High Instrument Range",	VT_R8
#define OPC_PROP_LORANGE    OPC_PROP_LORANGE_ID,	"Low Instrument Range",		VT_R8 
#define OPC_PROP_CLOSE      OPC_PROP_CLOSE_ID,		"Contact Close Label",		VT_BSTR
#define OPC_PROP_OPEN       OPC_PROP_OPEN_ID,		"Contact Open Label",		VT_BSTR 
#define OPC_PROP_TIMEZONE   OPC_PROP_TIMEZONE_ID,	"Item Time zone",			VT_I4

//Properties related operator displays
#define OPC_PROP_DEFDISP	OPC_PROP_DEFDISP_ID,	"Default Display",			VT_BSTR
#define OPC_PROP_FGC        OPC_PROP_FGC_ID,		"Current Foreground Color",	VT_I4 
#define OPC_PROP_BGC        OPC_PROP_BGC_ID,		"Current Background Color",	VT_I4 
#define OPC_PROP_BLINK      OPC_PROP_BLINK_ID,		"Current Blink",			VT_BOOL 
#define OPC_PROP_BMP        OPC_PROP_BMP_ID,		"BMP File",					VT_BSTR 
#define OPC_PROP_SND        OPC_PROP_SND_ID,		"Sound File",				VT_BSTR
#define OPC_PROP_HTML       OPC_PROP_HTML_ID,		"HTML File",				VT_BSTR 
#define OPC_PROP_AVI        OPC_PROP_AVI_ID,		"AVI File",					VT_BSTR

//Properties Related to Alarm and Condition Values
#define OPC_PROP_ALMSTAT    OPC_PROP_ALMSTAT_ID,	"Condition Status",			VT_BSTR 
#define OPC_PROP_ALMHELP    OPC_PROP_ALMHELP_ID,	"Alarm Quick Help",			VT_BSTR 
#define OPC_PROP_ALMAREAS   OPC_PROP_ALMAREAS_ID,	"Alarm Area List",			VT_BSTR|VT_ARRAY 
#define OPC_PROP_ALMPRIAREA OPC_PROP_ALMPRIAREA_ID,	"Primary Alarm Area",		VT_BSTR  
#define OPC_PROP_ALMCOND    OPC_PROP_ALMCOND_ID,	"Condition Logic",			VT_BSTR
#define OPC_PROP_ALMLIMIT   OPC_PROP_ALMLIMIT_ID,	"Limit Exceeded",			VT_BSTR 
#define OPC_PROP_ALMDB      OPC_PROP_ALMDB_ID,		"Deadband",					VT_R8 
#define OPC_PROP_ALMHH      OPC_PROP_ALMHH_ID,		"HiHi Limit",				VT_R8
#define OPC_PROP_ALMH       OPC_PROP_ALMH_ID,		"Hi Limit",					VT_R8
#define OPC_PROP_ALML       OPC_PROP_ALML_ID,		"Lo Limit",					VT_R8
#define OPC_PROP_ALMLL      OPC_PROP_ALMLL_ID,		"LoLo Limit",				VT_R8
#define OPC_PROP_ALMROC     OPC_PROP_ALMROC_ID,		"Rate of Change Limit",		VT_R8
#define OPC_PROP_ALMDEV     OPC_PROP_ALMDEV_ID,		"Deviation Limit",			VT_R8

//Vendor specific Properties 
//	ID codes for these properties must have values of 5000 orgreater. 
//	They donot need to be sequential. The data types must be compatable withthe VARIANT. 



#endif