//
//  MarkovMatrix.cpp
//  numgamebot
//
//  Created by Alex Nichol on 4/21/14.
//  Copyright (c) 2014 Alex Nichol. All rights reserved.
//

#include "MarkovMatrix.h"

namespace numgame {

MarkovMatrix::MarkovMatrix(int count) {
  this->count = count;
  data = new double[CellCount()];
}

MarkovMatrix::MarkovMatrix(int count, double eachOdds)
  : MarkovMatrix::MarkovMatrix(count) {
  bzero(data, DataByteSize());
  // initialize a matrix for a markov chain
  for (int i = 0; i < count; i++) {
    data[i + (i * (count + 1))] = 1.0 - eachOdds;
    data[i + ((i + 1) * (count + 1))] = eachOdds;
  }
  data[(count + 1) * (count + 1) - 1] = 1;
}

MarkovMatrix::MarkovMatrix(MarkovMatrix & mat)
  : MarkovMatrix::MarkovMatrix(mat.count) {
  memcpy(data, mat.data, DataByteSize());
}

MarkovMatrix::~MarkovMatrix() {
  delete data;
}

size_t MarkovMatrix::CellCount() const {
  return (count + 1) * (count + 1);
}

size_t MarkovMatrix::DataByteSize() const {
  return sizeof(double) * CellCount();
}

MarkovMatrix MarkovMatrix::Identity(int count) {
  MarkovMatrix mat(count);
  for (int i = 0; i < count + 1; i++) {
    for (int j = 0; j < count + 1; j++) {
      mat.data[i + (j * (count + 1))] = (i == j ? 1 : 0);
    }
  }
  return mat;
}

MarkovMatrix MarkovMatrix::operator*(const MarkovMatrix & mat) const {
  MarkovMatrix result(count);
  // i is x (column), j is y (row)
  for (int i = 0; i < count + 1; i++) {
    for (int j = 0; j < count + 1; j++) {
      
      double sum = 0;
      for (int k = 0; k < count + 1; k++) {
        double val1 = data[k + (j * (count + 1))];
        double val2 = mat.data[i + (k * (count + 1))];
        sum += val1 * val2;
      }
      result.data[i + (j * (count + 1))] = sum;
      
    }
  }
  return result;
}

MarkovMatrix & MarkovMatrix::operator=(const MarkovMatrix & mat) {
  assert(mat.count == count);
  memcpy(data, mat.data, DataByteSize());
  return *this;
}

double MarkovMatrix::EndProbability(int total) const {
  MarkovMatrix matrix(count);
  matrix = Identity(count);
  for (int i = 0; i < total; i++) {
    matrix = (*this) * matrix;
  }
  return matrix.data[count * (count + 1)];
}

std::ostream & operator<<(std::ostream & stream, const MarkovMatrix & mat) {
  stream << "[";
  for (int i = 0; i < mat.count + 1; i++) {
    if (i != 0) stream << "; ";
    for (int j = 0; j < mat.count + 1; j++) {
      if (j != 0) stream << " ";
      stream << mat.data[j + (i * (mat.count + 1))];
    }
  }
  stream << "]";
  
  return stream;
}

}