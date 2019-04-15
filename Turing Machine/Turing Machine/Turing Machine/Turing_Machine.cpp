#include "Turing_Machine.h"
#include "Tape.h"
#include "Input_Alphabet.h"
#include "Tape_Alphabet.h"
#include "Transition_Function.h"
#include "States.h"
#include "Final_States.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Uppercase.h"

using namespace std;
vector<string> input_strings;

Turing_Machine::Turing_Machine(string definition_file_name)
{
    valid = true;
    string defFilename = definition_file_name;
    defFilename.append(".def");
    ifstream definitionFile(defFilename);
    bool fileOpenCheck = true;
    /* Definition file checks*/
    if (!definitionFile)
    {
        cout << "FILE ERROR: THE DEFINITION FILE '" << defFilename << "' COULD NOT BE OPENED!\n"
             << "Check file name, path, and/or read permissions.\n";
        fileOpenCheck = false;
    }
    else if ((definitionFile.peek() == std::ifstream::traits_type::eof()))
    {
        cout << "FILE ERROR: THE DEFINITION FILE '" << defFilename << "' IS EMPTY!" << endl;
        fileOpenCheck = false;
    }
    if (fileOpenCheck)
    {
        // Loading the description
        vector<string> definitionFileContents;
        string line;
        int truncatePos, lineIndex = 0;
        while (getline(definitionFile, line))
        {
            definitionFileContents.push_back(line);
        }
        // Go through the definition file and find where the file description ends.
        for (int x = 0; x < definitionFileContents.size(); x++)
        {
            line = uppercase(definitionFileContents[x]);
            
            truncatePos = line.find("STATES: ");

            ++lineIndex;
            if (truncatePos != -1)
            {
                size_t cutlen = string::npos;
                definitionFileContents[x].erase(truncatePos, cutlen);
                definitionFileContents.erase(definitionFileContents.begin() + lineIndex, definitionFileContents.end());
                for (int index = 0; index < definitionFileContents.size(); index++)
                {
                    description.push_back(definitionFileContents[index]);
                }
                break;
            }
        }
        if (truncatePos == -1)
        {
            cout << "\nLOAD ERROR: Could not find keyword 'STATES: ' needed to begin file loading.\n";
            valid = false;
        }

        // Reopening the definition file to go through the rest of the definition file.
        definitionFile = ifstream(defFilename);

        /* Begin loading the turing machine */
        while ((definitionFile >> line) && (truncatePos != -1))
        {
            if ((uppercase(line)) == "STATES:")
            {
                // Load the states
                all_states.load(definitionFile, valid);
                if (!valid)
                {
                    cout << "\nLOAD ERROR: Errors must be fixed with STATES before loading can continue.\n";
                    break;
                }
                // Load the input_alphabet
                input_alphabet.load(definitionFile, valid);
                if (!valid)
                {
                    cout << "\nLOAD ERROR: Errors must be fixed with INPUT_ALPHABET before loading can continue.\n";
                    break;
                }
                // Load the tape_alphabet
                tape_alphabet.load(definitionFile, valid);
                if (!valid)
                {
                    cout << "\nLOAD ERROR: Errors must be fixed with TAPE_ALPHABET before loading can continue.\n";
                    break;
                }
                // Load the transition_function
                transition_function.load(definitionFile, valid);
                if (!valid)
                {
                    cout << "\nLOAD ERROR: Errors must be fixed with TRANSITION_FUNCTION before loading can continue.\n";
                    break;
                }

                // Load in the initial_state
                definitionFile >> line;
                if (all_states.is_element(line))
                    initial_state = line;
                else
                {
                    cout << "\nINITIAL_STATE ERROR: Initial state '" << line << "' does not exist in 'STATES:'.\n";
                    valid = false;
                }
                if ((!(definitionFile >> line)) ||
                    (uppercase(line) != "BLANK_CHARACTER:"))
                {
                    cout << "\nINITIAL_STATE ERROR: Missing keyword 'BLANK_CHARACTER:' after initial state.\n";
                    valid = false;
                }
                if (!valid)
                {
                    cout << "\nLOAD ERROR: Errors must be fixed with INITIAL_STATE before loading can continue.\n";
                    break;
                }
                // Load in the blank_character
                tape.load(definitionFile, valid);
                if (!valid)
                {
                    cout << "\nLOAD ERROR: Errors must be fixed with BLANK_CHARACTER before loading can continue.\n";
                    break;
                }
                // Load in the final_states
                final_states.load(definitionFile, valid);
                if (!valid)
                {
                    cout << "\nLOAD ERROR: Errors must be fixed with FINAL_STATES before loading can succeed.\n";
                    break;
                }
            }
        }
        // Validate the contents of the definition file
        tape.validate(tape_alphabet, input_alphabet, valid);
        input_alphabet.validate(tape_alphabet, valid);
        final_states.validate(all_states, valid);
        transition_function.validate(tape_alphabet, all_states, final_states, valid);
        
        if (valid)
        {
            cout << "Definition file '" << defFilename << "' loaded successfully!";
        }
        else
        {
            cout << "Definition file '" << defFilename << "' loading failed!";
        }
    }

    /* Input string file check section */
    string strFilename = definition_file_name;
    strFilename.append(".str");
    ifstream inputFile(strFilename);
    string line;

    
    if (!inputFile)
    {
        cout << "ERROR: THE INPUT STRING FILE '" << strFilename << "' COULD NOT BE OPENED!\n" << "Check file name and/or read permissions\n" << endl;
        valid = false;
    }
    else if((inputFile.peek() == std::ifstream::traits_type::eof()))
    {
        cout << "ERROR: THE INPUT STRING FILE '" << strFilename << "' IS EMPTY!" << endl;
        valid = false;
    }
    
    while (getline(inputFile, line))
    {
        input_strings.push_back(line);
    }
    vector<string> alteredInputStrings;
    bool validString = false;
    for (int x = 0; x < input_strings.size(); ++x)
    {
        if ((input_strings[x].size == 1) && (input_strings[x][0] == '\\'))
        {
            alteredInputStrings.push_back("");
        }
        else if (input_strings[x].size == 0)
        {
            continue;
        }
        else
        {
            for (int y = 0; y < input_strings[x].size(); ++y)
            {
                if (!input_alphabet.is_element(input_strings[x][y]))
                {
                    validString = false;
                    break;
                }
                validString = true;
            }
            if (validString)
            {
                alteredInputStrings.push_back(input_strings[x]);
            }
        }
    }
    // TODO: REMOVE DUPLICATE INPUT STRINGS
    input_strings = alteredInputStrings;
    if (valid)
    {
        cout << "Input String file '" << strFilename << "' loaded successfully!";
    }
    else
    {
        cout << "Input String file '" << strFilename << "' loading failed!";
    }
}

void Turing_Machine::view_definition() const
{
}

void Turing_Machine::view_instantaneous_description(int maximum_number_of_cells) const
{
}

void Turing_Machine::initialize(string input_string)
{
    original_input_string = input_string;
}

void Turing_Machine::perform_transitions(int maximum_number_of_transitions)
{
}

void Turing_Machine::terminate_operation()
{
}

string Turing_Machine::input_string() const
{
    return string();
}

int Turing_Machine::total_number_of_transitions() const
{
    return 0;
}

bool Turing_Machine::is_valid_definition() const
{
    return valid;
}

bool Turing_Machine::is_valid_input_string(string value) const
{
    for (int x = 0; x < value.size(); x++)
    {
        if (!(input_alphabet.is_element(value[x])))
        {
            return false;
        }
    }
    return true;
}

bool Turing_Machine::is_used() const
{
    return used;
}

bool Turing_Machine::is_operating() const
{
    return operating;
}

bool Turing_Machine::is_accepted_input_string() const
{
    return accepted;
}

bool Turing_Machine::is_rejected_input_string() const
{
    return rejected;
}

// Function for checking if a file is empty
bool is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}