//
//  lable_lib.cpp
//  DLCO_LAB_MINI_PROJEECT
//
//  Created by Sahil Shaikh on 10/14/24.
//  Roll Number 2301CS76
//  shaikh_2301CS76@iitp.ac.in
//
//

#include "lable_lib.hpp"
#include<iostream>
#include<map>
#include<string>
#include <fstream>
#include "opcode_lib.hpp"
using namespace std;

int lables;
int address;
map<string , string> lable_map;
bool error = 0;


void init(){
    lables = 0;
    address = 0;
    lable_map.clear();
    ofstream out;
    out.open("error.txt");
//        out.open("error.txt");
    
    out << "";
    out.close();
    out.open("machine_code.txt");
    out << "";
    out.close();
    out.open("listing_file.txt");
    ofstream ofs("listing_file.txt",ios::trunc);
    opc_reset();
}



