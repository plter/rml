//
//  main.cpp
//  T002Print
//
//  Created by plter on 1/16/15.
//  Copyright (c) 2015 plter. All rights reserved.
//

#include <iostream>
#include "RMLContext.h"

using namespace std;

int main() {
    
    rml::Context c;
    c.runFile("app.xml");
    return 0;
}
