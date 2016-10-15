#pragma once

#include "IOpcAreaNode.h"

#include <vector>
using namespace std;

class AreaBuilder
{
private:
	AreaBuilder(void) {}
	~AreaBuilder(void){}

public:
	static IOpcAreaNode* GetBrowser();

	static void	ChooseSource( vector<DWORD>& dwAreaIds, string& strSource );
private:
	static IOpcAreaNode*	m_pAreaRoot;
};

