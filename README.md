# NEVIL: Grandparent [![Build Status](https://travis-ci.org/ou-real/nevil-grandparent.svg)](https://travis-ci.org/ou-real/nevil-grandparent)


## Usage
You can clone this repository by running:
```bash
git clone https://github.com/ou-real/nevil-grandparent.git
```

### Compilation/Install
#### Windows
* Someone please write this

#### Unix
The binaries will be written to build folder.
```bash
cmake CMakeLists.txt <-DDEBUG=ON/OFF> <-DO=ON/OFF> <-DGUI=ON/OFF> 
make
```
Options:
* DDEBUG: for enabling debug mode. This value is OFF by default.
* DO: This flag enables O3 optimization and turns off assertions. This value is OFF by default.
* DGUI: For enabling GUI (disables multithreading). This value is OFF by default.

### Execution
You can run this application by executing the following command. The binaries are written to the build directory.
```bash
cd build
./nevil <args>
```
#### Command line arguments
This program takes command line arguments both for the simulation config and specific experiment config. You can pass any arguments (as long as they are not taken) and use them in your experiment.
#####Simulation Arguments
All arguments have default values
* `output`: The output folder for this application. `result` by default.
* `xp_path`: The path for output of that specific run only. Uses time for naming the directory by default.
* `tn`: The number of threads. By default `number_of_cores - 1`. If you use negative numbers it will use `number_of_cores - n`. You can use `0` for all cores.
* `mt`: Maximum number of trials to be simulates. 30 by default.
* `rs`: Random seed. Uses a random seed to initialize the random number generator. Note if this argument is specified, the application will only run 1 trial and uses no threading.
* `xn`: Experiment name. Default values are set in `trial_controller.cpp`: TestTrial.
* `mg`: Maximum number of generations. Default values are set in `trial_controller.cpp`: 200.
* `ms`: Maximum number of timesteps. Default values are set in `trial_controller.cpp`: 1000.
* `ps`: Population size.  Default values are set in `trial_controller.cpp`: 80.

##### JSON
You can use JSON to pass the desired command line arguments to the program.
```bash
./nevil control.json
```
JSON Example:
```javascript
{
  "tn": 1,
  "mg": 200,
  "xn": "TestTrial",
  "ms": 1000,
  "ps": 80
}
```
##### Specifying using command line
You have to use a dash `-` before the name of the argument the followed by the value.
Example
```bash
./nevil -tn 1 -ps 80 -sn true -xn TestTrial -ms 1000 -mg 200
```

### Adding Experiments
First you need to create a repository under the ou-real organization and name it nevil-<your-experiment-name>.
**Do not add any files to this repo.**

#### Forking this repository
To fork this repository you need to follow the instructions below:
```bash
git clone <your new repository>
cd <your new repository>
git remote add upstream https://github.com/ou-real/nevil-base.git
git fetch upstream
git merge upstream/master
git push origin master
```
Now you have a fork of nevil-base. 

#### Making changes
To add experiments you need to extend the following classes and provide your own implementation for **at least** the virtual methods. The files prefixed with test are place holders and can be deleted. You may follow the pattern used in test files. Here is a list of classes that you need to extend: 
* `arena` Example: `test_arena`
* `robot` Example: `test_robot`
* `individual` Example: `test_individual`
* `trial` Example: `test_trial`. You need to include this module in `trial_controller.hpp` and change the type of `* _trial` to `nevil::your_trial`
* You also need to make a population class Example: `test_population`

You can look at other experiments in this [organization](https://github.com/ou-real) as a guide.

#### Keep up to date with nevil-base
Too keep your code up to date with this repository, you can follow the instructions on [syncing a fork](https://help.github.com/articles/syncing-a-fork/) to cherry pick the changes that are made to `nevil-base`. This will not override your changes.

## Dependencies
* [GCC](https://gcc.gnu.org) or [Clang](http://clang.llvm.org)
* [CMake](http://www.cmake.org)
* [ENKI](http://home.gna.org/enki/): Already included in the project.
* [QT4.8](http://qt-project.org/doc/qt-4.8/): Optional, to enable GUI.

### Install Dependencies

#### Windows
* Someone please write this

#### Unix
##### OS X
To install the required packages you need to have Xcode installed. For convenience, you also need to have either [HomeBrew](http://brew.sh) or [MacPorts](https://www.macports.org) installed.
To install the required packages run the following commands:
```bash
xcode-select --install
```
If you are using HomeBrew run the following commands:
```bash
brew install cmake
brew install qt
```
If you are using MacPorts run the following commands:
```bash
sudo port install cmake
sudo port install qt4-mac
```
##### Debian based Linux
To install the required packages run the following commands:
```bash
sudo apt-get install build-essential
sudo apt-get install cmake
sudo apt-get install git-core
sudo apt-get install libqt4-dev
```
## Structure
    nevil-grandparent
    ├── README.md                   - Description
    ├── .gitignore                  - Files ignore by Git
    ├── CMakeLists.txt              - Cmake file for this project
    ├── .travis.yml                 - Travis build and test file
    ├── include
    │    ├── Enki                   - The ENKI project code with some modification in CMakeFiles
    │    │    ├── enki              - Contains the ENKI library files and headers
    │    │    ├── viewer            - Contains the GUI library files and headers 
    │    │    └── ...
    │    ├── json                   - A library for reading JSON files.
    │    └── nevil                  - Contains Header files for the NEVIL project
    │         ├── arena             - Header files for simulation arena
    │         ├── gui               - Header files for GUI
    │         ├── parallel          - Header files for parallelization
    │         ├── robot-controller  - Header files for robot controllers (i.e ANN)
    │         ├── util              - Header files for utility modules
    │         └── *.hpp             - Other header files specific to the project
    └── src                         - Implementation files for the NEVIL project.
        ├── arena                   - Implementation files for simulation arena
        ├── gui                     - Implementation files for GUI
        ├── parallel                - Implementation files for parallelization
        ├── robot-controller        - Implementation files for robot controllers (i.e ANN)
        ├── util                    - Implementation files for utility modules
        └── *.cpp                   - Other implementation files specific to the project

## [Potential Bugs](https://github.com/ou-real/nevil-grandparent/issues)

## [To do](https://github.com/ou-real/nevil-grandparent/milestones)

## License
[MIT license](http://opensource.org/licenses/MIT)
