// Created by Salma Emara on 2023-06-02.
#include "Register.h"

#include <iostream>

Register::Register(int id, double timePerItem, double overhead,
                   double entryTime) {
  ID = id;
  secPerItem = timePerItem;
  overheadPerCustomer = overhead;
  availableTime = entryTime;
  next = nullptr;           // no other registers yet
  queue = new QueueList();  // no customers in line yet, but has to initialize a
                            // queue
}

Register::~Register() { delete queue; }

QueueList* Register::get_queue_list() { return queue; }

Register* Register::get_next() { return next; }

int Register::get_ID() { return ID; }

double Register::get_secPerItem() { return secPerItem; }

double Register::get_overheadPerCustomer() { return overheadPerCustomer; }

double Register::get_availableTime() { return availableTime; }

void Register::set_next(Register* nextRegister) { next = nextRegister; }

void Register::set_availableTime(double availableSince) {
  availableTime = availableSince;
}

double Register::calculateDepartTime() {
  // Calculate and return the departure time of the first customer in the queue
  // returns -1 if no customer is in the queue
  Customer* _head = queue->get_head();
  if (_head == nullptr) {
    return -1;
  }

  // If departure time is already calculated, return it
  if (_head->get_departureTime() != -1) {
    return _head->get_departureTime();
  }

  // Calculate departure time
  double processingTime =
      secPerItem * _head->get_numOfItems() + overheadPerCustomer;
  double departTime;

  if (_head->get_arrivalTime() > availableTime) {
    departTime = _head->get_arrivalTime() + processingTime;
  } else {
    departTime = availableTime + processingTime;
  }

  // Set the departure time for the customer
  _head->set_departureTime(departTime);

  return departTime;
}

void Register::departCustomer(QueueList* doneList) {
  // dequeue the head, set last dequeue time, add to doneList,
  // update availableTime of the register
  Customer* customer = queue->dequeue();
  if (customer != nullptr) {
    double departTime = customer->get_departureTime();
    availableTime = departTime;
    doneList->enqueue(customer);
  }
}

void Register::print() {
  std::cout << "Register ID: " << ID << std::endl;
  std::cout << "Time per item: " << secPerItem << std::endl;
  std::cout << "Overhead per customer: " << overheadPerCustomer << std::endl;
  if (queue->get_head() != nullptr) {
    std::cout << "Queue has customers: \n";
    queue->print();
  }
}
