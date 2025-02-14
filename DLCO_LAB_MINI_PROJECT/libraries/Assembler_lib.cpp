//
//  Assembler_lib.cpp
//  DLCO_LAB_MINI_PROJEECT
//
//  Created by Sahil Shaikh on 10/21/24.
//  Roll Number 2301CS76
//  shaikh_2301CS76@iitp.ac.in
//

#include "Assembler_lib.hpp"
#include "iostream"
#include<string>
#include "reading_lib.hpp"
#include "error_library.hpp"
#include "emu_lib.hpp"

using namespace std ;

void asm_file (string &s ){
    //    string g ="code.txt";
    bool error = firstpass(s);
    if(error) {
        second_pass(s);
        ofstream lsf ;
        lsf.open("listing_file.txt", ios::app);
        map<string , string >lable_file = get_lable_file();
        for(auto it : lable_file ){
            lsf << it.first + " " + it.second + "\n";
        }
    }
    else {
        cout << "errors encountered check file\n";
        return;
    }
    if(error && !check_warnings_bool()){
        cout << "code compiled succesfully \n";
    }
    else if(error && check_warnings_bool()){
        cout << "code compiled with Warnings \n";
    }
    else{
        cout << "errors encountered check file\n";
    }
    return ;
}

void run (string s){
    cout << "runtype : \n -mac or -emu \n";
//    string s ;
//    cin >>s ;
    string runtype;
    cin >> runtype;
    if(runtype == "-mac"){
        asm_file(s);
    }else if (runtype == "-emu") {
        emu(s);
    }else{
        cout << "Wrong format \n";
        run(s);
        return;
    }
}
