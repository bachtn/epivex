#pragma once

#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <string>

#include "tetravex.hh"
#include "node.hh"

using queue_mat = std::queue<Node>;
using vect_2_int = std::vector<std::vector<int>>;
using vect_int = std::vector<int>;

struct tool
{
  queue_mat node_queue;
  vect_2_int tile_vect;
};

void solver(Tetravex tetra, std::string output);
std::pair<int, int> cursor_manager(bool insert, std::pair<int, int> cursor,
  std::vector<std::vector<int>>& curs_vect, int size);

bool mat_is_valid(vect_2_int mat, int size, struct tool *tl);
vect_int get_tile(int tile_nbr, struct tool *tl);
void write_to_file_sol(int size, std::string output,
  std::vector<std::vector<int>> mat, struct tool *tl);
