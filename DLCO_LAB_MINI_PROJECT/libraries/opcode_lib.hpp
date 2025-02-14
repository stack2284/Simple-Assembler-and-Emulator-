//
//  opcode_lib.hpp
//  DLCO_LAB_MINI_PROJEECT
//
//  Created by Sahil Shaikh on 10/14/24.
//

#ifndef opcode_lib_hpp
#define opcode_lib_hpp

#include <stdio.h>
#include<iostream>
#include<map>
#include<string>
using namespace std;

pair<string , int > op (string s );
string lable_address(string s);
void create_lable(string s , string address);
bool lable_present(string s);
void check_lable_set(string s);
map<string, string > get_lable_file();
void opc_reset ();
#endif /* opcode_lib_hpp */
