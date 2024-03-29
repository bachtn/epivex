#include "option_parser.hh"

Parser::Parser(int argc, char *argv[])
{
    bpo::options_description desc_("Options");
    desc_.add_options()
      ("help,h", "Display the help")
      ("output,o", bpo::value<std::string>()->default_value("out"),
        "Generate/solve puzzle in file out.vex")
      ("input,i", bpo::value<std::string>(), "Solve puzzle in file in.vex")
      ("size,s", bpo::value<int>()->default_value(3), "Size of the tetravex");

    try
    {
      bpo::store(bpo::parse_command_line(argc, argv, desc_), vm_);
      bpo::notify(vm_);
    }
    catch (std::exception& e)
    {
      std::cerr << desc_;
      exit(2);
    }

    combination_checker(desc_);

    size_setter();
    output_setter();
    input_setter();
    if (vm_.count("input"))
    {
      valid_input_file();
      valid_file_formating(input_);
      if (!vm_.count("output"))
        solver(input_tetra_, input_);
      else
        solver(input_tetra_, output_);
    }

    if (vm_.count("help"))
    {
      std::cout << desc_ << "\n";
    }
}

void Parser::size_setter()
{
  if (vm_.count("size"))
  {
    size_ = vm_["size"].as<int>();
  }
}

void Parser::output_setter()
{
  if (vm_.count("output"))
  {
    output_ = vm_["output"].as<std::string>();
    if (!vm_.count("input"))
    {
      if (vm_["output"].defaulted())
      {
        output_ = output_ + ".vex";
        generator(size_, output_);
      }
      else
        generator(size_, output_);
    }
  }
}

void Parser::input_setter()
{
  if (vm_.count("input"))
  {
    input_ = vm_["input"].as<std::string>();
  }
}
int Parser::size_get()
{
  return size_;
}

std::string Parser::output_get()
{
  return output_;
}

std::string Parser::input_get()
{
  return input_;
}

Tetravex& Parser::input_tetra_get()
{
  return input_tetra_;
}

void  Parser::print_values()
{
  std::cout << "output = " << output_ << "\n"
            << "input = " << input_ << "\n"
            << "size_ = " << size_ << "\n";
}

void Parser::combination_checker(bpo::options_description desc)
{
  if ((vm_.count("input") && !vm_["input"].defaulted()
      && vm_.count("size") && !vm_["size"].defaulted())
      ||
      (vm_.count("help") && vm_.count("input") && !vm_["input"].defaulted())
      ||
      (vm_.count("help") && vm_.count("output") && !vm_["output"].defaulted())
      ||
      (vm_.count("help") && vm_.count("size") && !vm_["size"].defaulted()))
  {
    std::cerr << desc;
    exit(2);
  }
}

void Parser::valid_input_file()
{
  std::ifstream input_file(input_);
  if (input_file.fail())
    exit(3);
}

void Parser::valid_file_formating(std::string str)
{
  std::ifstream file_in;
  file_in.open(str);
  std::string line;
  if (file_in.is_open())
  {
    while (std::getline(file_in, line) && count_character(line) == 0)
      continue;
    if (count_character(line) != 1)
      exit(4);
    int tetra_size = std::stoi(line);
    std::vector<std::vector<int>> tetra_vect(pow(tetra_size, 2),
      std::vector<int>(4));
    int tile_nbr = 0;
    while (std::getline(file_in, line) && tile_nbr < pow(tetra_size, 2))
    {
      int char_nbr = count_character(line);
      if (char_nbr == 4)
      {
        int tile_elt_nbr = 0;
        tile_nbr++;
        for (unsigned i = 0; i < line.length(); ++i)
        {
          if (line[i] != ' ')
          {
            tetra_vect[tile_nbr - 1][tile_elt_nbr] = line[i] - '0';
            tile_elt_nbr++;
          }
        }
      }
      else if (char_nbr != 0)
      {
        exit(4);
      }
    }
    if (tile_nbr != pow(tetra_size, 2))
    {
      exit(4);
    }
    input_tetra_.size_set(tetra_size);
    input_tetra_.vect_set(tetra_vect);
    file_in.close();
  }
  else
    exit(3);
}

int Parser::count_character(std::string line)
{
  int char_nbr = 0;
  for (unsigned i = 0; i < line.length(); ++i)
  {
    if (line[i] != ' ')
      char_nbr++;
  }
  return char_nbr;
}
