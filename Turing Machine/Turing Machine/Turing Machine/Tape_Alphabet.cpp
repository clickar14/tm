#include "Tape_Alphabet.h"
#include "Uppercase.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

void Tape_Alphabet::load(ifstream& definition, bool& valid)
{
    string value;
    /* If the state names is empty */
    if ((!(definition >> value)) || (uppercase(value) == "TRANSITION_FUNCTION:"))
    {
        cout << "\nTAPE_ALPHABET ERROR: There are no characters provided for the tape_alphabet.\n";
        valid = false;
        return;
    }
    while (true)
    {
        if ((value.length() == 1) && (value[0] != '\\') && (value[0] != '[') && (value[0] != ']') && (value[0] != '<') && (value[0] != '>') && (value[0] != '!') && (value[0] != '~'))
        {
            if (alphabet.size() == 0)
            {
                alphabet.push_back(value[0]);
            }
            else
            {
                bool uniqueFlag = true;
                for (int x = 0; x < alphabet.size(); ++x)
                {
                    if (alphabet[x] == value[0])
                    {
                        cout << "\nTAPE_ALPHABET ERROR: The character '" << value[x] << "' is already in the tape_alphabet.\n";
                        cout << "Please ensure that each character in the alphabet is unique.\n";
                        valid = false;
                        uniqueFlag = false;
                        break;
                    }
                }
                if (uniqueFlag)
                    alphabet.push_back(value[0]);
            }
        }
        else if(value.size() > 1)
        {
            if ((value.find(':') != -1) && (uppercase(value) != "TRANSITION_FUNCTION:") )
            {
                cout << "\nTAPE_ALPHABET ERROR: Encountered unexpected keyword '" << value << "' instead of expected keyword 'TRANSITION_FUNCTION:'.\n";
                definition >> value;
                valid = false;
                return;
            }
            cout << "\nTAPE_ALPHABET ERROR: Illegal string '" << value << "' found in tape_alphabet.\n";
            cout << "The tape_alphabet may only contain characters.\n";
            valid = false;
        }
        if ((!(definition >> value)))
        {
            cout << "\nTAPE_ALPHABET ERROR: Reached EOF without finding keyword 'TAPE_ALPHABET:'.\n";
            valid = false;
            return;
        }
        if (uppercase(value) == "TRANSITION_FUNCTION:")
        {
            return;
        }
    }
}
void Tape_Alphabet::view() const 
{
    cout << "Г = {" << endl;
    for (int x = 0; x < alphabet.size(); ++x)
    {
        cout << " " << alphabet[x];
    }
    cout << " }" << endl;
}
bool Tape_Alphabet::is_element(char value) const 
{
    for (int x = 0; x < alphabet.size(); ++x)
    {
        if (alphabet[x] == value)
        {
            return true;
        }
    }
    return false;
}