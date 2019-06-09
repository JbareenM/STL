//
//  Polynom.hpp
//  STL
//
//  Created by Jeme Jbareen on 6/9/19.
//  Copyright © 2019 Jeme Jbareen. All rights reserved.
//

#ifndef Polynom_hpp
#define Polynom_hpp
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include "function.hpp"
#include <locale>
#include "Monom.hpp"
#include "Monom_Comperator.hpp"
#include <vector>
#include "cont_function.hpp"

using std::string;


//https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

class Polynom:public cont_function {
private:
    /**
     * list of monoms
     */
    std::vector<Monom> pol;
public:
    Polynom(){
        *this;
    }
    double f(double x) {
        std::vector<Monom>::iterator iterV;
        double ans = 0;
        for (iterV = pol.begin(); iterV < pol.end(); iterV++){
            Monom m(*iterV);
            ans+=m.f(x);
        }
        return ans;
    }
    /**
     * function that add two polynoms
     */
    Polynom& operator+(const Polynom &p1) {
        for (auto v:p1.pol){
            *this+v;
        }
        return *this;
    }
    /**
     * function that add a monom to a polynom
     */
    Polynom& operator+(const Monom &m1) {
        bool found_power = false;

        if(m1.get_coefficient()==0)
            return *this;
        /**
         *check if v has a next monom
         */
        for (int i=0;i<pol.size();i++) {
            /**
             *check if power is equal
             */
            if (pol[i].get_power() == m1.get_power()) {
                pol[i]+m1;
                found_power = true;
                /**
                 *check if c coefficient is zero
                 if yes then remove the monom from the polynom
                 */
                if (pol[i].get_coefficient() == 0)
                    pol.erase(pol.begin()+i);
            }
        }
        /**
         *check if there is not a simular power
         */
        if (!found_power) {
            /**
             * add the new monom to the polynom
             */
            pol.push_back(m1);
            /**
             *sort the polynom by powers
             */
            sort(pol.begin(),pol.end(),compare);
        }
        return *this;
    }
    /**
     * function that delete monom from polynom
     */
    Polynom& operator-(const Monom &m1) {
        bool found_power = false;
        /**
         * check if there is power and the v has a next monom
         */
        for (int i=0;i<pol.size();i++) {
            /**
             *check if power is equal
             */
            if (pol[i].get_power() == m1.get_power()) {
                pol[i]-m1;
                found_power = true;
                /**
                 *check if c coefficient is zero
                 if yes then remove the monom from the polynom
                 */
                if (pol[i].get_coefficient() == 0)
                    pol.erase(pol.begin()+i);
            }
        }
        if (!found_power) {
            Monom m2(m1.get_coefficient() * -1, m1.get_power());
            pol.push_back(m2);
            sort(pol.begin(),pol.end(),compare);
        }
        return *this;
    }
    
    /**
     *function that substracts two polynoms
     */
    Polynom& operator-(const Polynom &p1) {
        for (auto v:p1.pol){
            *this-v;
        }
        return *this;
    }
    /**
     * function that multiple two polynoms and returns the new polynom
     */
    Polynom& operator*(const Polynom &p1) {
        if(!isZero() && !p1.isZero()) {
            Polynom copy;
            Polynom h=*this;
            h*p1.pol[0];
            copy=h;
            for(int i=1;i<p1.pol.size();i++){
                h=*this;
                h*p1.pol[i];
                copy+h;
            }
            *this=copy;
        }
        return *this;
    }
    /**
     * function that multiple two monoms
     */
    Polynom& operator*(const Monom &m1) {
        if(m1.get_coefficient()==0)
            pol.clear();
        else {
            for(int i=0;i<pol.size();i++) {
                pol[i]*m1;
            }
        }
        return *this;
    }
    /**
     *function that returns the size of the polynom
     */
    int size() const{
        return pol.size();
    }
    
