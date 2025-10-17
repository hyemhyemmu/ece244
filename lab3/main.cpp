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
    "resistor name already exists",                     // 7
    "resistor name not found "                          // 8
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
void handleSolve();

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
      handleSolve();
    } else {
      // Invalid command
      cout << "Error: " << errorArray[0] << endl;
    }

    // Prompt for next command
    cout << ">>> ";
    cout.flush();
  }

  // clean old stuff
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

// command handler
void handleMaxVal(stringstream& ss) {
  int maxNodes, maxRes;
  string temp;

  // Read maxNodeNumber
  if (!getInteger(ss, maxNodes)) {
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Read maxResistors
  if (!getInteger(ss, maxRes)) {
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

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

  // Update
  maxNodeNumber = maxNodes;
  maxResistors = maxRes;

  // Allocate new arrays
  nodes = new Node[maxNodeNumber];
  resistors = new Resistor*[maxResistors];

  // Initialize
  for (int i = 0; i < maxResistors; i++) {
    resistors[i] = nullptr;
  }
  resistorsCount = 0;

  cout << "New network: max node number is " << maxNodeNumber
       << "; max resistors is " << maxResistors << endl;
}

void handleInsertR(stringstream& ss) {
  string name;
  double resistance;
  int nodeid1, nodeid2;

  // Read name
  if (!getString(ss, name)) {
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Read resistance
  if (!getDouble(ss, resistance)) {
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Read nodeid1
  if (!getInteger(ss, nodeid1)) {
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Read nodeid2
  if (!getInteger(ss, nodeid2)) {
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

  // I think this should be checked, but the doc says to ignore
  // errors other than the list
  // // Check if both nodes can add a resistor
  // if (!nodes[nodeid1 - 1].canAddResistor()) {
  //   cout << "Error: node " << nodeid1 << " has too many resistors" << endl;
  //   return;
  // }
  // if (!nodes[nodeid2 - 1].canAddResistor()) {
  //   cout << "Error: node " << nodeid2 << " has too many resistors" << endl;
  //   return;
  // }

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

  cout << "Inserted: resistor " << name << " " << fixed << setprecision(2)
       << resistance << " Ohms " << nodeid1 << " -> " << nodeid2 << endl;
}

void handleModifyR(stringstream& ss) {
  string name;
  double newResistance;

  // Read name
  if (!getString(ss, name)) {
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Read newResistance
  if (!getDouble(ss, newResistance)) {
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Check for negative resistance
  if (newResistance < 0) {
    cout << "Error: " << errorArray[2] << endl;  // negative resistance
    return;
  }

  // Check if name is "all"
  if (name == "all") {
    cout << "Error: " << errorArray[4]
         << endl;  // resistor name cannot be keyword "all"
    return;
  }

  // Find the resistor by name
  int idx = -1;
  for (int i = 0; i < resistorsCount; i++) {
    if (resistors[i] != nullptr && resistors[i]->getName() == name) {
      idx = i;
      break;
    }
  }

  // Check if resistor was found
  if (idx == -1) {
    cout << "Error: " << errorArray[8] << endl;  // name not found
    return;
  }

  // Get old resistance value
  double oldResistance = resistors[idx]->getResistance();

  // Update resistance
  resistors[idx]->setResistance(newResistance);

  cout << "Modified: resistor " << name << " from " << fixed << setprecision(2)
       << oldResistance << " Ohms to " << newResistance << " Ohms" << endl;
}

void handlePrintR(stringstream& ss) {
  string name;

  // Read name
  if (!getString(ss, name)) {
    // Check
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Find the resistor by name
  int idx = -1;
  for (int i = 0; i < resistorsCount; i++) {
    if (resistors[i] != nullptr && resistors[i]->getName() == name) {
      idx = i;
      break;
    }
  }

  // Check if resistor was found
  if (idx == -1) {
    cout << "Error: " << errorArray[8] << endl;  // resistor name not found
    return;
  }

  // Print resistor information
  cout << "Print:" << endl;
  resistors[idx]->print();
}

void handleDeleteR(stringstream& ss) {
  string arg;

  // Read argument (should be "all")
  if (!getString(ss, arg)) {
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Check if argument is "all"
  if (arg != "all") {
    cout << "Error: " << errorArray[1] << endl;  // invalid argument
    return;
  }

  // Delete all resistor objects
  for (int i = 0; i < resistorsCount; i++) {
    if (resistors[i] != nullptr) {
      delete resistors[i];
      resistors[i] = nullptr;
    }
  }

  // Reset resistorsCount to 0
  resistorsCount = 0;

  // Reset all nodes (set numRes to 0)
  for (int i = 0; i < maxNodeNumber; i++) {
    // Reset the node by recreating it
    nodes[i] = Node();
  }

  cout << "Deleted: all resistors" << endl;
}

void handleSetV(stringstream& ss) {
  int nodeid;
  double voltage;

  // Read nodeid
  if (!getInteger(ss, nodeid)) {
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Read voltage
  if (!getDouble(ss, voltage)) {
    if (ss.eof()) {
      cout << "Error: " << errorArray[6] << endl;  // too few arguments
    } else {
      cout << "Error: " << errorArray[1] << endl;  // invalid argument
    }
    return;
  }

  // Check if node value is in permitted range
  if (nodeid < 1 || nodeid > maxNodeNumber) {
    cout << "Error: " << errorArray[3]
         << endl;  // node value is out of permitted range
    return;
  }

  // Set voltage for the node (index different)
  nodes[nodeid - 1].setVoltage(voltage);

  cout << "Set: node " << nodeid << " to " << fixed << setprecision(2)
       << voltage << " Volts" << endl;
}

void handleSolve() {
  const double MIN_ITERATION_CHANGE = 0.0001;
  const int MAX_ITERATIONS = 100000;  // Safety limit to prevent infinite loops

  // Step 1: Initialize all nodes without set voltage to 0
  for (int i = 0; i < maxNodeNumber; i++) {
    if (!nodes[i].isVoltageSet()) {
      nodes[i].setVoltageInternally(0.0);
    }
  }

  // Step 2: Iterate
  bool converged = false;
  int iteration = 0;

  while (!converged && iteration < MAX_ITERATIONS) {
    converged = true;  // Assume convergence, will be set to false if any node
                       // changes significantly
    iteration++;

    // For each node without a set voltage
    for (int nodeIndex = 0; nodeIndex < maxNodeNumber; nodeIndex++) {
      if (!nodes[nodeIndex].isVoltageSet()) {
        // Get the resistors connected to this node
        int numRes = nodes[nodeIndex].getNumRes();
        int* resIDArray = nodes[nodeIndex].getResIDArray();

        // Calculate new voltage using Eq. 3
        if (numRes > 0) {
          double sumVoltageOverR = 0.0;
          double sumOneOverR = 0.0;

          // Sum up contributions from all connected resistors
          for (int j = 0; j < numRes; j++) {
            int resistorID = resIDArray[j];
            if (resistors[resistorID] != nullptr) {
              double resistance = resistors[resistorID]->getResistance();

              // Get the other endpoint (neighbor node)
              // nodeIndex is 0-based, but endpoint IDs are 1-based
              int otherNodeID =
                  resistors[resistorID]->getOtherEndpoint(nodeIndex + 1);

              if (otherNodeID != -1) {
                // Convert to 0-based index
                int otherNodeIndex = otherNodeID - 1;
                double neighborVoltage = nodes[otherNodeIndex].getVoltage();

                sumVoltageOverR += neighborVoltage / resistance;
                sumOneOverR += 1.0 / resistance;
              }
            }
          }

          // Calculate new voltage: V0 = (1 / sum(1/R)) * sum(V/R)
          double newVoltage = 0.0;
          if (sumOneOverR != 0.0) {
            newVoltage = sumVoltageOverR / sumOneOverR;
          }

          // Check if voltage changed significantly
          double oldVoltage = nodes[nodeIndex].getVoltage();
          double change = (newVoltage - oldVoltage);
          if (change < 0) change = -change;  // Absolute value

          if (change > MIN_ITERATION_CHANGE) {
            converged = false;
          }

          // Update voltage
          nodes[nodeIndex].setVoltageInternally(newVoltage);
        }
      }
    }
  }

  // Step 3: Print results
  cout << "Solve:" << endl;

  // Print nodes in ascending order that have at least one resistor connected
  for (int i = 0; i < maxNodeNumber; i++) {
    if (nodes[i].getNumRes() > 0) {
      cout << "Node " << (i + 1) << ": " << fixed << setprecision(2)
           << nodes[i].getVoltage() << " V" << endl;
    }
  }
}
