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

Turing_Machine::Turing_Machine(string definition_file_name)
{
    valid = true;
    tape = Tape();
    string defFilename = definition_file_name;
    defFilename.append(".def");
    ifstream definitionFile(defFilename);
    bool fileOpenCheck = true;
    /* Definition file checks */
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

                // Load the input_alphabet
                input_alphabet.load(definitionFile, valid);

                // Load the tape_alphabet
                tape_alphabet.load(definitionFile, valid);

                // Load the transition_function
                transition_function.load(definitionFile, valid);

                definitionFile >> line;
                // Load in the initial_state
                if ((line[line.size() - 1] == ':'))
                {
                    cout << "INITIAL_STATE ERROR: Encountered unexpected keyword '" << line << "' instead of a valid initial state.\n";
                    valid = false;
                }
                else
                {
                    if (all_states.is_element(line))
                        initial_state = line;
                    else
                    {
                        cout << "\nINITIAL_STATE ERROR: Initial state '" << line << "' does not exist in 'STATES:'.\n";
                        valid = false;
                    }
                }
                if ((!(definitionFile >> line)) ||
                    (uppercase(line) != "BLANK_CHARACTER:"))
                {
                    cout << "\nINITIAL_STATE ERROR: Missing keyword 'BLANK_CHARACTER:' after initial state.\n";
                    valid = false;
                }
                // Load in the blank_character
                tape.load(definitionFile, valid);

                // Load in the final_states
                final_states.load(definitionFile, valid);

            }
        }
        // Validate the contents of the definition file
        if (valid)
        {
            tape.validate(tape_alphabet, input_alphabet, valid);
            input_alphabet.validate(tape_alphabet, valid);
            final_states.validate(all_states, valid);
            transition_function.validate(tape_alphabet, all_states, final_states, valid);
        }
        
        if (valid)
        {
            cout << "Definition file '" << defFilename << "' loaded successfully!";
        }
        else
        {
            cout << "Definition file '" << defFilename << "' loading failed!";
        }
        // Initialize boolean flags
        used = false;
        operating = false;
        accepted = false;
        rejected = false;
    }

    /* Input string file check section */
    string strFilename = definition_file_name;
    strFilename.append(".str");
    inputFileName = strFilename;
    ifstream inputFile(strFilename);
    string line;

    if (!inputFile)
    {
        cout << "ERROR: THE INPUT STRING FILE '" << strFilename << "' COULD NOT BE OPENED!\n" << "Check file name and/or read permissions\n" << endl;
        cout << "\nInput String file '" << strFilename << "' loading failed!\n";
        valid = false;
        return;
    }
    else if((inputFile.peek() == std::ifstream::traits_type::eof()))
    {
        cout << "ERROR: THE INPUT STRING FILE '" << strFilename << "' IS EMPTY!" << endl;
        cout << "\nInput String file '" << strFilename << "' loading failed!\n";
        valid = false;
        return;
    }
    
    while (getline(inputFile, line))
    {
        original_input_strings.push_back(line);
    }
    bool validString = false;
    for (int x = 0; x < original_input_strings.size(); ++x)
    {
        if ((original_input_strings[x].size() == 1) && (original_input_strings[x][0] == '\\'))
        {
            input_strings.push_back("");
        }
        else if (original_input_strings[x].size() == 0)
        {
            continue;
        }
        else
        {
            for (int y = 0; y < original_input_strings[x].size(); ++y)
            {
                if (!input_alphabet.is_element(original_input_strings[x][y]))
                {
                    validString = false;
                    break;
                }
                validString = true;
            }
            if (validString)
            {
                input_strings.push_back(original_input_strings[x]);
            }
        }
    }
    // Remove the duplicate strings and save to input_strings
    sort(input_strings.begin(), input_strings.end());
    sort(original_input_strings.begin(), original_input_strings.end());
    input_strings.erase(unique(input_strings.begin(), input_strings.end()), input_strings.end());

    if (valid)
    {
        cout << "\nInput String file '" << strFilename << "' loaded successfully!\n";
        inputFile.close();
        definitionFile.close();
    }
    
}
/*This function displays the description provided at the head of the definition file
  by sending it to standard output.*/
void Turing_Machine::view_definition() const
{
    for (int x = 0; x < description.size(); x++)
    {
        cout << description[x];
    }
}
//TODO: Finish
void Turing_Machine::view_instantaneous_description(int maximum_number_of_cells) const
{
}
//TODO: Finish
void Turing_Machine::view_input_strings() const
{
    for (int x = 0; x < input_strings.size(); ++x)
    {
        cout << x + 1 << ". " << input_strings[x] << endl;
    }
}

//TODO: Finish and add check for used
void Turing_Machine::initialize(int input_selection)
{
    // If the input string selected doesn't exist.
    if (input_strings.size() < input_selection || input_selection < 0)
    {
        cout << "Invalid input string selection!\n";
        return;
    }
    
    // Load the selected input string onto the tape.
    original_input_string = input_strings[input_selection - 1];
    tape.initialize(original_input_string);
    operating = true;

}
//TODO: Finish
void Turing_Machine::perform_transitions(int maximum_number_of_transitions)
{
    if (operating)
    {

    }
}
//TODO: Finish
void Turing_Machine::terminate_operation()
{
}

void Turing_Machine::delete_input_string(int index)
{
    if (index > input_strings.size() || index < 1)
    {
        cout << "Invalid input string selection!\n";
    }
    else
    {
        cout << "Input string '" << input_strings[index - 1] << "' was successfully deleted!\n";
        input_strings.erase(input_strings.begin() + index - 1);
    }
}
void Turing_Machine::save_input_strings()
{
    ofstream inputFile(inputFileName);
    string line;
    if (!inputFile)
    {
        cout << "The input strings file '" << inputFileName << "' could not be saved!\n";
        return;
    }
    for (int x = 0; x < input_strings.size(); ++x)
    {
        inputFile << input_strings[x] << endl;
    }
    cout << "The input string file '" << inputFileName << "' was successfully saved!\n";
    inputFile.close();
}
//TODO: Finish
string Turing_Machine::input_string() const
{
    return original_input_string;
}
//TODO: Finish
int Turing_Machine::total_number_of_transitions() const
{
    return number_of_transitions;
}

bool Turing_Machine::is_input_changed() const
{
    if (input_strings == original_input_strings)
    {
       return true;
    }
    else
    {
       return false;
    }
}

bool Turing_Machine::is_valid_definition() const
{
    return valid;
}

bool Turing_Machine::is_valid_input_string(string value)
{
    for (int x = 0; x < input_strings.size(); ++x)
    {
        if (input_strings[x] == value)
        {
            cout << "String '" << value << "' is already in the input_strings list!\n";
            return false;
        }
    }
    for (int x = 0; x < value.size(); x++)
    {

        if (!(input_alphabet.is_element(value[x])))
        {
            cout << "String '" << value << "' contains characters not found in the input_alphabet!\n";
            return false;
        }
    }
    input_strings.push_back(value);
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