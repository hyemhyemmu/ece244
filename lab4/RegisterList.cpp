#include "RegisterList.h"

#include <iostream>

#include "Register.h"
using namespace std;

RegisterList::RegisterList() {
  head = nullptr;
  size = 0;
}

RegisterList::~RegisterList() {
  // Delete all registers in the list
  Register* curr = head;
  for (int i = 0; i < size; i++) {
    Register* next = curr->get_next();
    delete curr->get_queue_list();
    delete curr;
    curr = next;
  }
}

Register* RegisterList::get_head() { return head; }

int RegisterList::get_size() {
  // return number of registers
  return size;
}

Register* RegisterList::get_min_items_register() {
  // loop all registers to find the register with least number of items
  if (head == nullptr) {
    return nullptr;
  }

  Register* min_ptr = head;
  int min = head->get_queue_list()->get_items();
  Register* curr = head->get_next();

  while (curr != nullptr) {
    int items = curr->get_queue_list()->get_items();
    if (items < min) {
      min = items;
      min_ptr = curr;
    }
    curr = curr->get_next();
  }

  return min_ptr;
}

Register* RegisterList::get_free_register() {
  // return the register with no customers
  // if all registers are occupied, return nullptr
  if (head == nullptr) {
    return nullptr;
  }

  Register* curr = head;
  while (curr != nullptr) {
    if (curr->get_queue_list()->get_head() == nullptr) {
      return curr;
    }
    curr = curr->get_next();
  }
  return nullptr;
}

void RegisterList::enqueue(Register* newRegister) {
  // a register is placed at the end of the queue
  // if the register's list is empty, the register becomes the head
  // Assume the next of the newRegister is set to null
  // You will have to increment size

  if (head == nullptr) {
    head = newRegister;
  } else {
    // get to the end
    Register* curr = head;
    while (curr->get_next() != nullptr) {
      curr = curr->get_next();
    }
    curr->set_next(newRegister);
  }
  size++;
}

bool RegisterList::foundRegister(int ID) {
  // look for a register with the given ID
  // return true if found, false otherwise
  if (head == nullptr) {
    return false;
  } else {
    Register* curr = head;
    while (curr != nullptr) {
      if (curr->get_ID() == ID) {
        return true;
      }
      curr = curr->get_next();
    }
  }
  return false;
}

Register* RegisterList::dequeue(int ID) {
  // dequeue the register with given ID
  // return the dequeued register
  // return nullptr if register was not found
  if (head == nullptr) {
    return nullptr;
  }

  if (head->get_ID() == ID) {
    Register* temp = head;
    head = head->get_next();
    size--;
    return temp;
  }

  Register* prev = head;
  Register* curr = head->get_next();
  while (curr != nullptr) {
    if (curr->get_ID() == ID) {
      prev->set_next(curr->get_next());
      size--;
      return curr;
    }
    prev = curr;
    curr = curr->get_next();
  }

  return nullptr;
}

Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed) {
  // return the register with minimum time of departure of its customer
  // if all registers are free, return nullptr
  if (head == nullptr) {
    return nullptr;
  }

  Register* minRegister = nullptr;
  double minDepartTime = -1;
  Register* curr = head;

  while (curr != nullptr) {
    if (curr->get_queue_list()->get_head() != nullptr) {
      double departTime = curr->calculateDepartTime();
      if (minRegister == nullptr || departTime < minDepartTime) {
        minDepartTime = departTime;
        minRegister = curr;
      }
    }
    curr = curr->get_next();
  }

  return minRegister;
}

void RegisterList::print() {
  Register* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