    /**
     *function that check if all the monoms in the two polynoms are equal
     */
    bool operator==(const Polynom &p1) {
        bool ans = false;
        /**
         *if the size of the two polynoms is equal ans=true
         */
        if(size() == p1.size()) {
            ans = true;
            std::vector<Monom>::iterator iter0;
            /**
             *if ans=true and iter0 has a next monom do
             */
            iter0=pol.begin();
            for(auto iter1:p1.pol) {
                Monom m0(*iter0);
                Monom m1(iter1);
                iter0++;
                /**
                 * if m0 is not equal to m1 ans=false
                 */
                if(!m0.equals(m1)) {
                    ans = false;
                }
            }
        }
        return ans;
    }
    
    
    /**
     *function that check if the polynom is a zero polynom
     */
    bool isZero() const{
        if (pol.size() == 0)
            return true;
        return false;
    }
    
    /**
     *function that returns the diffrence
     */
    double root(double x0, double x1, double eps) {
        double f0 = f(x0);
        double f1 = f(x1);
        if (f0 * f1 > 0){
            throw("ERROR: x1 and x0 are not opposite to one another.");
        }
        double length_x = abs(x0 - x1);
        double length_y = abs(f0 - f1);
        while (length_x > eps || length_y > eps) {
            double mid_x = (x0 + x1) / 2;
            double mid_y = f(mid_x);
            double value = f0 * mid_y;
            if (value < 0){
                x1 = mid_x;
                f1 = f(x1);
            }
            else if (value > 0){
                x0 = mid_x;
                f0 = f(x0);
            }
            else{
                return mid_x;
            }
            length_x = abs(x0 - x1);
            length_y = abs(f0 - f1);
        }
        return x1;
    }
    /**
     *function that adds new monom to the polynom
     */
    Polynom(const Polynom &p1) {
        for (auto iter : p1.pol){
            Monom m(iter);
            *this+Monom(m);
        }
    }
    /**
     *deep copy
     */
    Polynom& operator=(const Polynom &p1) {
        pol.clear();
        for(auto v:p1.pol) {
            //Monom m1(v);
            pol.push_back(v);
        }
        return *this;
    }
    /**
     * function that returns the derivative of a polynom
     */
    Polynom& derivative() {
        for(int i=0;i<pol.size();i++) {
            pol[i].derivative();
        }
        return *this;
    }
    
    /**
     * function that returns the area of the polynom
     */
    
    double area(double x0, double x1, double eps) {
        if (x0 > x1){
            throw("ERROR: Wrong values (x0 shoudl be less than x1");
        }
        double ar_under = 0; // Sum of each rectangle.
        double numOfRec = abs((x1 - x0) / eps); // Number of rectangles calculated using eps.
        double mideps = eps / 2;
        for (int i = 1; i <= numOfRec; i++){
            double Area = eps *f(x0 + mideps);
            if (Area <= 0)
            {
                ar_under += Area;
            }
            
            mideps += eps;
        }
        double under =0;
        double ar_above = 0; // Sum of each rectangle.
        numOfRec = abs((x1 - x0) / eps); // Number of rectangles calculated using eps.
        mideps = eps / 2;
        for (int i = 1; i <= numOfRec; i++)
        {
            double Area = eps * f(x0 + mideps);
            if (Area >= 0)
            {
                ar_above += Area;
            }
            
            mideps += eps;
        }
        double above= ar_above;
        return above + under;
    }
    

