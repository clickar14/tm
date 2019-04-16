#include "Final_States.h"
#include "States.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Uppercase.h"

using namespace std;

void Final_States::load(ifstream& definition, bool& valid)
{
    string value;
    /* If the state names is empty */
    if ((!(definition >> value)))
    {
        cout << "\nFINAL_STATES ERROR: THERE ARE NO FINAL_STATES PROVIDED IN THE DEFINITION FILE.\n";
        valid = false;
        return;
    }
    while (true)
    {
        /* Check whether the state name contains valid charecters or is a keyword */
        bool checkFlag = false, uniqueFlag = true;
        for (int x = 0; x < value.size(); x++)
        {
            if ((isalpha(value[x])) || (isdigit(value[x])) || (value[x] == '_'))
            {
                checkFlag = true;
            }
            else
            {
                checkFlag = false;
            }
        }
        /* If the state name is invalid */
        if (!checkFlag)
        {
            cout << "\nFINAL_STATES ERROR: Final_State name '" << value << "' contains invalid characters.\n";
            cout << "Final_State names may only contain letters, numbers, and underscores!\n";
            valid = false;
        }
        else
        {
            if (names.size() == 0)
            {
                names.push_back(value);
            }
            else if (names.size() > 0)
            {
                for (int y = 0; y < names.size(); y++)
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
                    cout << "\nFINAL_STATES ERROR: Final_State name '" << value << "' is not unique.\n";
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
            return;
        }
    }
}
void Final_States::validate(const States& all_states, bool& valid) const
{
    for (int x = 0; x < names.size(); x++)
    {
        if (all_states.is_element(names[x]) == false)
        {
            cout << "\nFINAL_STATES VALIDATION ERROR: The final_state '" << names[x] << "' is not in states.\n";
            valid = false;
        }
    }
}
void Final_States::view() const
{
    cout << "F = {" << endl;
    for (int x = 0; x < names.size(); ++x)
    {
        cout << " " << names[x];
    }
    cout << " }" << endl;
}
bool Final_States::is_element(string value) const
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