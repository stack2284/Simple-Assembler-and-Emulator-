//
//  reading_lib.cpp
//  DLCO_LAB_MINI_PROJEECT
//
//  Created by Sahil Shaikh on 10/14/24.
//  Roll Number 2301CS76
//  shaikh_2301CS76@iitp.ac.in
//
//

#include "reading_lib.hpp"
#include "lable_lib.hpp"
#include "support_lib.hpp"
#include "opcode_lib.hpp"
#include "error_library.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int colon(string &s){
    if(s.find(':') == string :: npos)
    {
        return  -1;
    }
    else return (int )(s.find(':'));
}

void remove_comment(string &s){
    if(s.find(';') == string :: npos){
        return;
    }
    int l =(int )s.find(';');
    s.erase( s.begin() + l, s.end());
    return;
}

void normalize_string(string &s){
    
    while (s.back() == ' ' || s.back() == '\t') {
        s.pop_back();
    }
    reverse(s.begin(), s.end());
    while (s.back() == ' ' || s.back() == '\t') {
        s.pop_back();
    }
    reverse(s.begin(), s.end());
    string temp = "";
    for (int i = 0; i < s.length(); i++) {
        if(s[i] != ' '){
            temp.push_back(s[i]);
        } else if (i + 1 < s.length() && s[i + 1] != ' ') {
            temp.push_back(s[i]);
        }
    }
    s = temp;
    temp = "";
    for (int i = 0 ; i < s.length(); i++) {
        if(s[i] == ':' ){
            if(i >= 1 && s[i -1 ] != ' '){
                temp += " ";
                
            }
            temp += s[i];
            if(i + 1 < s.length() && s[i + 1] != ' '){
                temp += " ";
            }
        }else if(s[i] == ',' ){
            if(i > 1 && s[i -1 ] != ' '){
                temp += " ";
            }
            temp += s[i];
            if(i + 1 < s.length() && s[i + 1] != ' '){
                
                temp += " ";
            }
        }else temp += s[i];
    }
    s = temp;
}

bool proper_lable_name(string &s ){
    if(s[0] - 'a' >= 0 && 'z' - s[0] <= 0){
        return true;
    }
    if(s[0] - 'A' >= 0 && 'Z' - s[0] <= 0){
        return true;
    }
    return false;
}

bool firstpass(string &name){ // name of file example hello.asm
    init();
    ifstream in;
    in.open(name);
    string s ;
    int adr_pointer = 0;
    bool create_lable_file = true ;
    
    while (!in.eof()) {
        getline(in, s);
        remove_comment(s);
        normalize_string(s);
        if(s == "" ||s == "\t" || s == "\n" ){
            continue;
        }
        string lable;
        string temp = "";
        vector<string> secondary;
        int cl = colon(s);
        bool error_present = pass_one_check(s , cl , intToHex(adr_pointer));
        if(error_present == false){ // error
            adr_pointer += 1;
            create_lable_file = 0 ;
            continue;
        }else{
            adr_pointer += 1;
        }
    }
    if(create_lable_file == 0){
        return false;
    }
    create_lable_file = post_pass_one_lable_check();
    
    if(create_lable_file == 0){
        return false;
    }
    
    return true ;
}

bool isdecimal(string s){
    if(s.find_first_not_of( "+-0123456789") == string::npos){
        return true;
    }
    return false;
}

void data_machine_entry(string data , string address ,ofstream &macf){
    macf << address << " "<<machine_code_inttohex((int )stol(data))<<"   data " << data << endl;
}

void data_machine_entry_hexdata(string data , string address ,ofstream &macf){
    string datax = data ;
    reverse(data.begin(), data.end());
    data.pop_back();
    data.pop_back();
    reverse(data.begin(), data.end());
    macf << address << " "<< data <<"   data " << datax << endl;
}

