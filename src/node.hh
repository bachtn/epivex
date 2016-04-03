#pragma once

#include <vector>
#include <utility>

class Node
{
  using vect_int = std::vector<int>;
  using vect_2_int = std::vector<std::vector<int>>;

  public:
    Node(vect_2_int mat, vect_2_int curs_vect, std::pair<int, int> cursor,
         int tile_nbr, int empty, int tag);
    vect_2_int mat_get();
    vect_2_int curs_vect_get();
    std::pair<int, int> cursor_get();
    int tile_nbr_get();
    int empty_get();
    int tag_get();
  private:
    vect_2_int mat_;
    vect_2_int curs_vect_;
    std::pair<int, int> cursor_;
    int tile_nbr_;
    int empty_;
    int tag_;
};
