#pragma once

#include "SimpleThread.h"
#include "IAlarmEventCenter.h"

class TrackingEventCenter : public IAlarmEventCenter, SimpleThread
{
public:
	TrackingEventCenter(void);
	~TrackingEventCenter(void);

public:
	void Release() override;
	BOOL Start() override;
	void Stop() override;

private:
	UINT Run() override;
};

