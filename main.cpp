/*
 * main.cpp
 *
 *  Created on: 31 mai 2010
 *      Author: user
 */

#include <iostream>
#include <string>
#include <ctime>
using namespace std;
#include "Interface.h"
#include "ApplicationManager.h"
#include "CTimer.h"


#include <cstdlib>
#include <cstdio>
using namespace std;



class Benchmark : public Executable, public Application
{
	public:

		Benchmark(ApplicationManager* am)
		{
			am->RegisterApplication(string("Benchmark"), this );
			am->RegisterMainLoop( this );
			m_applicationManager = am;
		}

		void Execute()
		{
			clock_t current = clock();
			//cout << (unsigned long)current << endl;
			unsigned long delay;
			delay = ((unsigned long)(current - m_last)/(unsigned long)CLOCKS_PER_SEC)*1000UL;
			if ( delay > m_maxDelay)
			{
				m_maxDelay = delay;
				cout << "Max loop delay = " << delay << " ms" << endl;
			}

			m_last = current;
		}
		void Start()
		{
			m_last = clock();
			m_maxDelay = 0UL;
		}

	private:
		ApplicationManager*	m_applicationManager;
		clock_t m_last;
		unsigned long m_maxDelay;
};

class TestTimer : public Timerable, public Application
{
	public:
		TestTimer(ApplicationManager* am)
		{
			m_applicationManager = am;
			am->RegisterApplication(string("TESTTIMER"), this );
		}
		~TestTimer()
		{

		}
		void Start()
		{
			cout << "TestTimer::Start" << endl;
			m_timer = (CTimer*)m_applicationManager->GetApplication("TIMER");
			m_start = clock();
			m_id1 = m_timer->AddTimer(this, 7000, 1L);
			m_id2 = m_timer->AddTimer(this, 2000, 2L);
		}
		void Timer(unsigned long id, unsigned long arg)
		{
			//if (id == m_id1)
			if ( arg == 1L )
			{
//				time_t rawtime;
//				struct tm* timeinfo;
//				time(&rawtime);
//				timeinfo = localtime(&rawtime);
//				cout << asctime(timeinfo);

				cout << "Time is " << double(clock() - m_start ) * 1000.0 / CLOCKS_PER_SEC << " ms" << endl;
				cout << "***Timer A*** " << id << endl;
				m_id1 = m_timer->AddTimer(this, 7000, 1L);
			}
			//if (id == m_id2)
			if ( arg == 2L )
			{
//				time_t rawtime;
//				struct tm* timeinfo;
//				time(&rawtime);
//				timeinfo = localtime(&rawtime);
//				cout << asctime(timeinfo);
				cout << "Time is " << double(clock() - m_start ) * 1000.0 / CLOCKS_PER_SEC << " ms" << endl;
				cout << "***Timer B*** " << id << endl;
				m_id2 = m_timer->AddTimer(this, 2000, 2L);
			}
		}
	private:
		ApplicationManager* m_applicationManager;
		CTimer* m_timer;
		unsigned long m_id1;
		unsigned long m_id2;
		clock_t m_start;
};

int main(int argc, char* argv[] ) {
	cout << "CTimer" << endl; //
	ApplicationManager am;
	Benchmark bench(&am);
	CTimer timer(&am);
	TestTimer tt(&am);
	am.Start();
	return 0;
}
