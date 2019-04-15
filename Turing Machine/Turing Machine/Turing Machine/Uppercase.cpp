#include "Uppercase.h"
#include "Direction.h"
#include <string>
#include <algorithm>
using namespace std;
string uppercase(string input)
{
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    return input;
}
string uppercase(direction input)
{
    input = toupper(input);
    string returnVal = { input };
    return returnVal;
}