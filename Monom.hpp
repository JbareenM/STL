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

namespace ariel{
    //https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
    std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
        return str;
    }
    class Monom:public function{
    public:
        double get_coefficient() const{return _coefficient;}
        int get_power() const{return _power;}
        /**
         *function that check if two monoms are equal
         */
        bool operator==(const Monom &m1) {
            if(_coefficient != m1._coefficient || _power != m1._power)
                return false;
            return true;
        }
        bool operator!=(const Monom &m1) {
            return !(*this==m1)
            ;    }
        /**
         * function that returns the result of a monom in a random x
         */
        double f(double x) {
            return _coefficient*pow(x, _power);
        }
        /**
         *constructor
         */
        Monom(const string s) {
            std::istringstream(s)>>*this;
        }
        /**
         *a function that multiples two monoms
         */
        const Monom operator*(const Monom &ot) const{
            /**
             * multiple the two cofficents
             */
            Monom m;
            m._coefficient=_coefficient*ot._coefficient;
            /**
             * add the two powers
             */
            m._power=_power+ot._power;
            return m;
        }
        /**
         *     function that compute the dervivate of a monom
         */
        const Monom derivative() const{
            Monom m;
            m._coefficient=_coefficient*_power;
            m._power=_power-1;
            return m;
        }
        /**
         *function that add two monoms
         */
        const Monom operator+(const Monom &ot) const{
            /**
             * if the power of the monoms is not equal they can not be added
             */
            Monom m;
            if (ot._power != _power)throw ("error could not add diffrent power");
            m._coefficient=_coefficient+ot._coefficient;
            m._power=_power;
            return m;
        }
        /**
         *function that substracts two monoms
         */
        const Monom operator-(const Monom &ot) const{
            /**
             * if the power of the monoms is not equal they can not be added
             */
            Monom m;
            if (ot._power != _power)throw ("error could not add diffrent power");
            m._coefficient=_coefficient - ot._coefficient;
            m._power=_power;
            return m;
        }
        const Monom operator-() const{
             return Monom(-_coefficient,_power);
        }
        /**
         *constructor
         */
        Monom(double a=0, int b=0):_coefficient(a),_power(b){
            if (b < 0) throw ("error have to be greater than 0");
        }
        /**
         * copy constructor
         */
        Monom(const Monom &ot) {
            _coefficient = ot._coefficient;
            _power = ot._power;
        }
        friend std::ostream &operator<<(std::ostream& out,const Monom &m);
        friend std::istream &operator>>(std::istream& is,Monom &m);
        //****************** Private Methods and Data *****************
    private:
        double _coefficient;
        int _power;
    };
    std::ostream &operator<<(std::ostream& out,const Monom &m) {
        if(m._coefficient == 0)
            return out<<"0";
        else if(m._power == 0)
            return out<< m._coefficient ;
        else if(m._power == 1)
            return out<< m._coefficient << "X";
        return out<< m._coefficient << "X^" << m._power;
    }
    std::istream &operator>>(std::istream& is, Monom &m1){
        string s;
        is>>s;
        if (s.length()==0) return is;
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
            b=0;
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
        m1._coefficient=a;
        m1._power=b;
        if(b<0) throw("error!");
        return is;
    }
};
#endif /* Monom_hpp */
