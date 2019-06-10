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
    try {
        Polynom p3;
        Monom m1(5,4);
        Monom m2(4,4);
        cout << p3 << endl;   // Prints "0"
        cout << (p3+Monom(2,8))<<endl;
        cout << (p3-Monom(2,7)) << endl;
        cout << (-Monom(5,4)) << endl;
        cout << (Monom(3,4)-Monom(5,4)) << endl;
        
        cout<<(p3+=m1)<<endl;
        cout<<(p3+=m2)<<endl;
        cout<<(p3*=Monom(2,0))<<endl;
        cout << p3 << endl;
        istringstream in("700X^4-5x^5+2x+5-1x");
        in>>p3;
        cout << p3 << endl;
        cout << (Monom(3,4)*Monom(5,2)) << endl;
        cout << (Monom(3,4)-Monom(5,4)) << endl;
        cout << (Monom(3,4)+Monom(5,4)) << endl;
        cout << (Monom(3,4)*Monom(5,4)) << endl;
        
        cout << boolalpha; // print booleans as strings from now on:
        cout <<(Monom(5,4)==Monom(4,4)) << endl;// Prints "false"
        cout <<(Monom(5,4)==Monom(5,4)) << endl;
        
        istringstream input("700X^4");
        input >> m1;
        cout << m1 << endl;
        cout << (m1 += Monom(4,4)) << endl;
        cout << m1<< endl;
        try {
            Monom m(5,-1);
            cout<<m<<endl;
        } catch (const std::exception& ex) {
            cout << ex.what() << endl; // Prints "Units do not match - [m] cannot be converted to [kg]"
        }
    } catch (...) {
        cout << "Unexpected exception!" << endl;
    }
    return 0;
}

