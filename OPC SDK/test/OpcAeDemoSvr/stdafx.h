// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <string>
#include <algorithm>
using namespace std;

#include "AreaBuilder.h"
#include "SyntaxSugar.h"

#include "ScOpcAeSvr.h"
extern ScOpcAeSvr	g_ScOpcAeSvr;

enum opc_category
{
	condition_category,
	tracking_category,
	simple_category
};


// TODO: reference additional headers your program requires here
