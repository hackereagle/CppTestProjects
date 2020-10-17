#ifndef _H_BASE_MENU_
#define _H_BASE_MENU_
#include <iostream>
#include <string>
#include <vector>

class BaseMenu
{
public:
    BaseMenu()
    {

    }

    virtual ~BaseMenu() = 0;
    //virtual BaseMenu* getNextMenu(int ichoice, bool& isQuitOptionSelected) = 0;
	virtual void doOptionAction(int ichoice) = 0;
    virtual void printMenu()
    {
        int len = m_Option.size();
        for(int i = 0; i < len; i++)
            std::cout << m_Option[i] << std::endl;
    }

protected:
    std::vector<std::string> m_Option;
	int row = 0;
	int col = 0;
};
#endif //_H_BASE_MENU_