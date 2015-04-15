#include "nevil/util/parser.hpp"

nevil::args nevil::parser::read_json(char* path)
{
  std::cout << "Reading config from \""<< path << "\"..." << std::endl;
  
  std::ifstream file(path);
  if(!file.is_open())
  {
    std::cerr << "Failed to open \""<< path << "\"" << std::endl;
    exit(1);
  }

  nevil::args cl_args;
  Json::Value root;
  Json::Reader reader;
  if(!reader.parse(file, root, false))
  {
    std::cerr << reader.getFormatedErrorMessages() << std::endl;
    exit(-1);
  }
  file.close();

  for (Json::ValueIterator it = root.begin(); it != root.end(); ++it)
    cl_args[it.key().asString()] = it->asString();
  return cl_args;
}

nevil::args nevil::parser::read_cl(int argc, char *argv[])
{
  nevil::args cl_args;
  for (int i = 1; i < argc; ++i)
  {
    if (argv[i][0] == '-')
    {
      std::string arg_name = std::string(argv[i]);
      //Erasing the starting dash
      arg_name.erase(arg_name.begin());
      // Default value for flags
      std::string arg_value = "true";
      ++i;
      if (i < argc && argv[i][0] != '-')
          arg_value = std::string(argv[i]);
      else
        --i;
      cl_args[arg_name] = arg_value;
    }
  }
  return cl_args;
}

nevil::args nevil::parser::parse_cl_args(int argc, char *argv[])
{
    nevil::args cl_args;
    if(argc < 2)
      std::cerr << "Warning: No configuration found!" << std::endl;
    else if (std::string(argv[1]).find(".json") != std::string::npos)
      cl_args = read_json(argv[1]);
    else
      cl_args = read_cl(argc, argv);

    std::cout << "Arguments read: \n" << cl_args;
    return cl_args;
}