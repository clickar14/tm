#include "Turing_Machine.h"
#include <iostream>
#include <string>

#define UL "\033[4m"
#define ULD "\033[0m"
using namespace std;

int main(int argc, char* argv[]) {
    string fileName(argv[1]);
    
    bool validTuringMachine = true;
    Turing_Machine turing_machine = Turing_Machine(fileName);

    // Check Turing machine definition file, returns true if file is valid
    // runTuringMachine = readTMDef(fileName);

    string input;
    char command;
    int maxTrans = 1;

    // If both files loaded successfully, continue to command menu.
    while (turing_machine.is_valid_definition()) {
        cout << "\nCommand: ";
        getline(cin, input);
        // If input is a single charecter
        if (input.length() == 1) {
            // Extract input character.
            command = input[0];

            // Menu cases:
            switch (command) {
            case 'D':
            case 'd':
                // Delete
                cout << "Delete Input String: 3" << endl;
                break;
            case 'X':
            case 'x':
                // Exit
                // If successfully saves input string file correctly
                if (true) {
                    cout << "Success!" << endl;
                }

                else {
                    cout << "Failure!" << endl;
                }
                validTuringMachine = false;
                break;
            case 'H':
            case 'h':
                // Help
                cout << "  " << UL << "D" << ULD << "elete\t Delete input string from list" << endl;
                cout << "  E" << UL << "x" << ULD << "it\t\t Exit application" << endl;
                cout << "  " << UL << "H" << ULD << "elp\t\t Help user" << endl;
                cout << "  " << UL << "I" << ULD << "nsert\t Insert input string into list" << endl;
                cout << "  " << UL << "L" << ULD << "ist\t\t List input strings" << endl;
                cout << "  " << UL << "Q" << ULD << "uit\t\t Quit operation of Turing machine on input string" << endl;
                cout << "  " << UL << "R" << ULD << "un\t\t Run Turing machine on input string" << endl;
                cout << "  S" << UL << "e" << ULD << "t\t\t Set maximum number of transitions to perform" << endl;
                cout << "  Sho" << UL << "w" << ULD << "\t\t Show status of application" << endl;
                cout << "  " << UL << "T" << ULD << "runcate\t Truncate instantaneous descriptions" << endl;
                cout << "  " << UL << "V" << ULD << "iew\t\t View Turing Machine" << endl;
                break;
            case 'I':
            case 'i':
                // Insert
                cout << "Input String: AABB" << endl;
                break;
            case 'L':
            case 'l':
                // List
                cout << "1. AABBB" << endl;
                cout << "2. AAB" << endl;
                cout << "3. AABB" << endl;
                break;
            case 'Q':
            case 'q':
                // Quit
                // If turing machine is running on an input string
                if (true) {
                    cout << "Input string not accepted!" << endl;
                    cout << "Total number of transitions performed: 1" << endl;
                    cout << "Input string: AABB" << endl;
                }
                else {
                    cout << "Error, turing machine isn't currently running an input string!" << endl;
                }

                break;
            case 'R':
            case 'r':
                // Run
                cout << "Input string number: 3" << endl;
                cout << "0. [s0]AABB" << endl;
                cout << "1. X[s1]ABB" << endl;
                break;
            case 'E':
            case 'e':
                // Set
                cout << "Maximum number of transitions[1]: 5" << endl;
                cout << "Maximum number of transitions set to 5" << endl;
                break;
            case 'W':
            case 'w':
                // Show

                break;
            case 'T':
            case 't':
                // Truncate
                cout << "Maximum number of cells to left/right of head: <1" << endl;
                break;
            case 'V':
            case 'v':
                // View

                break;
            default:
                // If invalid charecter was entered
                cout << "Invalid command! Type and enter 'h' for a list of available commands." << endl;
                break;
            }
        }
        else if (input.length() > 1)
        {
            cout << "Invalid command! Type and enter 'h' for a list of available commands." << endl;
        }
    }
}