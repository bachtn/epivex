#include <iostream>
#include <exception>
#include "option_parser.hh"
#include "tetravex_generator.hh"


int main(int argc, char *argv[])
{
  Parser parse(argc, argv);
  generator(parse.size_get(), parse.output_get());
  return 0;
}