void machine_code(string s , string &address , ofstream &macf , map<string , string > &lable_file){
    stringstream line(s);
    if(colon(s) != -1){
        string t;
        line >> t;
        macf << address << " ";
        macf << "         " ;
        macf << t << ":\n";
        line >> t ;
        getline(line ,t);
        normalize_string(t);
        if(t == ":"){
            return;
        }
        machine_code(t, address, macf, lable_file);
        return;
    }
    string instruction ;
    line >> instruction;
//    macf << address << " ";
    if(instruction == ""){ // no instruction
        macf << address << " "; // changed $$$
        macf << "         ";
        macf << endl;
        return ;
    }
//    if (op(instruction).first != ""){
//        macf << op(instruction).first << " ";
//    }
    
    // doing here
    if(op(instruction).second == 3){
        vector <string > data_values;
        string x = "NULL";
        while (x.size() != 0) {
            line >> x;
            data_values.push_back(x);
            line >> x ; // no commas after data
            if(x != ","){
                break;
            }
        }
        int address_int = (int ) stol(address , nullptr , 16);
        address_int -= 1 ;
        address = intToHex(address_int);
        for(auto it : data_values){
            address_int = (int )stol("0x" + address , nullptr , 16);
            address_int += 1 ;
            address = intToHex(address_int);
            if(isdecimal(it)){
                data_machine_entry(it, address, macf);
            }else{
                data_machine_entry_hexdata(it , address , macf);
            }

        }

        
        
        
        return;
        
    }
    macf << address << " ";
    
    
    if(op(instruction).second == 0){ // no operand
        macf <<"000000";
        if (op(instruction).first != ""){
            macf << op(instruction).first << " ";
        }
        macf << s ;
        
        macf << endl;
        
        return;
    }
    string operand;
    line >> operand;
    
    
    if(ifdata(operand)){
        if(isdecimal(operand) == 1){
            macf << machine_code_inttohex((int )stol(operand)) ;
        }else{
            operand = intToHex(stoi(operand , nullptr , 16));
            reverse(operand.begin(), operand.end());
            operand.pop_back();
            operand.pop_back();
            reverse(operand.begin(), operand.end());
            macf << operand ;
        }
        if(op(instruction).first != ""){
            macf << op(instruction).first  << " " ;
        }else{
            macf << "00 " ;
        }
        macf << s ;
        macf << endl;
                return;
    }
    
    
    
    
//    else is offset and must be found in lable_data
    
    if(op(instruction).second != 4){
        string put = lable_address(operand);
        reverse(put.begin(), put.end());
        put.pop_back();
        put.pop_back();
        reverse(put.begin(), put.end());
        macf << put;
        macf << op(instruction).first << " ";
        macf << s ;
        macf << endl;
                return;
    }
    
    string lable_actual_address = lable_address(operand);
//    current address is address
    int lable_actual_address_int = (int )stol("0x" + lable_actual_address , nullptr , 16);
    int curr_address = (int ) stol("0x" + address  , nullptr , 16);
    int diff_offset = lable_actual_address_int - curr_address ;
    if(diff_offset == 0){
        infinite_loop_warning(address);
        warnings_bool(1);
    }
    string diff_offset_int = machine_code_inttohex(diff_offset);
    macf << diff_offset_int ;
    macf << op(instruction).first << " ";
    
    macf << s ;
    macf << endl;
    
    return;
    
    
    
    
    
    
    
    
}


//machine_code.txt
void second_pass(string &name){
    ifstream in ;
    in.open(name);
    map<string , string > lable_file = get_lable_file();
    ofstream lsf ;
    ofstream macf ;
    macf.open("machine_code.txt");
//    lsf.open("Users/Sahil/Documents/DLCO_LAB_MINI_PROJEECT/DLCO_LAB_MINI_PROJEECT/listing_file.txt", ios :: app);
    lsf.open("listing_file.txt", ios::app);
    int address = 0 ;
    while (!in.eof()) {
        string s;
        getline(in , s);
        remove_comment(s);
        normalize_string(s);
        if(s == "" ||s == "\t" || s == "\n" ){
            continue;
        }
        string addressinhex =intToHex(address);
        machine_code(s, addressinhex, macf, lable_file);
        address += 1 ;
    }
//    lable_file = get_lable_file();
//    for(auto it : lable_file ){
//        lsf << it.first + " " + it.second + "\n";
//    }
    macf.close();
    lsf.close();
    in.close();
    return;
}
