#include "Tape.h"
#include "Input_Alphabet.h"
#include "Tape_Alphabet.h"
#include "Direction.h"
#include <string>
#include <fstream>

using namespace std;

Tape::Tape()
{
}

void Tape::load(ifstream & definition, bool & valid)
{
}

void Tape::validate(const Tape_Alphabet & tape_alphabet, const Input_Alphabet & input_alphabet, bool & valid) const
{
}

void Tape::view() const
{
}

void Tape::initialize(string input_string)
{
}

void Tape::update(char write_character, direction move_direction)
{
}

string Tape::left(int maximum_number_of_cells) const
{
    return string();
}

string Tape::right(int maximum_number_of_cells) const
{
    return string();
}

char Tape::current_character() const
{
    return 0;
}

bool Tape::is_first_cell() const
{
    return false;
}
