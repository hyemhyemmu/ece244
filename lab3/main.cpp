//
//  main.cpp
//  Lab 3 The Resistor Network Program
//
//  Created by Nathan Hung on 2024-09-11.
//  Modified by Salma Emara on 2024-09-30
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Node.h"
#include "Resistor.h"

using namespace std;

Resistor** resistors =
    nullptr;  // Pointer that should point to an array of Resistor pointers
Node* nodes = nullptr;  // pointer that should hold address to an array of Nodes
int maxNodeNumber = 0;  // maximum number of nodes as set in the command line
int maxResistors = 0;  // maximum number of resistors as set in the command line
int resistorsCount = 0;  // count the number of resistors

string errorArray[10] = {
    "invalid command",                                  // 0
    "invalid argument",                                 // 1
    "negative resistance",                              // 2
    "node value is out of permitted range",             // 3
    "resistor name cannot be keyword \"all\"",          // 4
    "both terminals of resistor connect to same node",  // 5
    "too few arguments",                                // 6
};

// Function Prototypes
bool getInteger(stringstream& ss, int& x);
bool getString(stringstream& ss, string& s);
bool getDouble(stringstream& ss, double& s);

void handleMaxVal(stringstream& ss);
void handleInsertR(stringstream& ss);
void handleModifyR(stringstream& ss);
void handlePrintR(stringstream& ss);
void handleDeleteR(stringstream& ss);
void handleSetV(stringstream& ss);

int main() {
  string line;
  string command;

  cout << ">>> ";
  cout.flush();

  // Main loop: read commands until EOF
  while (getline(cin, line)) {
    // Create stringstream from the input line
    stringstream ss(line);

    // Read the command (first word)
    if (!getString(ss, command)) {
      // Empty line, prompt for next command
      cout << ">>> ";
      cout.flush();
      continue;
    }

    // Process the command
    if (command == "maxVal") {
      handleMaxVal(ss);
    } else if (command == "insertR") {
      handleInsertR(ss);
    } else if (command == "modifyR") {
      handleModifyR(ss);
    } else if (command == "printR") {
      handlePrintR(ss);
    } else if (command == "deleteR") {
      handleDeleteR(ss);
    } else if (command == "setV") {
      handleSetV(ss);
    } else if (command == "solve") {
      // TODO: Implement solve command
      cout << "Error: solve not implemented yet" << endl;
    } else {
      // Invalid command
      cout << "Error: " << errorArray[0] << endl;
    }

    // Prompt for next command
    cout << ">>> ";
    cout.flush();
  }

  // Clean up: delete dynamically allocated arrays
  if (resistors != nullptr) {
    for (int i = 0; i < resistorsCount; i++) {
      delete resistors[i];
    }
    delete[] resistors;
  }
  if (nodes != nullptr) {
    delete[] nodes;
  }

  return 0;
}

// function implementations
bool getInteger(stringstream& ss, int& x) {
  ss >> x;
  if (ss.fail()) {
    return false;
  }
  return true;
}

bool getString(stringstream& ss, string& s) {
  ss >> s;
  if (ss.fail()) {
    return false;
  }
  return true;
}

bool getDouble(stringstream& ss, double& d) {
  ss >> d;
  if (ss.fail()) {
    return false;
  }
  return true;
}

