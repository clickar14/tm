#include "Turing_Machine.h"
#include <iostream>
#include <string>

#define UL "\033[4m"
#define ULD "\033[0m"
using namespace std;

// TODO: Go through and add additional comments to functions.

int main(int argc, char* argv[]) {
    string fileName(argv[1]);
    
    // Load in the turing machine.
    Turing_Machine turing_machine = Turing_Machine(fileName);

   
    char command;
    int maxTrans = 1;
    string inputString, input;
    int maximum_number_of_transitions = 1;
    int maximum_number_of_cells = 32;

    // If both files loaded successfully, continue to command menu.
    while (turing_machine.is_valid_definition()) {
        cout << "\nCommand: ";
        getline(cin, input);
        cout << endl;

        // If input is a single charecter
        if (input.length() == 1) {
            // Extract input character.
            command = input[0];

            // Menu cases:
            switch (command) {
            case 'D':
            case 'd':
                // Deletes the designated input string from the input list.
                int stringToDelete;
                cout << "Delete Input String: ";
                cin >> stringToDelete;
                turing_machine.delete_input_string(stringToDelete);
                cin.ignore();
                break;
            case 'X':
            case 'x':
                // Exit
                // If successfully saves input string file correctly
                if (!turing_machine.is_input_changed())
                {
                    turing_machine.save_input_strings();
                }
                cout << "Exiting application...\n";
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
                cout << "Input String: ";
                cin >> inputString;
                if (turing_machine.is_valid_input_string(inputString))
                {
                    cout << "String '" << inputString << "' was successfully loaded into strings list!\n";
                }
                else
                {
                    cout << "Discarding input string...\n";
                }
                cin.ignore();
                break;
            case 'L':
            case 'l':
                // List
                turing_machine.view_input_strings();
                break;
            case 'Q':
            case 'q':
                // TODO: Quit
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
                // TODO: Run
                int stringNumber;
                if (!turing_machine.is_operating())
                {

                    cout << "Input string number: ";
                    cin >> stringNumber;
                    turing_machine.initialize(stringNumber);
                    turing_machine.perform_transitions();
                    cout << "0. [s0]AABB" << endl;
                    cout << "1. X[s1]ABB" << endl;
                    cin.ignore();
                }
                else
                {

                }
                break;
            case 'E':
            case 'e':
                // TODO: Set
                cout << "Maximum number of transitions[1]: 5" << endl;
                cout << "Maximum number of transitions set to 5" << endl;
                break;
            case 'W':
            case 'w':
                //TODO: Show

                break;
            case 'T':
            case 't':
                // TODO: Truncate
                cout << "Maximum number of cells to left/right of head: <1" << endl;
                break;
            case 'V':
            case 'v':
                // TODO: View

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