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
        Monom m6(-4,5);
        Polynom p1;
        Polynom p2;
        testcase .setname("Monom output")
        .CHECK_OUTPUT(m1, "1X")
        .CHECK_OUTPUT(m2, "3X^4")
        .CHECK_OUTPUT(m3, "2X^4")
        .CHECK_OUTPUT(m4, "4.5X^9")
        .CHECK_OUTPUT(m5, "100")
        .CHECK_OUTPUT(m6, "-4X^5")
        .CHECK_EQUAL(m1.f(5), 5)
        .CHECK_EQUAL(m2.f(3), 243)
        .CHECK_EQUAL(m3.f(2), 32)
        .CHECK_EQUAL(m5.f(3), 100)
        .CHECK_EQUAL(m6.f(5), -12500)
        .CHECK_OK(m2+=m3)
        .CHECK_OUTPUT(m2, "5X^4")
        .CHECK_OK(m2-=m3)
        .CHECK_OUTPUT(m2, "3X^4")
        .CHECK_OK(m1*=m2)
        .CHECK_OUTPUT(m1, "3X^5")
        .CHECK_EQUAL(m1!=m2, true)
        ;
        testcase .setname("Monom input")
        .CHECK_OK(istringstream("4x^4") >> m1)
        .CHECK_OK(istringstream("1.5x^4") >> m2)
        .CHECK_OK(istringstream("0x^4") >> m3)
        .CHECK_OK(istringstream("2.8X^18") >> m4)
        .CHECK_OK(istringstream("5") >> m5)
        .CHECK_OK(istringstream("-4X^5") >> m6)
        .CHECK_OUTPUT(m1, "4X^4")
        .CHECK_THROWS(istringstream("4x^-1") >> m1)
        .CHECK_OUTPUT(m2, "1.5X^4")
        .CHECK_OUTPUT(m3, "0")
        .CHECK_OUTPUT(m4, "2.8X^18")
        .CHECK_OUTPUT(m5, "5")
        .CHECK_OUTPUT(m6, "-4X^5");
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
        .CHECK_OUTPUT(p1+m1+m2+m3+m4+m5, "2.8X^18 + 5.5X^4 + 5")
        .CHECK_OUTPUT(p1, "0")
        .CHECK_OUTPUT(p1+m1-m2+m3-m4-m5, "-2.8X^18 + 2.5X^4 - 5")
        .CHECK_OK(istringstream("-2.8X^18+2.5X^4-5")>>p1)
        .CHECK_OUTPUT(p1, "-2.8X^18 + 2.5X^4 - 5");
        testcase .setname("Polynom operator")
        .CHECK_OUTPUT(p1, "-2.8X^18 + 2.5X^4 - 5")
        .CHECK_OUTPUT(p1+m2, "-2.8X^18 + 4X^4 - 5")
        .CHECK_OUTPUT(p1+m1+m2+m3+m4+m5, "8X^4")
        .CHECK_OUTPUT((p1+m1+m2+m3+m4+m5)*m5, "40X^4")
        .CHECK_OUTPUT((p1+m1+m2+m3+m4+m5)*(m3), "0")
        .CHECK_OUTPUT((p1-m2*m5+m1-m4), "-5.6X^18 - 1X^4 - 5")
        .CHECK_OUTPUT(p1*m5, "-14X^18 + 12.5X^4 - 25")
        .CHECK_OK(istringstream("1x+3")>>p1)
        .CHECK_OK(istringstream("1x+5")>>p2)
        .CHECK_OUTPUT(p1, "1X + 3")
        .CHECK_OUTPUT(p2, "1X + 5")
        .CHECK_OUTPUT(p1*m5, "5X + 15")
        .CHECK_OUTPUT(p1+p2, "2X + 8")
        .CHECK_OUTPUT(p1-p2, "-2")
        .CHECK_OUTPUT(p1*p2, "1X^2 + 8X + 15")
        .CHECK_OK(istringstream("-4x-2+1x^2")>>p1)
        .CHECK_OK(istringstream("5x+4x^3+4")>>p2)
        .CHECK_OUTPUT(p1, "1X^2 - 4X - 2")
        .CHECK_OUTPUT(p2, "4X^3 + 5X + 4")
        .CHECK_OUTPUT(p1+p2, "4X^3 + 1X^2 + 1X + 2")
        .CHECK_OUTPUT(p1-p2, "-4X^3 + 1X^2 - 9X - 6")
        .CHECK_OUTPUT(p1*p2, "4X^5 - 16X^4 - 3X^3 - 16X^2 - 26X - 8")
        .CHECK_OUTPUT(p2.derivative(), "12X^2 + 5")
        .CHECK_OUTPUT((p1-p2).derivative(), "-12X^2 + 2X - 9")
        .CHECK_EQUAL(p1.f(5), 3)
        .CHECK_EQUAL(p1.f(3), -5)
        .CHECK_EQUAL(p2.f(2), 46)
        .CHECK_EQUAL(p2.f(3), 127)
        .CHECK_EQUAL(p2.f(5), 529)
        .CHECK_OK(p1+=p2)
        .CHECK_OUTPUT(p1, "4X^3 + 1X^2 + 1X + 2")
        .CHECK_OK(p2-=p1)
        .CHECK_OUTPUT(p2, "-1X^2 + 4X + 2")
        .CHECK_OK(p1*=p2)
        .CHECK_OUTPUT(p1, "-4X^5 + 15X^4 + 11X^3 + 4X^2 + 10X + 4")
        .CHECK_OK(p1+=m2)
        .CHECK_OUTPUT(p1, "-4X^5 + 16.5X^4 + 11X^3 + 4X^2 + 10X + 4")
        .CHECK_OK(p2-=m1)
        .CHECK_OUTPUT(p2, "-4X^4 - 1X^2 + 4X + 2")
        .CHECK_OK(p1*=m5)
        .CHECK_OUTPUT(p1, "-20X^5 + 82.5X^4 + 55X^3 + 20X^2 + 50X + 20")
        ; testcase.print();
        grade = testcase.grade();
    } else {
        testcase.print_signal(signal);
        grade = 0;
    }
    cout <<  grade << " " << "sdlghljwhtycdxfhb" << endl;
    return 0;
}
