/*
 * CTimer.cpp
 *
 *  Created on: 21 juin 2010
 *      Author: user
 */

#include "CTimer.h"
#include <iostream>
using namespace std;

CTimer::CTimer(ApplicationManager* am)
{

	am->RegisterMainLoop( this );
	am->RegisterApplication(string("TIMER"), this );
	m_id = 0L;
	cout << "CTimer ctor" << endl;
}

CTimer::~CTimer()
{
	CTimerList::iterator it;
	for (it = m_timerList.begin(); it != m_timerList.end(); it++)
	{
		delete *it;
	}
	m_timerList.clear();
}

//bool mycompare(CTimer::CTimerInfo* lhs, CTimer::CTimerInfo* rhs)
//{
//	return ( lhs->timestamp < rhs->timestamp);
//}

unsigned long
CTimer::AddTimer(Timerable* object, int delay, unsigned long arg)
{
	CTimerInfo* timerInfo = new CTimerInfo;
	timerInfo->id = ++m_id;
	timerInfo->object = object;
	timerInfo->arg = arg;
	clock_t current = clock();
	//cout << "current is " << current << endl;
	timerInfo->timestamp = current + (clock_t)((double)CLOCKS_PER_SEC*(double)delay/1000.0);
	//cout << "CLOCKS_PER_SEC is " << CLOCKS_PER_SEC << endl;
	//cout << "future is " << timerInfo->timestamp << endl;
	//m_timerList.push_back(timerInfo);
	//m_timerList.sort(mycompare);
	//m_timerList.sort(Compare());
	m_timerList.insert(timerInfo);
	return m_id;
}

void
CTimer::DeleteTimer(unsigned long id)
{
	CTimerList::iterator it;
	for (it = m_timerList.begin(); it != m_timerList.end(); it++)
	{
		if ( (*it)->id == id )
		{
			delete *it;
			break;
		}
	}
	m_timerList.erase(it);
}

void
CTimer::ProcessTimer()
{
	//cout << "CTimer ProcessTimer" << endl;
	if (m_timerList.empty()) return;

	clock_t current = clock();

	if ( (*m_timerList.begin())->timestamp <= current )
	{
		CTimerList::iterator it = m_timerList.begin();
		unsigned long id = (*it)->id;
		unsigned long arg = (*it)->arg;
		(*it)->object->Timer(id, arg);
		//DeleteTimer(id);
		delete *it;
		m_timerList.erase(it);
	}
	return;
}

void
CTimer::Start()
{
}

void
CTimer::Execute()
{
	ProcessTimer();
}
