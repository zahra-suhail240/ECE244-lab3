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
    // why not enoguh error checks?
    "invalid command",                       // 0
    "invalid argument",                      // 1
    "negative resistance",                   // 2
    "node value is out of permitted range 1-",  // 3 //make sure to add in the  1-
                                             // Max Node number var
    "resistor name cannot be keyword \"all\"",          // 4
    "both terminals of resistor connect to same node",  // 5
    "too few arguments",                                // 6
    "resistor name already exist",  // 7 where it says name, add name of the res
    "resistor "       // 8 where it says name, add name of the res
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
  // TODO: Implement the main function here
  // First get user input

  getline(cin, line);

  while (!cin.eof()) {
    stringstream userInput(line);

    userInput >> command;

    if (command == "maxVal") {
      handleMaxVal(userInput);
    } else if (command == "insertR") {
      handleInsertR(userInput);
    } else if (command == "modifyR") {
      handleModifyR(userInput);
    } else if (command == "printR") {
      handlePrintR(userInput);
    } else if (command == "deleteR") {
      handleDeleteR(userInput);
    } else if (command == "setV") {
      handleSetV(userInput);
    }

    else if (command == "solve") {
      // bonus

    } else {
      cout <<"Error :"<< errorArray[0] << endl;  // invalid command
    }

    cout << ">>> ";
    getline(cin, line);
  }

  //Clear memeory when the program ends
  delete[] nodes;

  for(int i=0; i<resistorsCount; i++){
    delete resistors[i];
  }
  delete[] resistors;

  return 0;
}

// TODO: Implement functions here

//Implement helper function

bool getInteger(stringstream& ss, int& x){
    ss >> x; //extract the integer, to be returned. all other function uses this value when needed
    
    //is the extraction successful or not
    if(ss.fail() == false){ //extraction was successful 
        return true; 
    }
    else if(ss.fail() == true){ //meaning extraction failed
        return false;
    }
}
bool getString(stringstream& ss, string& s) {
    ss >> s;
    if(ss.fail() == false){ //extraction was successful 
        return true; 
    }
    else if(ss.fail() == true){ //meaning extraction failed
        return false;
    }
}

bool getDouble(stringstream& ss, double& d){
    ss >> d;
    if(ss.fail() == false){ //extraction was successful 
        return true; 
    }
    else if(ss.fail() == true){ //meaning extraction failed
        return false;
    }
}



void handleMaxVal(stringstream& ss) {
int maxNodeVal, maxResistorVal;
bool checkMaxNode, checkMaxResistor;
checkMaxNode = getInteger(ss, maxNodeVal);
checkMaxResistor = getInteger(ss,maxResistorVal);

if(ss.eof() && (checkMaxNode == false || checkMaxResistor == false )){
     cout << "Error: " << errorArray[6] << endl; // too few arguments
     ss.clear();
     ss.ignore(1000, '\n');
     return;
}
//check if arg are correct, ensure their integers and positive value

else if(checkMaxNode == false || maxNodeVal <=0 ){
    cout << "Error: " <<  errorArray[1] << endl; //invalid arg
    ss.clear();
    ss.ignore(1000, '\n');
    return; //prevents function from cont execution when an error occurs
}

/*else if(ss.eof()){
    cout << "Error: " << errorArray[6] << endl; // too few arguments
     ss.clear();
     ss.ignore(1000, '\n');
     return;
}*/

else if(checkMaxResistor == false || maxResistorVal<=0){
    cout << "Error: " <<  errorArray[1] << endl; //invalid arg
    ss.clear();
    ss.ignore(1000, '\n');
    return;
}

else if(checkMaxNode == true && checkMaxResistor == true){

  delete[] nodes;

  for(int i=0; i<resistorsCount; i++){
    delete resistors[i];
  }
  delete[] resistors;

 maxNodeNumber = maxNodeVal;
 maxResistors = maxResistorVal;

 nodes = new Node[maxNodeNumber];
 resistors = new Resistor*[maxResistors];
 resistorsCount =0;

 cout<< "New network: max node number is "<< maxNodeNumber<< "; max resistors is "<< maxResistors<<endl;
    

}



//bcz by refernce maxNodeVal will change

/*else if(maxNodeVal <=0 || maxResistorVal<=0 ){
    cout << "Error: " <<  errorArray[1] << endl;
    return;
}*/

//If user created a new network, mae sure to delete the previous one

 /*delete[] nodes;

  for(int i=0; i<resistorsCount; i++){
    delete resistors[i];
  }
  delete[] resistors;

 maxNodeNumber = maxNodeVal;
 maxResistors = maxResistorVal;

 nodes = new Node[maxNodeNumber];
 resistors = new Resistor*[maxResistors];
 resistorsCount =0;

 cout<< "New network: max node number is "<< maxNodeNumber<< "; max resistors "<< maxResistors<<endl;
  */  
}

