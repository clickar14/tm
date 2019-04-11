#include "Tape.h"
#include "Input_Alphabet.h"
#include "Tape_Alphabet.h"
#include "Direction.h"
#include "Uppercase.h"
#include "Crash.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>


using namespace std;

Tape::Tape():
    all_cells(" "),
    current_cell(0),
    blank_character(' ')
{
   
}

void Tape::load(ifstream & definition, bool & valid)
{
    string value;
    if((definition >> value) && (value.length() == 1) && (value[0] != '\\') && (value[0] != '[') && (value[0] != ']') && (value[0] != '<') && (value[0] != '>') && (value[0] != '!') && (value [0] != '~'))
        blank_character = value[0];
    else
    {
        cout << "Illegal blank character. \n";
        valid = false;
    }
    if ((!(definition >> value)) ||
        (uppercase(value) != "FINAL_STATES:"))
    {
        cout << "Missing keyword after blank character.\n";
        valid = false;
    }
}

void Tape::validate(const Tape_Alphabet & tape_alphabet, const Input_Alphabet & input_alphabet, bool & valid) const
{
    if (input_alphabet.is_element(blank_character))
    {
        cout << "Blank character " << blank_character << " is in input alphabet.\n";
        valid = false;
    }
    if (!tape_alphabet.is_element(blank_character))
    {
        cout << "Blank character " << blank_character << " is not in tape alphabet.\n";
        valid = false;
    }
}

void Tape::view() const
{
    cout << "B = " << blank_character << "\n\n";
}

void Tape::initialize(string input_string)
{
    all_cells = input_string + blank_character;
    current_cell = 0;
}

/* DELETE LATER
BAD_ALLOC is derived from the base class Exception
main prog example
#include "Tape.h"
#include "Direction.h"
#include <exception>
#include <string>
#include <iostream>
using namespace std;

int main(){
    const int success(0);
    Tape tape;
    tape.initialize("AABB");
    try
    {
        tape.update('B','L');
    }
    catch(exception& error)
    {
        cout << error.what() << ".\n";
    }
    tape.view()
    return success;
}
*/

void Tape::update(char write_character, direction move_direction)
{
    // If attempting to move left and at start at tape return.
    move_direction = uppercase(move_direction);
    if ((move_direction == 'L') && (current_cell == 0))
        throw crash("Left move from first cell");
    //Append blank character to end of cells if at the end and attempting to move right
    if ((move_direction == 'R') && (current_cell == all_cells.length() - 1))
        all_cells += blank_character;
    // Write the character to the current cell.
    all_cells[current_cell] = write_character;
    // If you moved left decrement the index.
    if (move_direction == 'L')
        --current_cell;
    // If you moved right increment the index.
    else
        ++current_cell;
}
// Returns the cells to the left of the current cell depending on the max cell number.
string Tape::left(int maximum_number_of_cells) const
{
    int firstCell = max(0, current_cell - maximum_number_of_cells);
    string value = all_cells.substr(firstCell, current_cell - firstCell);
    if (value.length() < current_cell)
        value.insert(0, "<");
    return value;
    
}
// Returns the cells to the right of the current cell depending on the max cell number.
string Tape::right(int maximum_number_of_cells) const
{
    int endCell = all_cells.length() - 1;
    while ((endCell >= current_cell) && all_cells[endCell] == blank_character))
        --endCell;
    int lastCell = min(endCell, current_cell + maximum_number_of_cells - 1);
    string value = all_cells.substr(current_cell, lastCell - current_cell + 1);
    if (value.length() < endCell - current_cell + 1)
        value.append(">");
    return value;
}
// Returns the character stored in the current cell.
char Tape::current_character() const
{
    return all_cells[current_cell];
}
// Checks if the current cell is the first cell of the tape.
bool Tape::is_first_cell() const
{
    return (current_cell == 0);
}
