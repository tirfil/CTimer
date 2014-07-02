/*
 * CTimer.h
 *
 *  Created on: 21 juin 2010
 *      Author: user
 */

#ifndef CTIMER_H_
#define CTIMER_H_

#include "ApplicationManager.h"
#include "Interface.h"
#include <cstdlib>
#include <cstdio>
//#include <list>
#include <set>
#include <ctime>
using namespace std;

class CTimer : public Executable, public Application
{
	public:
		CTimer(ApplicationManager* );
		~CTimer();
		unsigned long AddTimer(Timerable*, int, unsigned long);
		void DeleteTimer(unsigned long);

		void Start(void);
		void Execute(void);
		struct CTimerInfo
		{
				clock_t timestamp;
				unsigned long id;
				Timerable*	object;
				unsigned long arg;
				/*bool operator<(CTimerInfo& rhs)
				{
					return (timestamp < rhs.timestamp);
				}
				*/
		};

		struct Compare
		{
			bool operator()(CTimerInfo* lhs, CTimerInfo* rhs)
			{
				return ( lhs->timestamp < rhs->timestamp);
			}
		};

	private:
		void ProcessTimer();

		//typedef list<CTimerInfo*> CTimerList;
		typedef multiset<CTimerInfo*, Compare > CTimerList;
		CTimerList m_timerList;
		unsigned long m_id;
};



#endif /* CTIMER_H_ */
