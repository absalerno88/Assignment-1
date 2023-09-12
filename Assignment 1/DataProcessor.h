#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

class DataProcessor {
private:
    int array[200];
    int currentIndex; // Track the last filled position in the array.

public:
    // Constructor
    DataProcessor();

    // Function to read data from a file into the array
    void readFromFile(const char* filename);

    // Function to check if a certain integer exists in the array
    int integerExists(int value);

    // Function to modify the value of an integer
    void modifyValue(int idx, int newValue, int &oldValue);

    // Function to add a new integer to the end of the array
    void addInteger(int value);

    // Function which intakes an index of an array and replaces the value with 0 or removes the integer altogether
    void replaceOrRemove(int idx, bool shouldRemove);

    // Function to display the current data in the array
    void displayArray() const;

    // Getter
    int getCurrentIndex() const;

};

#endif // DATA_PROCESSOR_H
