//
//  opcode_lib.cpp
//  DLCO_LAB_MINI_PROJEECT
//
//  Created by Sahil Shaikh on 10/14/24.
//  Roll Number 2301CS76
//  shaikh_2301CS76@iitp.ac.in
//
//

#include "opcode_lib.hpp"
#include<iostream>
#include<map>
#include<string>

pair<string , int > op (string s ){
    map<string, pair<string, int>> OPC;
    OPC["data"] = {"", 3}; OPC["ldc"] = {"00", 1}; OPC["adc"] = {"01", 1};
    OPC["ldl"] = {"02", 2}; OPC["stl"] = {"03", 2}; OPC["ldnl"] = {"04", 2};
    OPC["stnl"] = {"05", 2}; OPC["add"] = {"06", 0}; OPC["sub"] = {"07", 0};
    OPC["shl"] = {"08", 0}; OPC["shr"] = {"09", 0}; OPC["adj"] = {"0a" , 1};
    OPC["a2sp"] = {"0b" , 0}; OPC["sp2a"] = {"0c" , 0}; OPC["call"] = {"0d" , 4};
    OPC["return"] = {"0e" , 0}; OPC["brz"] = {"0f" , 4}; OPC["brlz"] = {"10" , 4};
    OPC["br"] = {"11", 4}; OPC["HALT"] = {"12", 0}; OPC["SET"] = {"" , 1};
    if (OPC.count(s)) return OPC[s];
    else return {"-1 " , -1};
}
map<string , string > lable_data;
map<string , bool > check_lable ;
string lable_address(string s){
    return lable_data[s];
}
void create_lable(string s , string address){
    lable_data[s] = address;
}
bool lable_present(string s){
    return check_lable[s];
}
void check_lable_set(string s ){
    
    check_lable[s] = true;
}
map<string, string > get_lable_file(){
    return lable_data;
}
void opc_reset (){
    lable_data.clear();
    check_lable.clear();
    return;
}
// 0 for not found 1 for found
