#include "Transition_Function.h"
#include "Transition.h"
#include "Tape_Alphabet.h"
#include "States.h"
#include "Final_States.h"
#include "Direction.h"
#include "Uppercase.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

void Transition_Function::load(ifstream& definition, bool& valid)
{
    string value;

    if ((!(definition >> value)) || ((uppercase(value) == "INITIAL_STATE:")))
    {
        cout << "\nTRANSITION_FUNCTION ERROR: There are no transitions defined in the TRANSITION_FUNCTION.\n";
        valid = false;
        return;
    }
    while (true)
    {
        string source, destination;
        char read, write;
        direction move;
        bool isCheck = true, readCheck = true, dsCheck = true, writeCheck = true, moveCheck = true;
        // Check if valid state
        for (int x = 0; x < value.size(); x++)
        {
            if ((isalpha(value[x])) || (isdigit(value[x])) || (value[x] == '_'))
            {
                isCheck = true;
                break;
            }
            isCheck = false;
        }
        // Store the source state
        if (!isCheck)
        {
            cout << "\nTRANSITION_FUNCTION ERROR: The source state '" << value << "' contains invalid characters.\n";
            cout << "State names may only contain letters, numbers, and underscores!\n";
            valid = false;
        }
        else
        {
            source = value;
        }
        // Function Entry Check
        if (!(definition >> value) || (uppercase(value) == "INITIAL_STATE:"))
        {
            cout << "\nTRANISTION_FUNCTION ERROR: Incomplete transition described at transition_function entry '" << all_transitions.size() + 1 << "'.\n";
            cout << "Please make sure the transition entry contains a source_state, read character, destination_state, write_character, and direction.\n";
            valid = false;
            return;
        }
        // Check if read character is valid
        if ((value.size() == 1) && (value[0] != '\\') && (value[0] != '[') && (value[0] != ']') && (value[0] != '<') && (value[0] != '>') && (value[0] != '!') && (value[0] != '~'))
            read = value[0];
        else
        {
            cout << "\nTRANSITION_FUNCTION ERROR: Illegal read character '" << value[0] << "'.\n";
            valid = false;
            readCheck = false;
        }
        // Function Entry Check
        if (!(definition >> value) || (uppercase(value) == "INITIAL_STATE:"))
        {
            cout << "\nTRANISTION_FUNCTION ERROR: Incomplete transition described at transition_function entry '" << all_transitions.size() + 1 << "'.\n";
            cout << "Please make sure the transition entry contains a source_state, read character, destination_state, write_character, and direction.\n";
            valid = false;
            return;
        }
        // Check if destination state is valid
        for (int x = 0; x < value.size(); x++)
        {
            if ((isalpha(value[x])) || (isdigit(value[x])) || (value[x] == '_'))
            {
                dsCheck = true;
                break;
            }
            dsCheck = false;
        }
        // Store the source state
        if (!dsCheck)
        {
            cout << "\nTRANSITION_FUNCTION ERROR: The destination state '" << value << "' contains invalid characters.\n";
            cout << "State names may only contain letters, numbers, and underscores!\n";
            valid = false;
        }
        else
        {
            destination = value;
        }
        // Function Entry Check
        if (!(definition >> value) || (uppercase(value) == "INITIAL_STATE:"))
        {
            cout << "\nTRANISTION_FUNCTION ERROR: Incomplete transition described at transition_function entry '" << all_transitions.size() + 1 << "'.\n";
            cout << "Please make sure the transition entry contains a source_state, read character, destination_state, write_character, and direction.\n";
            valid = false;
            return;
        }
        // Check if write character is valid
        if ((value.size() == 1) && (value[0] != '\\') && (value[0] != '[') && (value[0] != ']') && (value[0] != '<') && (value[0] != '>') && (value[0] != '!') && (value[0] != '~'))
            write = value[0];
        else
        {
            cout << "\nTRANSITION_FUNCTION ERROR: Illegal write character '" << value[0] << "'.\n";
            valid = false;
            writeCheck = false;
        }
        // Function Entry Check
        if (!(definition >> value) || (uppercase(value) == "INITIAL_STATE:"))
        {
            cout << "\nTRANISTION_FUNCTION ERROR: Incomplete transition described at transition_function entry '" << all_transitions.size() + 1 << "'.\n";
            cout << "Please make sure the transition entry contains a source_state, read character, destination_state, write_character, and direction.\n";
            valid = false;
            return;
        }
        // Check if direction character is valid
        if ((value.size() == 1) && ((uppercase(value[0])[0] == 'L') || ((uppercase(value[0])[0] == 'R'))))
            move = value[0];
        else
        {
            cout << "\nTRANSITION_FUNCTION ERROR: Illegal direction character '" << value[0] << "'.\n";
            cout << "Please make sure that the move direction is either 'L' or 'R'";
            valid = false;
            moveCheck = false;
        }
        // If all checks passed insert into all_tranistions
        if (moveCheck && writeCheck && dsCheck && isCheck && readCheck)
        {
            all_transitions.push_back(Transition(source, read, destination, write, move));
        }
        else
        {
            cout << "\nTRANISTION_FUNCTION ERROR: Incomplete or invalid transition described at transition_function entry '" << all_transitions.size() + 1 << "'.\n";
            cout << "Please make sure the transition entry contains a source_state, read character, destination_state, write_character, and direction in that order.\n";
            valid = false;
        }
        if ((!(definition >> value)))
        {
            cout << "\nTRANSITION_FUNCTION ERROR: Reached EOF before reading the next keyword 'INITIAL_STATE:'. \n";
            valid = false;
            return;
        }
        if  (uppercase(value) == "INITIAL_STATE:")
        {
            return;
        }
    }
}
void Transition_Function::validate(const Tape_Alphabet& tape_alphabet, const States& all_states, const Final_States& final_states, bool& valid) const
{
    for (unsigned int index = 0; index < all_transitions.size(); ++index)
    {
        if (final_states.is_element(all_transitions[index].source_state()))
        {
            cout << "\nTRANSITION_FUNCTION VALIDATION ERROR: Source state" << all_transitions[index].source_state() << "is in final states." << endl;
            valid = false;
        }
        if (!all_states.is_element(all_transitions[index].source_state()))
        {
            cout << "\nTRANSITION_FUNCTION VALIDATION ERROR: Source state " << all_transitions[index].source_state() << "is not in states. \n";
            valid = false;
        }
        if (!tape_alphabet.is_element(all_transitions[index].read_character()))
        {
            cout << "\nTRANSITION_FUNCTION VALIDATION ERROR: The read character " << all_transitions[index].read_character() << "is not in the tape alphabet. \n";
            valid = false;
        }
        if (!all_states.is_element(all_transitions[index].destination_state()))
        {
            cout << "\nTRANSITION_FUNCTION VALIDATION ERROR: Destination " << all_transitions[index].destination_state() << "is not in states. /n";
            valid = false;
        }
        if (!tape_alphabet.is_element(all_transitions[index].write_character()))
        {
            cout << "\nTRANSITION_FUNCTION VALIDATION ERROR: Write character " << all_transitions[index].write_character() << "is not in the tape alphabet. \n";
            valid = false;
        }
    }
}
void Transition_Function::view() const 
{

}
void Transition_Function::find_transition(
    string source_state,
    char read_character,
    string& destination_state,
    char& write_character,
    direction& move_direction,
    bool& found) const
{
    for (unsigned int index = 0; index < all_transitions.size(); ++index) 
    {
        if ((all_transitions[index].source_state() == source_state) && all_transitions[index].read_character() == read_character)
        {
            destination_state = all_transitions[index].destination_state();
            write_character = all_transitions[index].write_character();
            move_direction = all_transitions[index].move_direction();
            found = true;
            return;
        }
        found = false;
    }
}