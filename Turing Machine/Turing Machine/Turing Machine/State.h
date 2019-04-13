#ifndef State_h
#define State_h
#include "String_pointer.h"
#include <string>

using namespace std;

class State
{
private:
    string_pointer name;
    static int number_of_states;
public:
    State();
    State(string state_name);
    State(const State& state);
    virtual ~State();
    State& operator=(const State& state);
    void get_name(string& state_name) const;
    void set_name(string state_name);
    static int total_number_of_states();
};
typedef State* state_pointer;
#endif // !State_h
