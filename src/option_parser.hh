#pragma once

#include <iostream>
#include <exception>
#include "boost/program_options.hpp"
#include <fstream>

namespace bpo = boost::program_options;
class Parser
{
    public:
      Parser(int argc, char *argv[]);
      void size_setter();
      void output_setter();
      void input_setter();
      int size_get();
      std::string output_get();
      std::string input_get();
      void print_values();
      void combination_checker(bpo::options_description desc);
      void valid_input_file();
    private:
      bpo::options_description desc_;
      bpo::variables_map vm_;
      int size_;
      std::string output_;
      std::string input_;
};
