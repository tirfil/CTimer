//============================================================================
// Name        : ApplicationManager.cpp
// Author      : 
// Version     :
//============================================================================

#include "ApplicationManager.h"


ApplicationManager::ApplicationManager()
{
	m_running = false;
}

ApplicationManager::~ApplicationManager()
{

}

void
ApplicationManager::RegisterApplication( string name, Application* module )
{
	m_applicationTable[name] = module;
}

Application*
ApplicationManager::GetApplication(string name)
{
	return m_applicationTable[name];
}

void
ApplicationManager::RegisterMainLoop( Executable* module )
{
	m_mainLoopList.push_back(module);
}

void
ApplicationManager::MainLoop()
{
	while ( m_running )
	{
		if ( m_mainLoopList.empty() )
		{
#ifndef WIN32
			sleep(20);
#endif
			continue;
		}

		MainLoopList::iterator it;

		for ( it = m_mainLoopList.begin(); it != m_mainLoopList.end(); it++ )
		{
			(*it)->Execute();
		}
	}
}

void
ApplicationManager::Start()
{
	m_running = true;
	ApplicationTable::iterator it;
	for ( it = m_applicationTable.begin(); it != m_applicationTable.end(); it++)
	{
		it->second->Start();
	}
	MainLoop();
}

void
ApplicationManager::Stop()
{
	m_running = false;
}
