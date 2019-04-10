#ifndef Input_Alphabet_h
#define Input_Alphabet_h
#include "Tape_Alphabet.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Input_Alphabet
{
    private:
        vector<char>alphabet;
    public:
        void load(ifstream& definition, bool& valid);
        void validate(const Tape_Alphabet& tape_alphabet, bool& valid) const;
        void view() const;
        bool is_element(char value) const;
};
#endif // !Input_Alphabet_h
