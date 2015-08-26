#pragma once 

class Engine;

class Core
{
	friend class Engine;

protected:
	virtual bool OnCreate() 	{ return true; }	// init
	virtual bool OnUpdate()  {return true; }	// step
	virtual bool OnShutdown() { return true; }	// term
};