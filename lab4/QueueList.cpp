#include "QueueList.h"

#include "Customer.h"

QueueList::QueueList() { head = nullptr; }

QueueList::QueueList(Customer* customer) { head = customer; }

QueueList::~QueueList() {
  // QueueList doesn't own the customers, so don't delete them here
  // Customers will be deleted by whoever owns them (doneList in main)
}

Customer* QueueList::get_head() { return head; }

void QueueList::enqueue(Customer* customer) {
  // a customer is placed at the end of the queue
  // if the queue is empty, the customer becomes the head
  if (head == nullptr) {
    head = customer;
  } else {
    Customer* curr = head;
    while (curr->get_next() != nullptr) {
      curr = curr->get_next();
    }
    curr->set_next(customer);
  }
}

Customer* QueueList::dequeue() {
  // remove a customer from the head of the queue
  // and return a pointer to it
  if (head == nullptr) {
    return nullptr;
  } else {
    Customer* new_head = head->get_next();
    Customer* prev_head = head;
    head = new_head;
    return prev_head;
  }
}

int QueueList::get_items() {
  // count total number of items each customer in the queue has
  int num = 0;
  Customer* curr = head;
  while (curr != nullptr) {
    num += curr->get_numOfItems();
    curr = curr->get_next();
  }
  return num;
}

void QueueList::print() {
  // print customers in a queue
  Customer* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
