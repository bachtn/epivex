#include "bdd.hh"
#include <iostream>

void solver(Tetravex tetra, std::string output)
{
  int sol = 0;
  struct tool tl;
  int size = tetra.size_get();
  tl.tile_vect = tetra.vect_get();
  /************ CREATE THE FIRST NODE **************/
  // Create the matrix for the node and initialize it to -1
  std::vector<std::vector<int>> mat(size, std::vector<int>(size));
  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j)
        mat[i][j] = -1;
  // Cursor
  std::pair<int, int> cursor = std::make_pair(0,0);
  // Create the cursor matrix set the cursor case to 1 and the others to 0
  std::vector<std::vector<int>> curs_vect(size, std::vector<int>(size));
  curs_vect[cursor.first][cursor.second] = 1;
  // Create the node
  Node first_node(mat, curs_vect, cursor, size * size, size * size,
    size * size);
  // push the node in the matrix
  tl.node_queue.push(first_node);
  /************** Start treatment ***************/
  while (tl.node_queue.size() != 0)
  {
    // Get the first node in the queue and drop it
    auto node = tl.node_queue.front();
    tl.node_queue.pop();
    int empty = node.empty_get();
    auto mat = node.mat_get();
    // Check if it is a terminal node
    if (empty == 0)
    {
      if (mat_is_valid(mat, size, &tl))
      {
        write_to_file_sol(size, output + "_sol_" + std::to_string(sol) + ".vex",
          mat, &tl);
        sol++;
        std::cout << "valid node\n";
      }
      else
        std::cout << "invalid node\n";
    }
    else
    {
      for (int i = 0; i < size; ++i)
      {
        for (int j = 0; j < size; ++j)
          std::cout << mat[i][j] << " ";
        std::cout << "\n";
      }
      cursor = node.cursor_get();
      curs_vect = node.curs_vect_get();
      int tile_nbr = node.tile_nbr_get();
      int tag = node.tag_get();
      /********** Right Node manager *********/
      if (tag != 1)
      {
        auto right_curs_vect = curs_vect;
        std::pair<int, int> right_cursor = cursor_manager(false, cursor,
          right_curs_vect, size);
        Node right_node(mat, right_curs_vect, right_cursor, tile_nbr, empty,
                        tag - 1);
        //std::cout << "right node\n";
        tl.node_queue.push(right_node);
      }

      /********** Left Node manager **********/
      if (empty != 0)
      {
        auto left_curs_vect = curs_vect;
        // Insert the element in the left node matrix
        vect_2_int mat_left(size, std::vector<int>(size));
        for (int i = 0; i < size; ++i)
          for (int j = 0; j < size; ++j)
            mat_left[i][j] = mat[i][j];
        mat_left[cursor.first][cursor.second] = tile_nbr - 1;
        // Check if the matrix is valid
        if (mat_is_valid(mat_left, size, &tl))
        {
          // Manger the cursor in the insertion case
          std::pair<int, int> left_cursor = cursor_manager(true, cursor,
              left_curs_vect, size);
          Node left_node(mat_left, left_curs_vect, left_cursor, tile_nbr - 1, empty -1,
              empty - 1);
          tl.node_queue.push(left_node);
        }
      }
    }
  }
  if (sol == 0)
    exit(1);
}

std::pair<int, int> cursor_manager(bool insert, std::pair<int, int> cursor,
                   std::vector<std::vector<int>>& curs_vect, int size)
{
  int nbr_iter = size * size;
  if (insert)
  {
    // set the current cursor case to 1 because we inserted an elt in this case
    curs_vect[cursor.first][cursor.second] = 1;
  }
  else
  {
    curs_vect[cursor.first][cursor.second] = 0;
    if (cursor.second < size - 1)
      cursor.second++;
    else
    {
      if (cursor.first < size -1)
      {
        cursor.first++;
        cursor.second = 0;
      }
      else
      {
        cursor.first = 0;
        cursor.second = 0;
      }
    }
  }
  while (nbr_iter > 0)
  {
    while (cursor.second < size)
    {
      if (curs_vect[cursor.first][cursor.second] == 0)
      {
        curs_vect[cursor.first][cursor.second] = 1;
        return std::make_pair(cursor.first, cursor.second);
      }
      cursor.second++;
      nbr_iter--;
    }
    cursor.first = cursor.first == size - 1 ? 0 : cursor.first + 1;
    cursor.second = 0;
  }
  return std::make_pair(-1, -1);
}

bool mat_is_valid(vect_2_int mat, int size, struct tool *tl)
{
  for (int i = 0; i < size; ++i)
  {
    for (int j = 0; j < size; ++j)
    {
      if (i != 0 && mat[i][j] != -1 && mat[i - 1][j] != -1)
      {
        if (get_tile(mat[i][j], tl)[2] != get_tile(mat[i - 1][j], tl)[0])
          return false;
      }
      if (j != 0 && mat[i][j] != -1 && mat[i][j - 1] != -1)
      {
        if (get_tile(mat[i][j], tl)[3] != get_tile(mat[i][j - 1], tl)[1])
          return false;
      }
    }
  }
  return true;
}

vect_int get_tile(int tile_nbr, struct tool *tl)
{
  return tl->tile_vect[tile_nbr];
}

void write_to_file_sol(int size, std::string output,
  std::vector<std::vector<int>> mat, struct tool *tl)
{
  std::ofstream output_file;
  output_file.open(output);
  output_file << size << "\n";
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      auto tile = tl->tile_vect[mat[i][j]];
      for (int k = 0; k < 4; ++k)
      {
        output_file << tile[k];
        if (k != 3)
          output_file << " ";
        else
          output_file << "\n";
      }
    }
  }
}
