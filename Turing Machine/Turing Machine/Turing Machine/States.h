#ifndef States_h
#define States_h
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class States {
    private:
        vector<string>names;
    public:
        void load(ifstream& definition, bool& valid);
        void view() const;
        bool is_element(string value) const;
};
#endif // !States_h
