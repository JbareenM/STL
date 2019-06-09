//
//  Test.cpp
//  STL
//
//  Created by Jeme Jbareen on 6/9/19.
//  Copyright © 2019 Jeme Jbareen. All rights reserved.
//

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "Monom.hpp"
#include "Polynom.hpp"
using ariel::Monom, ariel::Polynom;
#include "badkan.hpp"

int main()
{
    badkan::TestCase testcase;
    int grade = 0;
    int signal = setjmp(badkan::longjmp_buffer);
    if (signal == 0)
    {
        Monom m1(1,1);
        Monom m2(3,4);
        Monom m3(2,4);
        Monom m4(4.5,9);
        Monom m5(100,0);
        Polynom p1;
        Polynom p2;
        testcase .setname("Monom output")
        .CHECK_OUTPUT(m1, "1X")
        .CHECK_OUTPUT(m2, "3X^4")
        .CHECK_OUTPUT(m3, "2X^4")
        .CHECK_OUTPUT(m4, "4.5X^9")
        .CHECK_OUTPUT(m5, "100");
        testcase .setname("Monom input")
        .CHECK_OK(istringstream("4x^4") >> m1)
        .CHECK_OK(istringstream("1.5x^4") >> m2)
        .CHECK_OK(istringstream("0x^4") >> m3)
        .CHECK_OK(istringstream("2.8X^18") >> m4)
        .CHECK_OK(istringstream("5") >> m5)
        .CHECK_OUTPUT(m1, "4X^4")
        .CHECK_THROWS(istringstream("4x^-1") >> m1)
        .CHECK_OUTPUT(m2, "1.5X^4")
        .CHECK_OUTPUT(m3, "0")
        .CHECK_OUTPUT(m4, "2.8X^18")
        .CHECK_OUTPUT(m5, "5");
        testcase .setname("Monom operator")
        .CHECK_OK(istringstream("4x^4") >> m1)
        .CHECK_OUTPUT(m1+m2, "5.5X^4")
        .CHECK_OUTPUT(m2+m2, "3X^4")
        .CHECK_OUTPUT(m3-m2, "-1.5X^4")
        .CHECK_OUTPUT(m3*m2, "0")
        .CHECK_OUTPUT(m2*m2, "2.25X^8")
        .CHECK_OUTPUT(m4*m2, "4.2X^22")
        .CHECK_OUTPUT(m5*m2, "7.5X^4")
        .CHECK_THROWS(m4+m1)
        .CHECK_THROWS(m5+m2);
         testcase .setname("Monom deriv")
        .CHECK_OUTPUT(m1.derivative(), "16X^3")
        .CHECK_OUTPUT(m5.derivative(), "0");
        
        testcase .setname("Polynom basic")
        .CHECK_OUTPUT(m1, "4X^4")
        .CHECK_OUTPUT(m2, "1.5X^4")
        .CHECK_OUTPUT(m3, "0")
        .CHECK_OUTPUT(m4, "2.8X^18")
        .CHECK_OUTPUT(m5, "5")
        .CHECK_OUTPUT(p1+m1+m2, "2.8X^18 + 4X^4 + 5")
        ; testcase.print();
        grade = testcase.grade();
    } else {
        testcase.print_signal(signal);
        grade = 0;
    }
    cout <<  grade << " " << "sdlghljwhtycdxfhb" << endl;
    return 0;
}