// Command handler functions
void handleMaxVal(stringstream& ss) {
  int maxNodes, maxRes;

  // Read maxNodeNumber
  if (!getInteger(ss, maxNodes)) {
    cout << "Error: " << errorArray[1] << endl;
    return;
  }

  // Read maxResistors
  if (!getInteger(ss, maxRes)) {
    cout << "Error: " << errorArray[6] << endl;
    return;
  }

  // Check if maxNodes and maxRes are positive
  if (maxNodes <= 0 || maxRes <= 0) {
    cout << "Error: " << errorArray[1] << endl;
    return;
  }

  // Delete old arrays if they exist
  if (resistors != nullptr) {
    // Delete all resistor objects first
    for (int i = 0; i < resistorsCount; i++) {
      delete resistors[i];
    }
    // Delete the array of pointers
    delete[] resistors;
    resistors = nullptr;
  }

  if (nodes != nullptr) {
    delete[] nodes;
    nodes = nullptr;
  }

  // Update global variables
  maxNodeNumber = maxNodes;
  maxResistors = maxRes;

  // Allocate new arrays
  nodes = new Node[maxNodeNumber];
  resistors = new Resistor*[maxResistors];

  // Initialize resistor pointers to nullptr
  for (int i = 0; i < maxResistors; i++) {
    resistors[i] = nullptr;
  }

  // Initialize resistorsCount to 0
  resistorsCount = 0;

  // Print success message
  cout << "New network: max node number is " << maxNodeNumber
       << "; max resistors is " << maxResistors << endl;
}

void handleInsertR(stringstream& ss) {
  string name;
  double resistance;
  int nodeid1, nodeid2;

  // TODO: Read name, resistance, nodeid1, nodeid2
  if (!getString(ss, name)) {
    cout << "Error: " << errorArray[1] << endl;
    return;
  }

  if (!getInteger(ss, )) {
    cout << "Error: " << errorArray[1] << endl;
    return;
  }
  // TODO: Check for errors in this order:
  //   1. too few arguments
  //   2. invalid argument
  //   3. negative resistance
  //   4. resistor name cannot be keyword "all"
  //   5. resistor name already exists
  //   6. node value is out of permitted range (for both nodes)
  //   7. both terminals of resistor connect to same node
  //   8. resistorsCount >= maxResistors (need space)
  //   9. nodes[nodeid1-1].canAddResistor() and
  //   nodes[nodeid2-1].canAddResistor()
  // TODO: Create new Resistor object with new
  // TODO: Add resistor pointer to resistors array
  // TODO: Call addResistor() on both nodes
  // TODO: Increment resistorsCount
  // TODO: Print success message: "Inserted: resistor name resistance Ohms
  // nodeid1 -> nodeid2"

  cout << "Error: insertR not implemented yet" << endl;
}

void handleModifyR(stringstream& ss) {
  string name;
  double newResistance;

  // TODO: Read name and newResistance
  // TODO: Check for errors:
  //   1. too few arguments
  //   2. invalid argument
  //   3. negative resistance
  //   4. resistor name cannot be keyword "all"
  //   5. resistor name not found
  // TODO: Get old resistance value
  // TODO: Call setResistance() to update
  // TODO: Print success message: "Modified: resistor name from oldResistance
  // Ohms to newResistance Ohms"

  cout << "Error: modifyR not implemented yet" << endl;
}

void handlePrintR(stringstream& ss) {
  string name;

  // TODO: Read name
  // TODO: Check for errors:
  //   1. too few arguments
  //   2. invalid argument
  //   3. resistor name not found
  // TODO: Find the resistor in the array
  // TODO: Print "Print: resistor " and then call resistor->print()

  cout << "Error: printR not implemented yet" << endl;
}

void handleDeleteR(stringstream& ss) {
  string arg;

  // TODO: Read argument (should be "all")
  // TODO: Check for errors:
  //   1. too few arguments
  //   2. invalid argument (if not "all")
  // TODO: Delete all resistor objects
  // TODO: Reset resistorsCount to 0
  // TODO: Reset all nodes (set numRes to 0)
  // TODO: Print success message: "Deleted: all resistors"

  cout << "Error: deleteR not implemented yet" << endl;
}

void handleSetV(stringstream& ss) {
  int nodeid;
  double voltage;

  // TODO: Read nodeid and voltage
  // TODO: Check for errors:
  //   1. too few arguments
  //   2. invalid argument
  //   3. node value is out of permitted range
  // TODO: Call nodes[nodeid-1].setVoltage(voltage)
  // TODO: Print success message: "Set: node nodeid to voltage Volts"

  cout << "Error: setV not implemented yet" << endl;
}
