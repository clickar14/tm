#ifndef Final_States_h
#define Final_States_h
#include "States.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Final_States {
private:
    vector<string>names;
public:
    void load(ifstream& definition, bool& valid);
    void validate(const States& all_states, bool& valid) const;
    void view() const;
    bool is_element(string value) const;
};
#endif // !Final_States_h
