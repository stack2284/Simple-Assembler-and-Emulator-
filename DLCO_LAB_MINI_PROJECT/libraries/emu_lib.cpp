//
//  emu_lib.cpp
//  DLCO_LAB_MINI_PROJEECT
//
//  Created by Sahil Shaikh on 10/21/24.
//  Roll Number 2301CS76
//  shaikh_2301CS76@iitp.ac.in
//
//

#include "emu_lib.hpp"
#include <iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<strstream>
#include "support_lib.hpp"
#include "opcode_lib.hpp"
#include "Assembler_lib.hpp"

using namespace std ;

int STACKPOINTER = 0 ;
int &SP = STACKPOINTER ;
int PC = 0;
int A = 0, B = 0;
int Value = 0;
int Offset = 0;

int Memory [(1ll<<25)]; //32 bit memory set to
void function_call(int opcode){
    switch (opcode) {
        case 0:
            B = A ;
            A = Value;
            break;
        case 1 :
            A += Value;
            break;
        case 2 :
            B =A;
            A = Memory[Offset + SP];
            break;
        case 3:
            
            Memory[SP + Offset] = A;
            A = B ;
            break;
        case 4 :
            A = Memory[A + Offset];
            break;
        case 5 :
            Memory[A + Offset] = B;
            break;
        case 6 :
            A += B;
            break;
        case 7 :
            A = B - A;
            break;
        case 8 :
            A = B << A;
            break;
        case 9 :
            A = B >> A;
            break;
        case 10 :
            SP = SP + Value;
            break;
        case 11 :
            SP = A;
            A = B;
            break;
        case 12 :
            B = A;
            A = SP;
            break;
        case 13 :
            B = A;
            A = PC;
            PC += Offset;
            PC --; // for PC++ in loop
            break;
        case 14 :
            PC = A;
            A = B;
            break;
        case 15 :
            if(A == 0){
                PC = PC + Offset;
                PC --; // for PC++ in loop
            }
            break;
        case 16 :
            if(A < 0){
                PC = PC + Offset;
                PC --; // for PC++ in loop
            }
            break;
        case 17 :
            PC = PC + Offset;
            PC --; // for PC++ in loop
            break;
        case 18 : // halt
            return ;
            break;
            
        default:
            break;
    }
}


void memory_dump_create(string s){
    
    ofstream mdf;
    mdf.open(s);
    mdf << "A : " << intToHex((int)A);
    mdf << "\nB : " << intToHex((int)B);
    mdf << "\nPC : " << intToHex((int)PC);
    mdf << "\nSP : " << intToHex((int)SP)<<"\n";
    
    for(int i = 0 ; i < (1ll << 25) ; i += 4){
        mdf << intToHex(i) << " ";
        mdf << intToHex((int)Memory[i])<< " ";
        mdf << intToHex((int)Memory[i  +1 ])<< " ";
        mdf << intToHex((int)Memory[i + 2 ])<< " ";
        mdf << intToHex((int)Memory[i + 3 ])<< " \n";
    }
    return ;
}
void emu (string &s){
    asm_file(s);
    // now process obj code
    vector <string > code;
    ifstream obj;
    obj.open("machine_code.txt");
    int line_no = 0;
    while (!obj.eof()) {
        string code_line;
        getline(obj ,code_line);
        stringstream code_stream(code_line);
        string mac_opcode;
        code_stream >> mac_opcode; // address
        code_stream >> mac_opcode; // actual ocp
        if(mac_opcode[mac_opcode.size() - 1] == ':') {
            line_no ++;
            continue;
        }
        code.push_back(mac_opcode);
        if(mac_opcode.size() == 6){
            Memory[code.size() - 1] =hexToDecimal(mac_opcode);
        }else if(mac_opcode.size() == 8){
            mac_opcode.pop_back();
            mac_opcode.pop_back();
            Memory[code.size() - 1] =hexToDecimal(mac_opcode);
        }
        line_no ++;
    }
    obj.close();
    while (PC < code.size()) {
        string code_line = code[PC];
        if(code_line.size() == 8){
            string line_operand = "00";
            line_operand[0] = code_line[6];
            line_operand[1] = code_line[7];
            Value = Memory[PC];
            Offset = Memory[PC];
            int opc = hexToDecimal(line_operand);
            if(opc == 18) break; // halt
            else function_call(opc);
        }
        PC ++;
    }
    
    memory_dump_create("Memory_dump.txt");
    return;
}


