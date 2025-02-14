//
//  reading_lib.hpp
//  DLCO_LAB_MINI_PROJEECT
//
//  Created by Sahil Shaikh on 10/14/24.
//

#ifndef reading_lib_hpp
#define reading_lib_hpp

#include <stdio.h>
#include "opcode_lib.hpp"
#include<iostream>
#include<map>
#include<string>
#include <fstream>

using namespace std ;
void normalize_string(string &s);
bool firstpass(string &name);
void second_pass(string &name);
#endif /* reading_lib_hpp */
