#pragma once

#include <vector>

class Tetravex
{
  using vect_vect_int = std::vector<std::vector<int>>;
  public:
    Tetravex();
    int size_get();
    void size_set(int size);
    vect_vect_int vect_get();
    void vect_set(vect_vect_int vect);
  private:
    int size_;
    vect_vect_int vect_;
};
