//
//  Monom.hpp
//  STL
//
//  Created by Jeme Jbareen on 6/9/19.
//  Copyright © 2019 Jeme Jbareen. All rights reserved.
//

#ifndef Monom_hpp
#define Monom_hpp
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include "function.hpp"
#include <locale>
using std::string;


class Monom:public function{
public:
    double get_coefficient() const{return _coefficient;}
    int get_power() const{return _power;}
    /**
     *function that check if two monoms are equal
     */
    bool equals(const Monom &m1) {
        if(_coefficient != m1._coefficient || _power != m1._power)
            return false;
        return true;
    }
    /*
     * cofficient=a
     */
    void set_coefficient(double a){
        _coefficient = a;
    }
    /**
     *power =p
     */
    void set_power(int p) {
        _power = p;
    }
    /**
     * function that returns the result of a monom in a random x
     */
    double f(double x) {
        return _coefficient*pow(x, _power);
    }
    /**
     *constructor
     */
    Monom(string s) {
        Monom th = init_from_String(s);
        set_coefficient(th._coefficient);
        set_power(th._power);
    }
    /**
     *a function that multiples two monoms
     */
    Monom& operator*(const Monom &ot) {
        /**
         * multiple the two cofficents
         */
        set_coefficient(_coefficient*ot._coefficient);
        /**
         * add the two powers
         */
        set_power(_power+ot._power);
        return *this;
    }
    /**
     *     function that compute the dervivate of a monom
     */
    Monom& derivative() {
        set_coefficient(_coefficient*_power);
        set_power(_power-1);
        return *this;
    }
    /**
     *function that add two monoms
     */
    Monom& operator+(const Monom &ot) {
        /**
         * if the power of the monoms is not equal they can not be added
         */
        if (ot._power != _power)throw ("error could not add diffrent power");
        set_coefficient(_coefficient+ot._coefficient);
        return *this;
    }
    /**
     *function that substracts two monoms
     */
    Monom& operator-(const Monom &ot) {
        /**
         * if the power of the monoms is not equal they can not be added
         */
        if (ot._power != _power)throw ("error could not add diffrent power");
        set_coefficient(_coefficient - ot._coefficient);
        return *this;
    }
    /**
     *constructor
     */
    Monom(double a=0, int b=0){
        set_coefficient(a);
        set_power(b);
        if (b < 0) throw ("error have to be greater than 0");
    }
    /**
     * copy constructor
     */
    Monom(const Monom &ot) {
        if (ot._coefficient==0 && ot._power==0) throw ("error can not be null");
        else    {
            _coefficient = ot._coefficient;
            _power = ot._power;
        }
    }
    friend std::ostream &operator<<(std::ostream& out,const Monom &m);
    //****************** Private Methods and Data *****************
private:
    double _coefficient;
    int _power;
    /**
     * function that changes the monom from string to double
     */
    Monom init_from_String(string s) {
        if (s.length()==0) throw("error can not recive null");
        double a = 0;
        int b = 0;
        std::locale loc;
        std::stringstream _in;
        for (std::string::size_type i=0; i<s.length(); ++i)
            _in << std::tolower(s[i],loc);
        string in=_in.str();
        int inx = in.find("x");
        /**
         *check if the index of the x is smaller than 0
         */
        if (inx < 0) {
            /**
             *if it is smaller then return the coefficient of the monom and change it to double
             */
            a = atof(in.c_str());
        }
        else {
            /**
             * if not create new string that is a substring from 0 to inx
             */
            string c = in.substr(0 , inx);
            /**
             * change from string to double
             */
            a = atof(c.c_str());
            /**
             * return the index of "^"
             */
            int inp = in.find("^");
            /**
             * checks if the index is smaller than 0
             */
            if (inp < 0) {
                /**
                 *new string that is a substring from inx+1 to the end of (s)
                 */
                string p = in.substr(inx+1);
                p = "1" + p;
                b = atoi(p.c_str());
                if (b != 1)  throw("error");
            }
            
            else {
                string v = in.substr(inp+1);
                b = atoi(v.c_str());
            }
        }
        return Monom(a,b);
        
    }
};
/**
 * function that returns s
 */
std::ostream &operator<<(std::ostream& out,const Monom &m) {
    if(m._coefficient == 0)
        return out<<"0";
    else if(m._power == 0)
        return out<< m._coefficient ;
    else if(m._power == 1)
        return out<< m._coefficient << "X";
    return out<< m._coefficient << "X^" << m._power;
}

#endif /* Monom_hpp */
