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
    "resistor name already exists"                      // 7
    // not in original code but exist in doc
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
  string temp;

  // Read maxNodeNumber
  if (!getInteger(ss, maxNodes)) {
    // Check if it's missing or wrong type
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Read maxResistors
  if (!getInteger(ss, maxRes)) {
    // Check if it's missing or wrong type
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
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

  // Read name
  if (!getString(ss, name)) {
    // Check if it's missing or wrong type
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Read resistance
  if (!getDouble(ss, resistance)) {
    // Check if it's missing or wrong type
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Read nodeid1
  if (!getInteger(ss, nodeid1)) {
    // Check if it's missing or wrong type
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Read nodeid2
  if (!getInteger(ss, nodeid2)) {
    // Check if it's missing or wrong type
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Check for negative resistance
  if (resistance < 0) {
    cout << "Error: " << errorArray[2] << endl;  // negative resistance
    return;
  }

  // Check if name is "all"
  if (name == "all") {
    cout << "Error: " << errorArray[4] << endl;  // resistor name  "all"
    return;
  }

  // Check if resistor name already exists
  for (int i = 0; i < resistorsCount; i++) {
    if (resistors[i] != nullptr && resistors[i]->getName() == name) {
      cout << "Error: " << errorArray[7] << endl;
      return;
    }
  }

  // Check if node values are in permitted range
  if (nodeid1 < 1 || nodeid1 > maxNodeNumber) {
    cout << "Error: " << errorArray[3]
         << endl;  // node value is out of permitted range
    return;
  }
  if (nodeid2 < 1 || nodeid2 > maxNodeNumber) {
    cout << "Error: " << errorArray[3]
         << endl;  // node value is out of permitted range
    return;
  }

  // Check if both terminals connect to same node
  if (nodeid1 == nodeid2) {
    cout << "Error: " << errorArray[5]
         << endl;  // both terminals of resistor connect to same node
    return;
  }

  // Check if we have space for more resistors
  if (resistorsCount >= maxResistors) {
    cout << "Error: resistor array is full" << endl;
    return;
  }

  // Check if both nodes can add a resistor
  if (!nodes[nodeid1 - 1].canAddResistor()) {
    cout << "Error: node " << nodeid1 << " has too many resistors" << endl;
    return;
  }
  if (!nodes[nodeid2 - 1].canAddResistor()) {
    cout << "Error: node " << nodeid2 << " has too many resistors" << endl;
    return;
  }

  // Create endpoint array (convert to 0-based indices)
  int endpoints[2];
  endpoints[0] = nodeid1;  // Keep 1-based for printing
  endpoints[1] = nodeid2;

  // Create new Resistor object
  Resistor* newResistor = new Resistor(name, resistance, endpoints);

  // Add resistor pointer to resistors array
  resistors[resistorsCount] = newResistor;

  // Add resistor to both nodes (using resistorID which is the current count)
  nodes[nodeid1 - 1].addResistor(resistorsCount);
  nodes[nodeid2 - 1].addResistor(resistorsCount);

  // Increment resistorsCount
  resistorsCount++;

  // Print success message
  cout << "Inserted: resistor " << name << " " << fixed << setprecision(2)
       << resistance << " Ohms " << nodeid1 << " -> " << nodeid2 << endl;
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
