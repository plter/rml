//
//  main.cpp
//  T002Print
//
//  Created by plter on 1/16/15.
//  Copyright (c) 2015 plter. All rights reserved.
//

#include <iostream>
#include <rml.h>

using namespace std;

int main() {

    rml::FuncContext c(nullptr);
    c.runFile("app.xml");
    return 0;
}
