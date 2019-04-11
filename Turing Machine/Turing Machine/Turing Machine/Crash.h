#ifndef Crash_h
#define Crash_h

#include <stdexcept>
#include <string>

using namespace std;

class crash : public runtime_error
{
    public:
        crash(string reason);
};
#endif // !Crash_h
