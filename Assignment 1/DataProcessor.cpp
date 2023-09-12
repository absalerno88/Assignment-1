#include "DataProcessor.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;


DataProcessor::DataProcessor() : currentIndex(0) {
    // Initialize array with zeros
    for (int i = 0; i < 200; i++) {
        array[i] = 0;
    }
}

void DataProcessor::readFromFile(const char* filename) {
    ifstream file(filename);
    int value;
    if (file.is_open()) {
        while (file >> value && currentIndex < 100) {
            array[currentIndex++] = value;
        }

        // Check if the stream is in a fail state and it's not due to EOF
        if (file.fail() && !file.eof()) {
            cerr << "Error reading file. Possibly non-integer data encountered." << endl;
        }

        file.close();
    } else {
        cerr << "Failed to open the file." << endl;
    }
}

int DataProcessor::integerExists(int value) {
    for (int i = 0; i < currentIndex; i++) {
        if (array[i]  == value) {
            return i;
        }
    }
    return -1; // Indicates that the int does not exist
}

void DataProcessor::modifyValue(int idx, int newValue, int &oldValue) {
    if (idx < 0 || idx >= currentIndex) {
        throw out_of_range("Index out of range.");
    }
    oldValue = array[idx];
    array[idx] = newValue;
}

void DataProcessor::addInteger(int value) {
    if (currentIndex >= 200) {
        throw length_error("Array is full.");
    }
    array[currentIndex++] = value;
}

void DataProcessor::replaceOrRemove(int idx, bool shouldRemove) {
    if (idx < 0 || idx >= currentIndex) {
        throw out_of_range("Index out of range.");
    }

    if (shouldRemove) {
        for (int i = idx; i < currentIndex - 1; i++) {
            array[i] = array[i + 1];
        }
        currentIndex--;
        array[currentIndex] = 0; // Resetting the value at the new "last" position
    } else {
        array[idx] = 0;
    }
}

void DataProcessor::displayArray() const {
    if (currentIndex == 0) {
        cout << "The array is empty." << endl;
        return;
    }

    cout << "Current data in the array:" << endl;
    for (int i = 0; i < currentIndex; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int getIntegerInput(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer." << endl;
        } else {
            break;
        }
    }
    return val;
}

int DataProcessor::getCurrentIndex() const {
    return currentIndex;
}


int main() {
    DataProcessor processor;

    // Read data from a file
    const char* filename = "data.txt"; // Assuming the file is named 'data.txt'
    processor.readFromFile(filename);

    // Menu-driven application for easy usability
    int choice = 0;
    while (choice != 6) { // Option to exit program
        cout << "\nMenu:\n";
        cout << "1. Check if integer exists in the array.\n";
        cout << "2. Modify value of an integer by index.\n";
        cout << "3. Add a new integer to the array.\n";
        cout << "4. Replace or remove an integer by index.\n";
        cout << "5. Display current data in array.\n";
        cout << "6. Exit.\n";

        do {
            cout << "Enter your choice: --> ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard the rest of the line

            if (cin.fail()) {
            cin.clear();  // Clear the failure state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard bad input
            cout << "Invalid input. Please enter a number 1-6." << endl;
            } else {
                break;  // Exit the loop if a valid input is provided
            }
        } while (true);

        try {
            switch (choice) {
                case 1:{
                    int val;
                    val = getIntegerInput("Enter integer to check: ");

                    int idx = processor.integerExists(val);
                    if (idx != -1) {
                        cout << "Integer found at index: " << idx << endl;
                    } else {
                        cout << "Integer not found in the array." << endl;
                    }
                    break;
                }
                case 2: {
                    int idx, newVal, oldVal;
                    do {
                        cout << "Enter index of integer to modify: ";
                        cin >> idx;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard the rest of the line

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a valid index." << endl;
                        } else {
                            break;
                        }
                    } while (true);

                    newVal = getIntegerInput("Enter new value: ");

                    processor.modifyValue(idx, newVal, oldVal);
                    cout << "Value at index " << idx << " changed from " << oldVal << " to " << newVal << endl;
                    break;
                }
                case 3: {
                    int val;

                    val = getIntegerInput("Enter integer to add: ");

                    processor.addInteger(val);
                    cout << "Integer added successfully." << endl;
                    break;
                }
                case 4: {
                    int idx;
                    char decision;

                    do {
                        cout << "Enter index of integer: ";
                        cin >> idx;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard the rest of the line

                        if (cin.fail() || idx < 0 || idx >= processor.getCurrentIndex()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a valid index." << endl;
                        } else {
                            break;
                        } 
                    } while (true);

                    do {
                        cout << "Replace with 0 (R) or remove (D)? (R/D): ";
                        cin >> decision;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard the rest of the line

                        if (cin.fail() || (decision != 'R' && decision != 'D' && decision != 'r' && decision != 'd')) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid choice. Please select R or D." << endl;
                        } else {
                            break;
                        }
                    } while (true);

                    if (decision =='D' || decision == 'd') {
                        processor.replaceOrRemove(idx, true);
                    } else if (decision == 'R' || decision == 'r') {
                        processor.replaceOrRemove(idx, false);
                    }
                    cout << "Operation successful." << endl;
                    break;
                }
                case 5: {
                    //Display function
                    processor.displayArray();
                    break;
                }
                case 6: {
                    cout << "Goodbye!" << endl;
                    break;
                }
                default: {
                    cout << "Invalid choice. Please choose a valid option." << endl;
                }
            }
        // Error handling
        } catch (ios_base::failure& f) {
            cerr << "Invalid number format input\n"; 
        } catch (exception& ex) {
            cerr << "An error occurred: " << ex.what() << endl;
        } catch (...) {
            cerr << "An unknown error occurred.\n";
        }
    }

    return 0;
}
