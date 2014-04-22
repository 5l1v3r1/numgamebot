//
//  main.cpp
//  numgamebot
//
//  Created by Alex Nichol on 4/21/14.
//  Copyright (c) 2014 Alex Nichol. All rights reserved.
//

#include <iostream>
#include "MarkovMatrix.h"

using namespace numgame;

int main(int argc, const char * argv[]) {
  MarkovMatrix * mat = new MarkovMatrix(2, 0.1);
  std::cout << "the odds of getting at least two 2's in 8 tries are "
    << mat->EndProbability(8) << std::endl;

  delete mat;
  mat = new MarkovMatrix(3, 0.1);
  std::cout << "the odds of getting at least three 3's in 4 tries are "
    << mat->EndProbability(4) << std::endl;
  std::cout << "the odds of getting at least three 3's in 3 tries are "
    << mat->EndProbability(3) << std::endl;
}
