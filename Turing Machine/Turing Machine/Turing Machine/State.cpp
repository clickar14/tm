#include "State.h"
#include "String_pointer.h"
#include <string>

using namespace std;

int State::number_of_states = 0;

/* Testing main
#include "State,h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
    const int success = 0;
    string name;
    State x;
    State y = "s2";
    State z = y;
    state_pointer p = new State(z);
    x = *p;
    delete p;
    x.get_name(name);
    cout << "Name of state x is " << name << ".\n";
    the state::total_numb is how you should call the value of total number of states.
    cout << "Total number of states is " << State::total_number_of_states() << ".\n";
    return success;
 */

State::State()
{
    name = new string;
    ++number_of_states;
}

State::State(string state_name)
{
    name = new string(state_name);
    ++number_of_states;
}

State::State(const State& state)
{
    name = new string(*state.name);
    ++number_of_states;
}

State::~State()
{
    delete name;
    --number_of_states;
}

State& State::operator=(const State& state)
{
    if (this != &state)
    {
        *name = *state.name;
    }
    return *this;
}

void State::get_name(string& state_name) const
{
    state_name = *name;
}

void State::set_name(string state_name)
{
    *name = state_name;
}
int State::total_number_of_states()
{
    return number_of_states;
}


