//
//  Test.cpp
//  Copyright 2019 Yingan Wang
//
//  example-calibration copy
//
//  Created by vivianfca on 4/28/19.
//

#include <stdio.h>
#define CATCH_CONFIG_RUNNER
#include "./catch.h"
#include "../src/Transformation.hpp"


int main(int argc, char *argv[]) {
    int r = Catch::Session().run(1, argv);
    return r;
}
