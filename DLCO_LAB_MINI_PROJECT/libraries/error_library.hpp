//
//  error_library.hpp
//  DLCO_LAB_MINI_PROJEECT
//
//  Created by Sahil Shaikh on 10/18/24.
//

#ifndef error_library_hpp
#define error_library_hpp

#include <stdio.h>
#include<iostream>
#include<map>
#include<string>
#include <fstream>
using namespace std;

bool pass_one_check(string &s , int colon,string line_number );
bool post_pass_one_lable_check();
void infinite_loop_warning (string address);
bool ifdata(string s);
void warnings_bool(bool t);
bool check_warnings_bool();
#endif /* error_library_hpp */
