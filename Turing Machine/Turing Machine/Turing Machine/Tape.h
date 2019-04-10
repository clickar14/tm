#ifndef Tape_h
#define Tape_h

#include "Input_Alphabet.h"
#include "Tape_Alphabet.h"
#include "Direction.h"
#include <string>
#include <fstream>

using namespace std;
class Tape
{
    private:
        string all_cells;
        int current_cell;
        char blank_character;
    public:
        Tape();
        void load(ifstream& definition, bool& valid);
        void validate(const Tape_Alphabet& tape_alphabet, const Input_Alphabet& input_alphabet, bool& valid) const;
        void view() const;
        void initialize(string input_string);
        void update(char write_character, direction move_direction);
        string left(int maximum_number_of_cells) const;
        string right(int maximum_number_of_cells) const;
        char current_character() const;
        bool is_first_cell() const;
};
#endif // !Tape_h
