#ifndef Tape_Alphabet_h
#define Tape_Alphabet_h
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Tape_Alphabet
{
    private:
        vector<char>alphabet;
    public:
    void load(ifstream& definition, bool& valid);
    void view() const;
    bool is_element(char value) const;
};
#endif // !
