#include "comfyscript.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>

class cfs::scriptrunner::_sr_impl_ {
public:
  std::vector<function> functions;
  std::vector<variable> variables;
  std::vector<type>     types;

  cfs::script_type tname;
};

cfs::scriptrunner::scriptrunner()
  : _impl{new _sr_impl_()} {
  alive = true;
}

cfs::scriptrunner::scriptrunner(const std::string& file)
  : _impl{new _sr_impl_()} {
  alive = true;
  load(file);
}

bool cfs::scriptrunner::load(const std::string& file) {
  std::ifstream fi(file);

  if(!fi.is_open()) {
    throw std::runtime_error("Failed to load script file '"+file+"'");
    return false;
  }

  std::stringstream buf;
  buf << fi.rdbuf();

  data = buf.str();

  return true;
}

void cfs::scriptrunner::destroy() {
  if(alive) {
    delete _impl;
    alive = false;
  }
}

typedef std::tuple<std::string,std::string> strpair;

strpair guesspairs = {
  strpair("variable", "var")
};

bool cfs::scriptrunner::interpret() {
  std::string current = "";

  std::string guess   = "";
  
  for(unsigned int i=0; i<data.length(); ++i) {
    switch(data[i]) {
    case '\n':
    case '\t':
    case ' ' :
      
      break;
      
    default:
      current += data[i];
      break;
    }
  }
}

void cfs::scriptrunner::run() {

}
