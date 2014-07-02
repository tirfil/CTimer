/*
 * ApplicationManager.h
 *
 *  Created on: 31 mai 2010
 *      Author: user
 */

#ifndef APPLICATIONMANAGER_H_
#define APPLICATIONMANAGER_H_

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

#include "Interface.h"

class ApplicationManager
{

	typedef map<string, Application* > ApplicationTable ;
	typedef vector< Executable* > MainLoopList	;

	public:
		ApplicationManager(void);
		~ApplicationManager(void);

		void 			RegisterApplication(string, Application*);
		Application* 	GetApplication(string);

		void 	RegisterMainLoop( Executable* );

		void 	Start();
		void 	Stop();

	private:

		ApplicationTable 	m_applicationTable;
		MainLoopList		m_mainLoopList;

		ApplicationManager(const ApplicationManager&) {};
		const ApplicationManager& operator=(const ApplicationManager& am ) { return am; };

		bool	m_running;
		void 	MainLoop();

};


#endif /* APPLICATIONMANAGER_H_ */
