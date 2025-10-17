#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "Customer.h"
#include "QueueList.h"
#include "Register.h"
#include "RegisterList.h"

using namespace std;

// Function Declarations:

// Set mode of the simulation
string getMode();

// Register
void parseRegisterAction(stringstream& lineStream, string mode);
void openRegister(
    stringstream& lineStream,
    string mode);  // register opens (it is upto customers to join)
void closeRegister(stringstream& lineStream,
                   string mode);  // register closes

// Customer
void addCustomer(stringstream& lineStream,
                 string mode);  // customer wants to join

// Depart customers
void departCustomers(string mode);

// Helper functions
bool getInt(stringstream& lineStream, int& iValue);
bool getDouble(stringstream& lineStream, double& dValue);
bool foundMoreArgs(stringstream& lineStream);

// Global variables
RegisterList* registerList;  // holding the list of registers
QueueList* doneList;         // holding the list of customers served
QueueList* singleQueue;      // holding customers in a single virtual queue
double expTimeElapsed;  // time elapsed since the beginning of the simulation

// List of commands:
// To open a register
// register open <ID> <secPerItem> <setupTime> <timeElapsed>
// To close register
// register close <ID> <timeElapsed>
// To add a customer
// customer <items> <timeElapsed>

int main() {
  registerList = new RegisterList();
  doneList = new QueueList();
  singleQueue = new QueueList();
  expTimeElapsed = 0;

  // Set mode by the user
  string mode = getMode();

  string line;
  string command;

  cout << "> ";  // Prompt for input
  getline(cin, line);

  while (!cin.eof()) {
    stringstream lineStream(line);
    lineStream >> command;
    if (command == "register") {
      parseRegisterAction(lineStream, mode);
    } else if (command == "customer") {
      addCustomer(lineStream, mode);
    } else {
      cout << "Invalid operation" << endl;
    }
    cout << "> ";  // Prompt for input
    getline(cin, line);
  }

  // Print final time
  cout << "Finished at time " << expTimeElapsed << endl;

  // Calculate statistics
  if (doneList->get_head() != nullptr) {
    cout << "Statistics:" << endl;

    double maxWaitTime = 0;
    double totalWaitTime = 0;
    int numCustomers = 0;

    // First pass: calculate max and average
    Customer* curr = doneList->get_head();
    while (curr != nullptr) {
      double waitTime = curr->get_departureTime() - curr->get_arrivalTime();
      totalWaitTime += waitTime;
      if (waitTime > maxWaitTime) {
        maxWaitTime = waitTime;
      }
      numCustomers++;
      curr = curr->get_next();
    }

    double avgWaitTime = totalWaitTime / numCustomers;

    // Second pass: calculate standard deviation
    double sumSquaredDiff = 0;
    curr = doneList->get_head();
    while (curr != nullptr) {
      double waitTime = curr->get_departureTime() - curr->get_arrivalTime();
      double diff = waitTime - avgWaitTime;
      sumSquaredDiff += diff * diff;
      curr = curr->get_next();
    }

    double stdDev = sqrt(sumSquaredDiff / numCustomers);

    cout << "Maximum wait time: " << maxWaitTime << endl;
    cout << "Average wait time: " << avgWaitTime << endl;
    cout << "Standard Deviation of wait time: " << stdDev << endl;
  }

  // Free all dynamically allocated memory
  // Delete all customers in doneList
  while (doneList->get_head() != nullptr) {
    Customer* customer = doneList->dequeue();
    delete customer;
  }
  delete doneList;

  // Delete all customers in singleQueue
  while (singleQueue->get_head() != nullptr) {
    Customer* customer = singleQueue->dequeue();
    delete customer;
  }
  delete singleQueue;

  // Delete all registers (and their queues) in registerList
  delete registerList;

  return 0;
}

string getMode() {
  string mode;
  cout << "Welcome to ECE 244 Grocery Store Queue Simulation!" << endl;
  cout << "Enter \"single\" if you want to simulate a single queue or "
          "\"multiple\" to "
          "simulate multiple queues: \n> ";
  getline(cin, mode);

  if (mode == "single") {
    cout << "Simulating a single queue ..." << endl;
  } else if (mode == "multiple") {
    cout << "Simulating multiple queues ..." << endl;
  }
  // default???

  return mode;
}

void departCustomers(string mode) {
  // Depart customers whose time has come
  while (true) {
    Register* minReg =
        registerList->calculateMinDepartTimeRegister(expTimeElapsed);
    if (minReg == nullptr) break;

    Customer* customer = minReg->get_queue_list()->get_head();
    if (customer == nullptr) break;

    double departTime = minReg->calculateDepartTime();
    if (departTime > expTimeElapsed) break;

    cout << "Departed a customer at register ID " << minReg->get_ID() << " at "
         << departTime << endl;
    minReg->departCustomer(doneList);

    // In single queue mode, assign next customer from single queue
    if (mode == "single" && singleQueue->get_head() != nullptr) {
      Customer* nextCustomer = singleQueue->dequeue();
      minReg->get_queue_list()->enqueue(nextCustomer);
      // Departure time will be calculated by calculateDepartTime()
    }
  }
}