    /**
     * we assumed that there is a space between every polynom
     *and there is a plus between every polynom
     * and the minus in the negative polynoms are attached to the coeficients
     *
     /**
     * function that change from string to integer
     */
    Polynom(const string str) {
        int start=0,end=0;
        string st;
        st.append(ReplaceAll(str, " ", ""));
        st.append("+");
        if(st.at(0)!='+'&&st.at(0)!='-')
            st.insert(0, 1,'+');
        string s="";
        for (int i = 0; i < st.length(); i++) {
            if(i==st.length()-1)
                break;
            if(st.at(i)=='+') {
                start=i+1;
                for (int j = i+1; j < st.length(); j++) {
                    if(st.at(j)=='+'||st.at(j)=='-') {
                        end=j;
                        break;
                    }
                    else if(j==st.length()) {
                        end=st.length();
                        break;
                    }
                }
                s=st.substr(start,end);
                *this+Monom(s);
            }
            else if(st.at(i)=='-') {
                start=i;
                for (int j = i+1; j < st.length(); j++) {
                    if(st.at(j)=='+'||st.at(j)=='-') {
                        end=j;
                        break;
                    }
                    else if(j==st.length()) {
                        end=st.length();
                        break;
                    }
                }
                s=st.substr(start,end);
                *this+Monom(s);
            }
        }
    }
//    void remove(const Monom &m1) {
//        //if(!contains(m1)) throw ("value not found!");
//            std::vector<Monom>::iterator itr;
//            //itr=find(pol.begin(), pol.end(), m1);
//           //if (itr != pol.end())
//               // pol.erase(itr);
//    }
//    bool contains(const Monom& m1) {
//        std::vector<Monom>::iterator itr;
//        itr=find(pol.begin(), pol.end(), &m1);
//        if (itr != pol.end()){
//            return true;
//        }
//        return false;
//    }
    friend Polynom operator+(const Monom &a,const Polynom &b);
    friend Polynom operator*(const Monom &a,const Polynom &b);
    friend Polynom operator/(const Monom &a,const Polynom &b);
    friend std::ostream &operator<<(std::ostream& out,const Polynom &p);
    friend std::istream &operator>>(std::istream& in,Polynom &p);
};
Polynom operator+(const Monom &a,const Polynom &b){
    Polynom p=b;
    p+a;
    return p;
}
Polynom operator-(const Monom &a,const Polynom &b){
    Polynom p=b;
    p-a;
    return p;
}
Polynom operator*(const Monom &a,const Polynom &b){
    Polynom p=b;
    p*a;
    return p;
}
    std::ostream &operator<<(std::ostream& out,const Polynom &a){
    std::stringstream s;
    int i=0;
    for(auto v:a.pol) {
        Monom m(v);
        if(i==0){
            s<<m;
            i++;
        }
        else if(m.get_coefficient()>0)
            s << " + " << m;
        else if(m.get_coefficient()<0) {
            std::stringstream r;
            r<< m;
            string str=r.str();
            str.substr(1);
            s<<" - " << r.str();
        }
    }
    if(a.pol.size()==0) out<<"0";
    return out<<s.str();
}
    std::istream &operator>>(std::istream& in,Polynom &p){
    int start=0,end=0;
    string str;
    in>>str;
    string st;
    st.append(ReplaceAll(str, " ", ""));
    st.append("+");
    if(st.at(0)!='+'&&st.at(0)!='-')
        st.insert(0, 1,'+');
    string s="";
    for (int i = 0; i < st.length(); i++) {
        if(i==st.length()-1)
            break;
        if(st.at(i)=='+') {
            start=i+1;
            for (int j = i+1; j < st.length(); j++) {
                if(st.at(j)=='+'||st.at(j)=='-') {
                    end=j;
                    break;
                }
                else if(j==st.length()) {
                    end=st.length();
                    break;
                }
            }
            s=st.substr(start,end);
            p+Monom(s);
        }
        else if(st.at(i)=='-') {
            start=i;
            for (int j = i+1; j < st.length(); j++) {
                if(st.at(j)=='+'||st.at(j)=='-') {
                    end=j;
                    break;
                }
                else if(j==st.length()) {
                    end=st.length();
                    break;
                }
            }
            s=st.substr(start,end);
            p+Monom(s);
        }
    }
    return in;
}

#endif /* Polynom_hpp */
