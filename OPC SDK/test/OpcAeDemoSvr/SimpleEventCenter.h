#pragma once

#include "SimpleThread.h"
#include "IAlarmEventCenter.h"

class SimpleEventCenter : public IAlarmEventCenter, SimpleThread
{
public:
	SimpleEventCenter(void);
	~SimpleEventCenter(void);

public:
	void Release() override;

	BOOL Start() override;
	void Stop() override;

private:
	UINT Run() override;

};