void addCustomer(stringstream& lineStream, string mode) {
  int items;
  double timeElapsed;
  if (!getInt(lineStream, items) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments." << endl;
    return;
  }

  // Update system time
  expTimeElapsed += timeElapsed;

  // Depart customers whose time has come
  departCustomers(mode);

  // Add new customer
  Customer* newCustomer = new Customer(expTimeElapsed, items);
  cout << "A customer entered" << endl;

  // 1. single mode
  if (mode == "single") {
    Register* freeReg = registerList->get_free_register();
    if (freeReg != nullptr) {
      freeReg->get_queue_list()->enqueue(newCustomer);
      cout << "Queued a customer with free register " << freeReg->get_ID()
           << endl;
    } else {
      singleQueue->enqueue(newCustomer);
      cout << "No free registers" << endl;
    }
  } else {
    // Multiple queue mode
    Register* minReg = registerList->get_min_items_register();
    if (minReg != nullptr) {
      minReg->get_queue_list()->enqueue(newCustomer);
    }
  }
}

void parseRegisterAction(stringstream& lineStream, string mode) {
  string operation;
  lineStream >> operation;
  if (operation == "open") {
    openRegister(lineStream, mode);
  } else if (operation == "close") {
    closeRegister(lineStream, mode);
  } else {
    cout << "Invalid operation" << endl;
  }
}

void openRegister(stringstream& lineStream, string mode) {
  int ID;
  double secPerItem, setupTime, timeElapsed;
  // convert strings to int and double
  if (!getInt(lineStream, ID) || !getDouble(lineStream, secPerItem) ||
      !getDouble(lineStream, setupTime) ||
      !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }

  // Check if the register is already open
  if (registerList->foundRegister(ID)) {
    cout << "Error: register " << ID << " is already open" << endl;
    return;
  }

  // Update system time
  expTimeElapsed += timeElapsed;

  // Depart customers whose time has come
  departCustomers(mode);

  // Open the register
  Register* newRegister =
      new Register(ID, secPerItem, setupTime, expTimeElapsed);
  registerList->enqueue(newRegister);
  cout << "Opened register " << ID << endl;

  // If we were simulating a single queue,
  // and there were customers in line, then
  // assign a customer to the new register
  if (mode == "single" && singleQueue->get_head() != nullptr) {
    Customer* customer = singleQueue->dequeue();
    newRegister->get_queue_list()->enqueue(customer);
    cout << "Queued a customer with free register " << ID << endl;
  }
}

void closeRegister(stringstream& lineStream, string mode) {
  int ID;
  double timeElapsed;
  // convert string to int
  if (!getInt(lineStream, ID) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }
  // Check if the register is open
  // If it is open dequeue it and free it's memory
  // Otherwise, print an error message

  if (!registerList->foundRegister(ID)) {
    cout << "Error: register " << ID << " is not open" << endl;
    return;
  }

  // Update system time
  expTimeElapsed += timeElapsed;

  // Depart customers whose time has come
  departCustomers(mode);

  // Dequeue the register from the register list
  Register* closingRegister = registerList->dequeue(ID);

  if (closingRegister == nullptr) {
    return;
  }

  // If in single queue mode, move customers back to the single queue
  if (mode == "single") {
    QueueList* regQueue = closingRegister->get_queue_list();
    Customer* customer = regQueue->dequeue();
    while (customer != nullptr) {
      singleQueue->enqueue(customer);
      customer = regQueue->dequeue();
    }
  } else {
    // In multiple queue mode, redistribute customers to other registers
    QueueList* regQueue = closingRegister->get_queue_list();
    Customer* customer = regQueue->dequeue();
    while (customer != nullptr) {
      Register* minReg = registerList->get_min_items_register();
      if (minReg != nullptr) {
        minReg->get_queue_list()->enqueue(customer);
      }
      customer = regQueue->dequeue();
    }
  }

  // Free the register's memory
  delete closingRegister;
  cout << "Closed register " << ID << endl;
}

bool getInt(stringstream& lineStream, int& iValue) {
  // Reads an int from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  iValue = stoi(command);
  return true;
}

bool getDouble(stringstream& lineStream, double& dvalue) {
  // Reads a double from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  dvalue = stod(command);
  return true;
}

bool foundMoreArgs(stringstream& lineStream) {
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  } else {
    return true;
  }
}
