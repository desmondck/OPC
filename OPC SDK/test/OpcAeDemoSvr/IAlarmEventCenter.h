#pragma once

interface IAlarmEventCenter
{
	virtual void Release() = 0;

	virtual BOOL Start() = 0;
	virtual void Stop()	= 0;
};