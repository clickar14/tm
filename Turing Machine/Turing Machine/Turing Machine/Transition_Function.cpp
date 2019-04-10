#include "Transition_Function.h"
#include "Transition.h"
#include "Tape_Alphabet.h"
#include "States.h"
#include "Final_States.h"
#include "Direction.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

void Transition_Function::load(ifstream& definition, bool& valid)
{

}
void Transition_Function::validate(const Tape_Alphabet& tape_alphabet, const States& all_states, const Final_States& final_states, bool& valid) const
{
    for (unsigned int index = 0; index < all_transitions.size(); ++index)
    {
        if (final_states.is_element(all_transitions[index].source_state()))
        {
            cout << "Source state" << all_transitions[index].source_state() << "is in final states." << endl;
            valid = false;
        }
        if (!all_states.is_element(all_transitions[index].source_state()))
        {
            cout << "Source state " << all_transitions[index].source_state() << "is not in states. \n";
            valid = false;
        }
        if (!tape_alphabet.is_element(all_transitions[index].read_character()))
        {
            cout << "The read character " << all_transitions[index].read_character() << "is not in the tape alphabet. \n";
            valid = false;
        }
        if (!all_states.is_element(all_transitions[index].destination_state()))
        {
            cout << "Destination " << all_transitions[index].destination_state() << "is not in states. /n";
            valid = false;
        }
        if (!tape_alphabet.is_element(all_transitions[index].write_character()))
        {
            cout << "Write character " << all_transitions[index].write_character() << "is not in the tape alphabet. \n";
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