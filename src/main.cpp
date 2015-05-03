#include "nevil/util/system.hpp"
#include "nevil/util/parser.hpp"
#include <chrono>

// Default output path
const std::string DEFAULT_OUTPUT_PATH = "results";
void set_output_path(nevil::args &cl_args);

#ifdef GUI
#include <QApplication>
#include "nevil/gui/view.hpp"
#include "nevil/trial_controller.hpp"

/**
* Main for GUI simulator
*/
int main(int argc, char *argv[])
{

  using namespace nevil;

  QApplication app(argc, argv);
  args cl_args = parser::parse_cl_args(argc, argv);
  set_output_path(cl_args);

  srand(time(0));
  trial_controller controller (1, rand(), cl_args);
  controller.run();

  return app.exec();
}

#else

#include "nevil/parallel/parallel_simulator.hpp"

/**
* Main for parallel simulator
*/
int main(int argc, char *argv[])
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  using namespace nevil;

  args cl_args = parser::parse_cl_args(argc, argv);
  set_output_path(cl_args);
  parallel::simulator(cl_args);

  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_time = end - start;
  std::cout << "elapsed time: " << elapsed_time.count() / 60.0 << std::endl;
  return 0;
}

#endif

/**
* Creates and sets the result directory.
* @param nevil::Args parsed program arguments.
* @return
*/
void set_output_path(nevil::args &cl_args)
{
  using namespace nevil;
  // Set output directory to default if user didn't specify one.
  args::const_iterator it;
  if ((it = cl_args.find("output")) != cl_args.end())
    cl_args["output"] = it->second;
  else
    cl_args["output"] = DEFAULT_OUTPUT_PATH;

  os::create_directory(cl_args["output"]);
  
  if ((it = cl_args.find("xp_path")) != cl_args.end())
    cl_args["xp_path"] =os::append_path(cl_args["output"], it->second);
  else
    cl_args["xp_path"] = os::append_path(cl_args["output"], os::get_time_name_dir());

  // Creating the trial path directory
  os::create_directory(cl_args["xp_path"]);
}

