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

    valid_input_file();

    if (vm_.count("help"))
    {
      std::cout << desc_ << "\n";
    }

    print_values();
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
  if (input_file)
  {
    std::cout << "valid input file " << input_ << "\n";
    input_file.close();
  }
  else
  {
    exit(3);
  }
}
