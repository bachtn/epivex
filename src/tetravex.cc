#include "tetravex.hh"

Tetravex::Tetravex()
{}

int Tetravex::size_get()
{
  return size_;
}

Tetravex::vect_vect_int Tetravex::vect_get()
{
  return vect_;
}

void Tetravex::size_set(int size)
{
  size_ = size;
}

void Tetravex::vect_set(vect_vect_int vect)
{
  vect_ = vect;
}
