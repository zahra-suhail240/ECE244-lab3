//
//  Node.cpp
//  Lab 3 The Resistor Network Program
// Author:
// Date:

// Constructor

#include "Node.h"

#include <string>

#include "Resistor.h"

Node::Node() {
  numRes = 0;
  voltage = 0;
  voltageIsSet = false;
}

bool Node::canAddResistor() {  // double check this
  if (numRes < MAX_RESISTORS_PER_NODE) {
    return true;
  }
}

void Node::addResistor(int rIndex) {
  // adds a resistor to resIDArray array and increments number of resistors

  if (canAddResistor() == true) {
    resIDArray[numRes] = rIndex;
    numRes++;
  }
}

double Node::getVoltage() { return voltage; }

void Node::setVoltage(double voltage_) {
  voltage = voltage_;
  voltageIsSet = true;
}

bool Node::isVoltageSet() { return voltageIsSet; }

int Node::getNumRes() { return numRes; }

int* Node::getResIDArray() {
  /*func returns a pointer to the first element of
   the array*/

  return resIDArray;
}