void handleInsertR(stringstream& ss) {
  string name_;
  double resistance;
  int endpoints_[2];

  bool checkName, checkRes, checkendPoint1, checkendPoint2;
  checkName = getString(ss, name_);
  checkRes = getDouble(ss, resistance);

  checkendPoint1 = getInteger(ss, endpoints_[0]);
  checkendPoint2 = getInteger(ss, endpoints_[1]);

  if(ss.eof() && (checkName == false || checkRes == false || checkendPoint1 == false || checkendPoint2 == false) ){
    cout << "Error: " << errorArray[6] << endl;  // too few arguments
        ss.clear();
        ss.ignore(1000, '\n');
        return;
  }
  else if(checkName == false){
     cout << "Error: " << errorArray[1] << endl; //invalid arg 
     ss.clear();
     ss.ignore(1000, '\n');
    return;
  }
  else if(checkRes == false){
     cout << "Error: " << errorArray[1] << endl; //invalid arg 
     ss.clear();
     ss.ignore(1000, '\n');
    return;
  }
  else if(checkendPoint1== false){
     cout << "Error: " << errorArray[1] << endl; //invalid arg 
     ss.clear();
     ss.ignore(1000, '\n');
    return;
  }
   else if(checkendPoint2== false){
     cout << "Error: " << errorArray[1] << endl; //invalid arg 
     ss.clear();
     ss.ignore(1000, '\n');
    return;
  }

  else if(resistance < 0){
    cout << "Error: " << errorArray[2] << endl; // negative resistance
    ss.clear();
    ss.ignore(1000, '\n');
    return;
  }
  else if(endpoints_[0] < 1 || endpoints_[0] > maxNodeNumber ||
        endpoints_[1] < 1 || endpoints_[1] > maxNodeNumber){
        cout << "Error: " << errorArray[3] << maxNodeNumber << endl; // node value out of range
        ss.clear();
        ss.ignore(1000, '\n');
        return;
        }
  else if(name_ == "all"){
    cout << "Error: " << errorArray[4] << endl; // name cannot be "all"
    ss.clear();
    ss.ignore(1000, '\n');
    return;
  }
  else if(checkName == true && checkRes==true && checkendPoint1 ==true && checkendPoint2==true){
    
    for (int i = 0; i < resistorsCount; ++i) {
        if (resistors[i]->getName() == name_) {
            cout << "Error: " << errorArray[7] << endl; // name already exists
            ss.clear();
            ss.ignore(1000, '\n');
            return;
        }
    }

     if (endpoints_[0] == endpoints_[1]) {
        cout << "Error: " << errorArray[5] << endl; // both terminals same node
        ss.clear();
        ss.ignore(1000, '\n');
        return;
    }

        int nodeIndex1 = endpoints_[0] - 1;
        int nodeIndex2 = endpoints_[1] - 1;

        int endpoints[2] = {nodeIndex1, nodeIndex2};
        //add an object of resistor to resistor array

        resistors[resistorsCount] = new Resistor(name_, resistance, endpoints);
        nodes[nodeIndex1].addResistor(resistorsCount);
        nodes[nodeIndex2].addResistor(resistorsCount);
        resistorsCount++;
        
        cout << "Inserted: resistor "<< name_<< " "<< fixed << setprecision(2)<< resistance << " Ohms " << endpoints_[0] << " -> " << endpoints_[1] << endl;

  
  }

  /*ss >> name_;
  ss >> resistance;

  for (int i = 0; i < 2; i++) {
    ss >> endpoints_[i];
  }*/

  //resistors[resistorsCount] = new Resistor(name_, resistance, endpoints_);
  //resistorsCount++;
  
  
}
void handleModifyR(stringstream& ss) {
    string name_;
    double newResistance, oldResistance;
    bool checkName, checkRes;

    checkName = getString(ss, name_);
    checkRes = getDouble(ss,newResistance);

    if(ss.eof() && (checkName == false || checkRes == false) ){
    cout << "Error: " << errorArray[6] << endl;  // too few arguments
        ss.clear();
        ss.ignore(1000, '\n');
        return;
  }
  else if(checkName == false){
     cout << "Error: " << errorArray[1] << endl; //invalid arg 
     ss.clear();
     ss.ignore(1000, '\n');
    return;
  }
  else if(checkRes == false){
     cout << "Error: " << errorArray[1] << endl; //invalid arg 
     ss.clear();
     ss.ignore(1000, '\n');
    return;
  }
  else if(newResistance < 0){
    cout << "Error: " << errorArray[2] << endl; // negative resistance
    ss.clear();
    ss.ignore(1000, '\n');
    return;
  }
   else if(name_ == "all"){
    cout << "Error: " << errorArray[4] << endl; // name cannot be "all"
    ss.clear();
    ss.ignore(1000, '\n');
    return;
  }
  else if(checkName == true && checkRes==true){

    for(int i=0; i < resistorsCount; i++){
        if(resistors[i]->getName() == name_){
            oldResistance = resistors[i]->getResistance();
            resistors[i]->setResistance(newResistance);
            cout << "Modified: resistor " << name_ << " from " << fixed << setprecision(2)
                 << oldResistance << " Ohms to " << newResistance << " Ohms" << endl;
            return;
        }
    }
    cout << "Error: " << errorArray[8] << name_ << " not found"<< endl; // name not found
        
  }


}
void handlePrintR(stringstream& ss) {
    string name_;
    bool checkName;

    checkName = getString(ss, name_);

   if(ss.eof() && (checkName == false ) ){
    cout << "Error: " << errorArray[6] << endl;  // too few arguments
        ss.clear();
        ss.ignore(1000, '\n');
        return;
  }
  else if(checkName == false){
     cout << "Error: " << errorArray[1] << endl; //invalid arg 
     ss.clear();
     ss.ignore(1000, '\n');
    return;
  }
  else if(name_ == "all"){
    cout << "Error: " << errorArray[4] << endl; // name cannot be "all"
    ss.clear();
    ss.ignore(1000, '\n');
    return;
  }
  else if(checkName == true){

    for(int i = 0; i < resistorsCount; i++){
        if (resistors[i]->getName() == name_) {
                resistors[i]->print();
                return;
            }
    }

     cout << "Error: " << errorArray[8] << name_ << " not found"<< endl; // name not found
            
  }

}
void handleDeleteR(stringstream& ss) {
    string name_;
    bool checkName;

    checkName = getString(ss, name_);

    if(ss.eof() && (checkName == false ) ){
    cout << "Error: " << errorArray[6] << endl;  // too few arguments
        ss.clear();
        ss.ignore(1000, '\n');
        return;
   }
   else if(checkName == false){
     cout << "Error: " << errorArray[1] << endl; //invalid arg 
     ss.clear();
     ss.ignore(1000, '\n');
    return;
  }
  else if(checkName == true){
     if (name_ == "all") {
        for (int i = 0; i < resistorsCount; ++i) {
            delete resistors[i];
        }
        delete[] resistors;
        resistorsCount = 0;
        cout << "Deleted: all resistors" << endl;
  }
}
}
void handleSetV(stringstream& ss) {
    int nodeIndex;
    double voltage;

    bool checkIndex, checkVoltage;

    checkIndex = getInteger(ss, nodeIndex);
    checkVoltage = getDouble(ss, voltage);

  if(ss.eof() && (checkIndex == false || checkVoltage == false) ){
    cout << "Error: " << errorArray[6] << endl;  // too few arguments
        ss.clear();
        ss.ignore(1000, '\n');
        return;
  }
  else if(checkIndex == false){
     cout << "Error: " << errorArray[1] << endl; //invalid arg 
     ss.clear();
     ss.ignore(1000, '\n');
    return;
  }
  else if(checkVoltage == false){
     cout << "Error: " << errorArray[1] << endl; //invalid arg 
     ss.clear();
     ss.ignore(1000, '\n');
    return;
  }
  else if(nodeIndex < 1 || nodeIndex > maxNodeNumber){

        cout << "Error: " << errorArray[3] << maxNodeNumber << endl; // node value out of range
        ss.clear();
        ss.ignore(1000, '\n');
        return;

  }
  else if(checkIndex && checkVoltage==true){
    nodes[nodeIndex - 1].setVoltage(voltage);
    cout << "Set: node " << nodeIndex << " to " << fixed << setprecision(2) << voltage << " Volts" << endl;
  }

}









