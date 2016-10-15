// ErrorHelper.h: interface for the ErrorHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(ERROR_DEFINE_H)
#define ERROR_DEFINE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//code��Χ0-255
#define STD_CTL_SCODE(n) MAKE_SCODE(SEVERITY_ERROR, FACILITY_CONTROL, n)

#define E_TASK_NO_FOUND			STD_CTL_SCODE(0)
#define E_TASK_CONN_FAILED		STD_CTL_SCODE(1)
#define E_TASK_HAS_CONNECTED	STD_CTL_SCODE(2)
#define E_TASK_SVR_UNSPECIFIED	STD_CTL_SCODE(3)
#define E_TASK_DISCON_SVR_FIRST	STD_CTL_SCODE(4)
#define E_TASK_DUPLICATE_NAME	STD_CTL_SCODE(5)
#define E_TASK_ERR_TASK			STD_CTL_SCODE(6)
#define E_TASK_NO_GROUP			STD_CTL_SCODE(7)
#define E_TASK_REG_PROXY		STD_CTL_SCODE(8)
#define E_TASK_INVALID_PARAM	STD_CTL_SCODE(9)
#define E_TASK_SREAD_NO_SOURCE	STD_CTL_SCODE(10)
#define E_TASK_INVALID_ALL_SYM	STD_CTL_SCODE(11)
#define E_TASK_WRITE_INVALID_DATA	STD_CTL_SCODE(12)

#endif // !defined(AFX_ERRORHELPER_H__4B6FB549_5EA6_4538_8FEE_B29ECDD948A2__INCLUDED_)