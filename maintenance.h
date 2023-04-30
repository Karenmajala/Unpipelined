#ifndef maintenance_h
#define maintenance_h
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <iostream>
using namespace std;
extern int step, inum;
void initializeArrays(int *array, int size)
{
    for(int i = 0; i < size; i++)
    {
        array[i] = 0;
    }
}

int binaryToDecimal(string binary)
{
    int decimal = 0;
    int power = 0;
    int sign=0;
    if(binary[0]=='1'){ //2s complement
      sign=1;
      if(binary[binary.size()-1]=='1'){
       binary[binary.size()-1]='0';
     }else{
      for(int i =binary.size()-1; i>=0; i--){
        if(binary[i]=='0'){
         binary[i]='1';
        }else{
         binary[i]='0';
         break;
    }}
    }for(int i= 0; i<binary.size(); i++){
      if(binary[i]=='0'){binary[i]='1';}
      else{binary[i]='0';}
    }} //convert to decimal
    for (int i=(binary.size()-1) ; i>=0; i--)
    {
        if (binary[i] == '1')
        {
            decimal += pow(2, power);
        }
        
        power++;
    }
    if(sign==1){decimal =-decimal;}
    return decimal;
}

void loadregisters(ifstream &input, int* reg){
  string line, subR;
  int R;
  input>>line;
  if(line=="REGISTERS"){
  input>>line;
   do{
        //Rs will always come in pairs
        subR = line.substr(1);
        R= stoi(subR);
        input>>line;
        reg[R] = stoi(line);
        reg[0]= 0;
        input>>line;
      }while(line!="MEMORY");
  }return;
}

void loadmemory(ifstream &input, int* mem){
  string line;
  int Mem;
  input>>line;
  do {
        Mem = stoi(line);
        input>>line;
        mem[Mem/4] = stoi(line);
        input>>line;
      }while(line!="CODE");
  return;
}

void printStep(ofstream &out, string istep){
  out<<"C#"<<step<<" "<<"I"<<inum<<" - "<<istep<<endl;
  step=step+1;
  return;
}

void printRegisters(ofstream &out, int* reg){
  out<<"REGISTERS"<<endl;
  for(int i=0; i<32; i++){
    if(reg[i]!=0){
      out<<"R"<<i<<" "<<reg[i]<<endl;
} } }

void printMemory(ofstream &out, int* mem){
  out<<"MEMORY"<<endl;
  for(int i=0; i<250; i++){
    if(mem[i]!=0){
      out<<(i*4)<<" "<<mem[i]<<endl;
} } }

#endif /* maintenance_h */
