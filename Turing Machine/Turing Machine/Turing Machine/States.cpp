#include "States.h"
#include "Uppercase.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

void States::load(ifstream& definition, bool& valid)
{

    string value;
    /* If the state names is empty */
    if ((!(definition >> value)) || ((uppercase(value) == "INPUT_ALPHABET:")))
    {
        cout << "\nSTATES ERROR: THERE ARE NO STATES PROVIDED IN THE DEFINITION FILE.\n";
        valid = false;
        return;
    }
    while (true)
    {
        /* Check whether the state name contains valid charecters or is a keyword */
        bool checkFlag, uniqueFlag, keywordFlag;
        for (int x = 0; x < value.size(); x++)
        {
            if ((isalpha(value[x])) || (isdigit(value[x])) || (value[x] == '_'))
            {
                checkFlag = true;
                keywordFlag = false;
            }
            else
            {
                checkFlag = false;
                if (value[value.size() - 1] == ':')
                {
                    keywordFlag = true;
                }
                else
                {
                    keywordFlag = false;
                }
                break;
            }
        }
        /* If the state name is invalid */
        if (!checkFlag && !keywordFlag) 
        {
            cout << "\nSTATES ERROR: State name '" << value << "' contains invalid characters.\n";
            cout << "State names may only contain letters, numbers, and underscores!\n";
            valid = false;
        }
        else if (keywordFlag)
        {
            /* If the value is the next keyword return*/
            if ((uppercase(value) == "INPUT_ALPHABET:"))
            {
                return;
            }
            else
            {
                cout << "\nSTATES ERROR: Encountered unexpected keyword '" << value << "'.\n";
                cout << "States must be followed by the 'INPUT_ALPHABET:' keyword.\n";
                valid = false;
                return;
            }
        }
        else
        {
            if (names.size() == 0)
            {
                names.push_back(value);
            }
            else if (names.size() > 0)
            {
                for(int y = 0; y < names.size(); y++)
                {
                    if (names[y] == value)
                    {
                        uniqueFlag = false;
                        break;
                    }
                    uniqueFlag = true;
                }
                if (!uniqueFlag)
                {
                    cout << "\nSTATES ERROR: State name '" << value << "' is not unique.\n";
                    cout << "All state names must consist of a unique set of characters.\n";
                    valid = false;
                }
                else
                {
                    names.push_back(value);
                }
            }
        }
        if ((!(definition >> value)))
        {
            cout << "\nSTATES ERROR: Reached EOF before encountering keyword 'INPUT_ALPHABET'.\n";
            valid = false;
            return;
        }
    }

}
void States::view() const
{
    cout << "Q = {" << endl;
    for (int x = 0; x < names.size(); ++x)
    {
        cout << " " << names[x];
    }
    cout << " }" << endl;
}
bool States::is_element(string value) const
{
    for (int x = 0; x < names.size(); ++x)
    {
        if (names[x] == value)
        {
            return true;
        }
    }
    return false;
}