//
//  support_lib.cpp
//  DLCO_LAB_MINI_PROJEECT
//
//  Created by Sahil Shaikh on 10/14/24.
//  Roll Number 2301CS76
//  shaikh_2301CS76@iitp.ac.in
//
//

#include "support_lib.hpp"
#include<iostream>
#include<map>
#include<algorithm>
#include<string>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;


string intToHex(int num) {

    stringstream ss;

    ss << hex << setw(8) << setfill('0') << num;

    return ss.str();
}

string machine_code_inttohex(int num) {
    
    if(num < 0){
        stringstream ss;
        ss << hex << setw(6) << setfill('0') << num;
        string tempss;
        getline(ss , tempss);
        reverse(tempss.begin(), tempss.end());
        tempss.pop_back();
        tempss.pop_back();
        reverse(tempss.begin(), tempss.end());
        return tempss;
    }

    stringstream ss;
    ss << hex << setw(6) << setfill('0') << num;
//    string tempss;
//    getline(ss , tempss);
    return ss.str();
}

int hexToDecimal( string& hexStr) {
       int32_t result = stoi(hexStr, nullptr, 16);
       if (result & 0x800000) { // if the highest bit (for 24 bits) is set
           result |= 0xFF000000; // extend the sign to 32 bits
       }
       return result;
}


