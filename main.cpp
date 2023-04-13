#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include "maintenance.h"
using namespace std;
int binaryToDecimal(string binary)
{
    int decimal = 0;
    int power = 0;
    for (int i=(binary.size()-1) ; i>=0; i--)
    {
        if (binary[i] == '1')
        {
            decimal += pow(2, power);
        }
        
        power++;
    }
    return decimal;
};
struct instruction{
  char type;
  int op;
  int rs;
  int rt;
  int rd; 
  int shamt;
  int function;
  int immed;
};
int main()
{
    
    ifstream fileInput;
    ofstream fileOutput;
    fileInput.open("input.txt");
    if(!fileInput.is_open()){
		  cout << "Could not open file ";
		  return -1;
    }
    fileOutput.open("Output.txt");
    
    
    string line;
    istringstream numbers(line);
    int *registers = new int[32];
    int *memory = new int[1000];
    initializeArrays(registers, 32);
    initializeArrays(memory, 1000);
    int regNum, memNum, regVal, memVal;

  //main code
    fileInput>>line;
    if(line=="REGISTERS"){
      fileInput>>line;
      int R;
      string subR ;
      do
      {
        //Rs will always come in pairs
        subR = line.substr(1);
        R= stoi(subR);
        fileInput>>line;
        registers[R] = stoi(line);
        fileInput>>line;
      }while(line!="MEMORY");
      
    }else{ cout<< "File not in correct Format"<<endl;
         return -1;}
  //MEMORY
  int Mem;
  fileInput>>line;
  do
      {
        Mem = stoi(line);
        fileInput>>line;
        memory[Mem] = stoi(line);
        fileInput>>line;
      }while(line!="CODE");
  //code
  fileInput>>line;
  //cout<<instruction fetch
  //decode
  instruction inst;
  string subC;
  subC = line.substr(0,6);
  inst.op = stoi(subC);
  subC=line.substr(6,5); //getting rs
  inst.rs = binaryToDecimal(subC);
  subC=line.substr(11,5); //getting rt
  inst.rt = binaryToDecimal(subC);
  subC=line.substr(16,5); //getting rd
  inst.rd = binaryToDecimal(subC);
  if(inst.op==0){ 
    inst.type = 'R';
    subC=line.substr(21,5);
    inst.shamt = binaryToDecimal(subC);
    subC=line.substr(26,6);
    inst.function = stoi(subC);
  }else{inst.type = 'I';
    subC=line.substr(16,16);
    inst.immed = binaryToDecimal(subC);}
  //cout<<instruction decode
  //arithmetic part
  
  if(inst.type=='R'){
    if(inst.function == 100000){//ADD
      
    }
    else if(inst.function == 100010){//SUB
      
    }
    else if(inst.function == 101010){//SLT
      
    }
  }else{
    if(inst.op == 001000){//ADDI
    }
    else if(inst.op == 100011){//LW
    }
    else if(inst.op == 101011){//SW
    }
    else if(inst.op == 000100){//BEQ
    }
    else if(inst.op == 000101){//BNE
    }
  }
  
    
    
    
    fileInput.close();
    fileOutput.close();
    delete [] registers;
    delete [] memory;
}
