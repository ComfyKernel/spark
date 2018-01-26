#ifndef H_COMFYSCRIPT_HPP
#define H_COMFYSCRIPT_HPP

#include <string>
#include <vector>

namespace cfs {
  enum script_type {
    SCRIPT_TYPE_GLOBAL,
    SCRIPT_TYPE_LOCAL,
    SCRIPT_TYPE_IMMEDIATE
  };
  
  struct type {
  public:
    std::string type;
    std::string name;
  };

  struct variable {
  public:
    type t;
    std::string value;
  };
  
  struct function {
  public:
    std::string name;
    std::vector<type> args;
  };
  
  class scriptrunner {
  protected:
    class _sr_impl_;
    _sr_impl_* _impl;
    bool alive = false;
    
  public:
    std::string data;
    
    scriptrunner();
    scriptrunner(const std::string& file);

    bool load(const std::string& file);
    void destroy();

    bool interpret();
    void run();
  };
};

#endif
