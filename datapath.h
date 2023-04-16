#ifndef datapath_h
#define datapath_h
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include "maintenance.h"
using namespace std;
extern int step, inum, PC;
struct instruction{ //for organizing machine code fields
  char type;
  string op;
  int rs;
  int rt;
  int rd; 
  int shamt;
  int function;
  int immed;
};
struct MultiCycleReg{  //additional multicycle registers
  string IR;
  int A;
  int B;
  int ALUOut;
  int MDR;
};

//Instruction steps
void IF(ofstream &out, MultiCycleReg &mc, vector<string> &code){
  mc.IR=code[PC]; //get instruction, store in IR
  PC = PC+1; //increment PC
  printStep(out, "IF");
  return;
}

void ID(ofstream &out, MultiCycleReg &mc, instruction &inst, int *reg){
  string subC;
  subC = mc.IR.substr(0,6);
  inst.op = subC;
  subC=mc.IR.substr(6,5); //getting rs
  inst.rs = binaryToDecimal(subC);
  subC=mc.IR.substr(11,5); //getting rt
  inst.rt = binaryToDecimal(subC);
  subC=mc.IR.substr(16,5); //getting rd
  inst.rd = binaryToDecimal(subC);
  mc.A = reg[inst.rs];
  mc.B = reg[inst.rt];
  if(inst.op=="000000"){ 
    inst.type = 'R';
    subC=mc.IR.substr(21,5);
    inst.shamt = binaryToDecimal(subC);
    subC=mc.IR.substr(26,6);
    inst.function = stoi(subC);
  }else{inst.type = 'I';
    subC=mc.IR.substr(16,16);
    inst.immed = binaryToDecimal(subC);
    mc.ALUOut = inst.immed;}
  printStep(out, "ID");
  return;
}

//class dependent paths

//R-Type
void ClassR(ofstream &out, MultiCycleReg &mc, instruction &inst,int *reg){
  //execution
  if(inst.function == 100000){//ADD
      mc.ALUOut= mc.A + mc.B; }
  else if(inst.function == 100010){//SUB
      mc.ALUOut= mc.A- mc.B; }
  else if(inst.function == 101010){//SLT
    if(mc.A <mc.B){ mc.ALUOut= 1;}
    else{ mc.ALUOut=0;}}
  printStep(out, "EX");
  //write back (prof example) or memory (book)
  reg[inst.rd] = mc.ALUOut;
  printStep(out, "WB");
  return;
}

//I-Type
void ClassI(ofstream &out, MultiCycleReg &mc, instruction &inst, int *reg, int *mem){
  //execution
  if(inst.op == "000100"){//BEQ
    if(mc.A==mc.B){PC = PC + mc.ALUOut;}}
  else if(inst.op == "000101"){//BNE
      if(mc.A!=mc.B){PC = PC + mc.ALUOut;}}
  else{mc.ALUOut=mc.A + inst.immed;} //ADDi, LW, OR SW
  printStep(out, "EX");
  //Memory and Write Back
  if(inst.op == "100011"){mc.MDR = mem[mc.ALUOut/4]; //LW
    printStep(out, "MEM");
    reg[inst.rt]= mc.MDR ;
    printStep(out, "WB"); }                    
  else if(inst.op == "101011"){mem[mc.ALUOut/4] = mc.B;
     printStep(out, "MEM"); } //SW
  else if(inst.op == "001000"){reg[inst.rt]= mc.ALUOut;
     printStep(out, "WB"); } //addi
  return;
}


#endif /* datapath_h */
