//
//  error_library.cpp
//  DLCO_LAB_MINI_PROJEECT
//
//  Created by Sahil Shaikh on 10/18/24.
//  Roll Number 2301CS76
//  shaikh_2301CS76@iitp.ac.in
//
//

#include "error_library.hpp"
#include "reading_lib.hpp"
#include "lable_lib.hpp"
#include "opcode_lib.hpp"
#include<iostream>
#include<map>
#include<vector>
#include<string>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

bool warnings = 0;

void warnings_bool(bool t){
    warnings = t ;
}

bool check_warnings_bool(){
    return  warnings;
}

bool lable(stringstream &str) {
    string lable_name ;
    str >> lable_name;
    string l ;
    str >> l;
    if( l != ":"){
        return false;
    }
    return true;
}

bool ifdata(string s){
    
    if(s.find_first_not_of( "+-0123456789") == string::npos){
        return true;
    }
    if(s[0] == '0' && s[1] == 'x' && s.length() >=2){
        reverse(s.begin(), s.end());
        s.pop_back();
        s.pop_back();
        reverse(s.begin(), s.end());
        if(s.find_first_not_of( "0123456789abcdef") == string::npos){
            return true;
        }
    }
    return false;
    
}

bool ifoffset(string s){
    return !(s.find_first_not_of( "0123456789") == string::npos);
}

bool pass_one_check(string &s , int colon, string line_number ){
    ofstream erf ;
erf.open("error.txt", ios::app);
//    erf.open("error.txt", ios::app); // xxx
    stringstream str(s) ;
    stringstream lable_func_input(s);
    if (colon != -1){
        bool cl = false;
        cl = lable(lable_func_input);
        lable_func_input.clear();
        if(cl == 0){
            erf << "Error at line 0x" << line_number << " improper lable\n";
            erf.close();
            return false;
        }
        lable_func_input.clear();
        string lable_variable;
        str >> lable_variable;
        string zci;
        str >> zci;
        if(lable_present(lable_variable) == false){
            check_lable_set(lable_variable);
            create_lable(lable_variable, line_number);
        }else{
            erf << "Error at line 0x" << line_number << " lable already defined at " << lable_address(lable_variable) << endl;
            erf.close();
            return false;
        }
        erf.close();

        
        
    }
    
    // instruction processing
    string instruction = "";
    str >> instruction;
//    cout << instruction+ "j" << line_number << endl;
    if(instruction == ""){
        erf.close();
        return true;
    }
    pair<string , int > opc_data = op(instruction);
    if(opc_data.second == -1){
        erf << "Error at line 0x" << line_number << " Unknown instruction\n";
        erf.close();
        return false;
    }
    
    vector<string > Operand ;
    string x ;
    while (str >> x) {
        Operand.push_back(x);
    }
    if(opc_data.second == 3){
        for (int i = 1 ; i < Operand.size() ; i += 2){
            if(Operand[i] != ","){
                erf << "Error at line 0x" << line_number << " expected ',' found " << Operand[i] << " \n";
                return false;
            }
        }
        return true;
    }
    
    if(opc_data.second == 0 && Operand.size() != 0)
    {
        erf << "Error at line 0x" << line_number << " Unexpected operand\n";
        erf.close();
        return false;
    }

    if(opc_data.second != 0 && Operand.size() != 1)
    {
        erf << "Error at line 0x" << line_number << " Invalid operand\n";
        erf.close();
        return false;
    }
    if(opc_data.second == 0){
        return true;
    }

    
    string temp_operand_storage = Operand[0];
    if(!ifdata(temp_operand_storage)){
        string offset = Operand[0];
        if(lable_present(offset) == 0){
            create_lable(offset, "");
        }
    }
    
    erf.close();
    
    return true;
}

bool post_pass_one_lable_check(){
    bool out = 1;
    map<string , string > lable_data = get_lable_file();
    ofstream erf ;
    erf.open("error.txt", ios::app);
//    erf.open("error.txt", ios::app); // xxx
    for(auto it : lable_data){
        if(it.second == ""){
            erf << "declaration of " << it.first <<" missing\n";
            out = 0;
        }
    }
    erf.close();
    return out;
}

void infinite_loop_warning (string address){
    ofstream erf ;
    
    erf.open("error.txt", ios::app);
//    erf.open("error.txt", ios::app); // xxx
    erf << "Warning: Infinite loop at line 0x" << address << " \n";
    
    erf.close();
    return;
}
