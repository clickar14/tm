#include "Input_Alphabet.h"
#include "Tape_Alphabet.h"
#include "Uppercase.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

void Input_Alphabet::load(ifstream& definition, bool& valid)
{
    string value;

    if ((!(definition >> value)))
    {
        cout << "\nINPUT_ALPHABET ERROR: reached EOF before encountering other keywords.";
        valid = false;
        return;
    }
    // If the input_alphabet has no characters.
    if ((uppercase(value) == "TAPE_ALPHABET:"))
    {
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
                        cout << "\nINPUT_ALPHABET ERROR: The character '" << value[x] << "' is already in the input_alphabet.\n";
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
        else
        {
            cout << "\nINPUT_ALPHABET ERROR: Illegal alphabet character '" << value[0] << "'.\n";
            valid = false;
        }
        if ((!(definition >> value)))
        {
            cout << "\nINPUT_ALPHABET ERROR: Reached EOF without finding keyword 'TAPE_ALPHABET:'.\n";
            valid = false;
            return;
        }
        if (uppercase(value) == "TAPE_ALPHABET:")
        {
            return;
        }
    }
}
void Input_Alphabet::validate(const Tape_Alphabet& tape_alphabet, bool& valid) const
{
    for (int x = 0; x < alphabet.size(); x++)
    {
        if (!tape_alphabet.is_element(alphabet[x]))
        {
            cout << "\nINPUT_ALPHABET VALIDATION ERROR: The character '" << alphabet[x] << "' is not in the tape alphabet.\n";
            valid = false;
        }
    }
}
void Input_Alphabet::view() const
{
    //TODO ADD SIGMA SYMBOL
    cout << "SIGMA = {" << endl;
    for (int x = 0; x < alphabet.size(); ++x)
    {
        cout << " " << alphabet[x];
    }
    cout << " }" << endl;
}
bool Input_Alphabet::is_element(char value) const
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