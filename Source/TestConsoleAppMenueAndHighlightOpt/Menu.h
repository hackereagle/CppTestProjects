#pragma once
#ifndef _H_MENU_
#define _H_MENU_

#include "BaseMenu.h"

// here record some idea:
// The feature of reading option from file would be a class can read option as be instance
// and can get option from its properties
class MainMenu : public BaseMenu
{
public:
	MainMenu()
	{
		// In future, we can write menue and each sub menu in a file, e.g. xml, ini, json etc.
		// I seem like json is very proper for this case.
		// Reading and assignning setting into protected member m_Option in constructor.
		m_Option.push_back("First Option");
		m_Option.push_back("Second Option");
		m_Option.push_back("Third Option");
		m_Option.push_back("Exit");
	}

	~MainMenu()
	{
	}

private:

};

#endif // !_H_MENU_