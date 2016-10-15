// IdGenerator.h: interface for the IdGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDGENERATOR_H__3DD13675_8D61_46D4_B7CD_B83099BF34B1__INCLUDED_)
#define AFX_IDGENERATOR_H__3DD13675_8D61_46D4_B7CD_B83099BF34B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IdGenerator  
{
public:
	static DWORD GenerateId() { return ++m_dwId; }

private:
	IdGenerator();
	virtual ~IdGenerator();

	static DWORD m_dwId;
};

DWORD IdGenerator::m_dwId = 0;

#endif // !defined(AFX_IDGENERATOR_H__3DD13675_8D61_46D4_B7CD_B83099BF34B1__INCLUDED_)
