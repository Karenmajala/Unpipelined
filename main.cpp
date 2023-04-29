#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include <stdlib.h>
#include <vector>
#include "maintenance.h"
#include "datapath.h"
using namespace std;
int step, inum, PC;
int main(){
  
  string inputFile, outputFile;
  char run='y';
  ifstream fileInput;
  ofstream fileOutput;
  
  while(run=='y'){
  cout<< "Enter the input and output file names separated by a space: "<<endl;
  cin>>inputFile>>outputFile;
  fileInput.open(inputFile);
    if(!fileInput.is_open()){
		  cout << "Could not open file ";
		  return -1;}
  fileOutput.open(outputFile);
    
//initialize
  step=1;
  inum=1; 
  PC=0;
  vector<string> code;
  MultiCycleReg mc;
  instruction inst;
  int *registers = new int[32];
  int *memory = new int[250]; //int is always 32 bits
  initializeArrays(registers, 32);
  initializeArrays(memory, 250);
  loadregisters(fileInput, registers);
  loadmemory(fileInput, memory);
  
  //load in code so that it can be indexed
  while(!fileInput.eof()){
   string line;
   fileInput>>line;
   if(line.length()>0){
   code.push_back(line);}
  }
  
  //cycle steps
  while(PC<code.size()){
   IF(fileOutput, mc, code); 
   ID(fileOutput, mc, inst,registers);
    //the following steps are dependent on instruction classification
   if(inst.type=='R'){ ClassR(fileOutput, mc, inst, registers);}
   else{ ClassI(fileOutput, mc, inst, registers, memory);}
   inum++; 
  }

  printRegisters(fileOutput, registers);
  printMemory(fileOutput, memory);
  fileInput.close();
  fileOutput.close();
  delete [] registers;
  delete [] memory;
  code.clear();

  cout<<"Would you like to simulate another round? (y/n)"<<endl;
  cin>>run;
  
}}
