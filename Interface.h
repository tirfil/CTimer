/*
 * Interface.h
 *
 *  Created on: 31 mai 2010
 *      Author: user
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

// To register: (in constructor)
// ApplicationManager::RegisterMainLoop( Executable* module )
class Executable
{
	public:
		// Code to execute into the MainLoop
		// ApplicationManager::MainLoop()
		virtual void Execute(void) = 0;
};

// Application can communicate with other registered application
// using ApplicationManager::GetApplication(string name)
// To register: (in constructor)
// ApplicationManager::RegisterApplication( string name, Application* module )
class Application
{
	public:
		// 	All applications are registered
		virtual void Start(void) = 0;
};

class Timerable
{
	public:
		virtual void Timer(unsigned long,unsigned long) = 0;
};

#endif /* INTERFACE_H_ */
