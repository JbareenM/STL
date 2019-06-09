//
//  Demo.cpp
//  STL
//
//  Created by Jeme Jbareen on 6/9/19.
//  Copyright © 2019 Jeme Jbareen. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include "Monom.hpp"
#include "Polynom.hpp"
using namespace std;
using namespace ariel;
int main() {
    Polynom p3;
    p3+Monom(2,8);
    p3+Monom(2,7);
    p3+Monom(2,5)+Monom(2,6);
    cout<<p3<<endl;
    double _coefficient1 = 5 ;
    int _pow1 = 2 ;
    double _coefficient2 = 7.8;
    int _pow2 = 7 ;
    double _coefficient3 =4 ;
    int _pow3 = 1;
    stringstream s;
    s<<_coefficient3<<"x^"<<_pow3<<"+"<<_coefficient2<<"x^"<<_pow2<<"+"<<_coefficient1<<"x^"<<_pow1;
    Polynom p(s.str());
    cout<<p<<endl;
    try{
        Monom m(5,-1);
        cout<<m<<endl;
    }catch(...){
        cout<<"error!"<<endl;
    }
    return 0;
}
