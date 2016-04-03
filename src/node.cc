#include "node.hh"

Node::Node(vect_2_int mat, vect_2_int curs_vect,std::pair<int, int> cursor,
           int tile_nbr, int empty, int tag)
: mat_(mat), curs_vect_(curs_vect), cursor_(cursor), tile_nbr_(tile_nbr),
  empty_(empty), tag_(tag)
{}

Node::vect_2_int Node::mat_get()
{
  return mat_;
}

Node::vect_2_int Node::curs_vect_get()
{
  return curs_vect_;
}

std::pair<int, int> Node::cursor_get()
{
  return cursor_;
}

int Node::tile_nbr_get()
{
  return tile_nbr_;
}

int Node::empty_get()
{
  return empty_;
}

int Node::tag_get()
{
  return tag_;
}
