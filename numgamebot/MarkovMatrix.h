//
//  MarkovMatrix.h
//  numgamebot
//
//  Created by Alex Nichol on 4/21/14.
//  Copyright (c) 2014 Alex Nichol. All rights reserved.
//

#ifndef __numgamebot__MarkovMatrix__
#define __numgamebot__MarkovMatrix__

#include <cstring>
#include <cassert>
#include <iostream>

namespace numgame {

class MarkovMatrix {
protected:
  double * data;
  int count;
  
  size_t CellCount() const;
  size_t DataByteSize() const;
  
  friend std::ostream & operator<<(std::ostream & stream, const MarkovMatrix & mat);
  
public:
  static MarkovMatrix Identity(int count);
  
  MarkovMatrix(int count);
  MarkovMatrix(int count, double eachOdds);
  MarkovMatrix(MarkovMatrix &);
  ~MarkovMatrix();
  
  MarkovMatrix operator*(const MarkovMatrix &) const;
  MarkovMatrix & operator=(const MarkovMatrix &);
  
  double EndProbability(int total) const;
};
  
std::ostream & operator<<(std::ostream & stream, const MarkovMatrix & mat);

}

#endif /* defined(__numgamebot__MarkovMatrix__) */
