#pragma once

#include <string>
using namespace std;

#include "SimpleThread.h"
#include "IAlarmEventCenter.h"

class ConditionEventCenter : public IAlarmEventCenter, SimpleThread
{
public:
	ConditionEventCenter(void);
	~ConditionEventCenter(void);

public:
	void Release() override;
	BOOL Start() override;
	void Stop() override;

private:
	UINT Run() override;
	void _AddCondition( OpcEventCategory& category, const string& name );

private:
	vector<string>	m_CondNames;
};

