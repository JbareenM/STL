//
//  Monom_Comperator.hpp
//  STL
//
//  Created by Jeme Jbareen on 6/9/19.
//  Copyright © 2019 Jeme Jbareen. All rights reserved.
//

#ifndef Monom_Comperator_hpp
#define Monom_Comperator_hpp
bool compare(const Monom &m0,const Monom &m1) {
    return m1.get_power() < m0.get_power();
}
#endif /* Monom_Comperator_hpp */
