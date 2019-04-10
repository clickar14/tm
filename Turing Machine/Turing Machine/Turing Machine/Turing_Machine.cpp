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

using namespace std;

Turing_Machine::Turing_Machine(string definition_file_name)
{
    string defFilename = definition_file_name;
    defFilename.append(".def");
    string strFilename = definition_file_name;
    strFilename.append(".str");
    ifstream definitionFile(defFilename);
    ifstream inputFile(strFilename);
    if (!definitionFile)
    {
        cout << "Error opening definition file '" << defFilename << "'\n" << "Check file name and/or read permissions\n" << "Exiting..." << endl;
        exit(0);
    }
    if (!inputFile) 
    {
        cout << "Error opening input file '" << strFilename << "'\n" << "Check file name and/or read permissions\n" << "Exiting..." << endl;
        exit(0);
    }
    // Pick up from here
    vector<string> definitionFileContents;
    string line;
    // Def file contents into vector
    while (getline(definitionFile, line)) 
    {
        definitionFileContents.push_back(line);
    }
    // Check if the file has content
    if(definitionFileContents.size < 2)
}

void Turing_Machine::view_definition() const
{
}

void Turing_Machine::view_instantaneous_description(int maximum_number_of_cells) const
{
}

void Turing_Machine::initialize(string input_string)
{
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
    return false;
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
