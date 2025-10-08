//
//  Node.cpp
//  Lab 3 The Resistor Network Program
// Author: Fei Mo
// Date:

#include "Node.h"

// constructor
Node::Node() {
  numRes = 0;
  voltage = 0.0;
  voltageIsSet = false;

  for (int i = 0; i < MAX_RESISTORS_PER_NODE; i++) {
    resIDArray[i] = 0;
  }
}

bool Node::canAddResistor() { return (numRes < MAX_RESISTORS_PER_NODE); }

void Node::addResistor(int rIndex) {
  if (canAddResistor) {
    resIDArray[numRes] = rIndex;
    numRes++;
  } else {
    cerr << "cannot add resistor!" << endl;
  }
}
// returns voltage
double Node::getVoltage() { return voltage; }

// sets voltage and sets voltageIsSet to true
void Node::setVoltage(double voltage_) {
  voltage = voltage_;
  voltageIsSet = true;
}

// sets voltage temporarily during
// iterations for solve command
// returns voltageIsSet
void Node::setVoltageInternally(double voltage_) {
  voltage = voltage_;
  // Note: NOT set voltageIsSet to true - for internal iterations
  // only
}

bool Node::isVoltageSet() { return voltageIsSet; }

int Node::getNumRes() { return numRes; }

int* Node::getResIDArray() { return resIDArray; }
