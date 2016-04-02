#include "tetravex_generator.hh"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

void generator(int size, std::string output)
{
  if (size > 1)
  {
    std::vector<std::vector<std::vector<int>>> mat(size,
      std::vector<std::vector<int>>(size,
      std::vector<int>(4)));
    for (int i = 0; i < size; ++i)
    {
      for (int j = 0; j < size; ++j)
      {
        for (int k = 0; k < 4; ++k)
          mat[i][j][k] = -1;
      }
    }

    for (int i = 0; i < size; ++i)
    {
      for (int j = 0; j < size; ++j)
      {
        if (i != 0)
          mat[i][j][3] = mat[i - 1][j][2];
        else if (j != 0)
          mat[i][j][2] = mat[i][j - 1][0];
        else
        {
          if (mat[i][j][0] == -1)
            mat[i][j][0] = rand() % 10;
          if (mat[i][j][1] == -1)
            mat[i][j][1] = rand() % 10;
          if (mat[i][j][2] == -1)
            mat[i][j][2] = rand() % 10;
          if (mat[i][j][3] == -1)
            mat[i][j][3] = rand() % 10;
        }
      }
    }
    write_to_file(size, output, mat);
  }
}

void write_to_file(int size, std::string output, std::vector<std::vector
  <std::vector<int>>> mat)
{
  std::ofstream output_file;
  output_file.open(output);
  output_file << size << "\n";
  for (int i = 0; i < size; ++i)
  {
    for (int j = 0; j < size; ++j)
    {
      for (int k = 0; k < 4; ++k)
      {
        output_file << mat[i][j][k];
        if (k != 3)
          output_file << " ";
        else
          output_file << "\n";
      }
    }
  }
}
