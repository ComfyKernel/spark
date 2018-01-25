#ifndef H_ERROR_HPP
#define H_ERROR_HPP

#include <string>
#include <unistd.h>

class errorwindow {
protected:
  pid_t _pid;
  
public:
  errorwindow();
  errorwindow(std::string, std::string);

  bool show(std::string, std::string);
};

#endif
