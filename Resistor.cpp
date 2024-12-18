//
//  Resistor.cpp
//  Lab 3 The Resistor Network Program
// Author:
// Date:

#include "Resistor.h"

#include <iomanip>
#include <string>

#include "Node.h"

// Constructor

Resistor::Resistor(string name_, double resistance_, int endpoints_[2]) {
  name = name_;
  resistance = resistance_;

  endpointNodeIDs[0] = endpoints_[0];
  endpointNodeIDs[1] = endpoints_[1];
}

string Resistor::getName() { return name; }

double Resistor::getResistance() { return resistance; }

void Resistor::setResistance(double resistance_) { resistance = resistance_; }

int Resistor::getOtherEndpoint(int nodeIndex) {
  if (endpointNodeIDs[0] == nodeIndex) {
    return endpointNodeIDs[1];
  }

  else if (endpointNodeIDs[1] == nodeIndex) {
    return endpointNodeIDs[0];
  }
}

void Resistor::print() {
  cout << std::left << std::setw(20) << name << std::right << std::setw(8)
       << std::fixed << std::setprecision(2) << resistance << " Ohms "
       << endpointNodeIDs[0]+1 << " -> " << endpointNodeIDs[1]+1 << endl;
}
