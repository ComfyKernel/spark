#include "error.hpp"

#include <Xm/Xm.h>
#include <Xm/Text.h>

#include <iostream>

#define UNUSED(thing) do { (void)(thing); } while (0)

errorwindow::errorwindow() { }
errorwindow::errorwindow(std::string name, std::string description) {
  show(name, description);
}

bool errorwindow::show(std::string name, std::string description) {
  UNUSED(name);
  
  _pid = fork();

  if(_pid > 0) return true;
  
  Widget       _wid_top, _wid_txt;
  XtAppContext _ctx_app;
  Arg          args[2];
  
  int argc=0;
  char *argv[10];
  
  _wid_top = XtVaAppInitialize(&_ctx_app, "top", NULL, 0,
			       &argc, argv, NULL, NULL);

  XtSetArg(args[0], XmNvalue, description.c_str());
  
  _wid_txt = XmCreateText(_wid_top, "text", args, 1);

  XtManageChild(_wid_txt);
  XtRealizeWidget(_wid_top);
  XtAppMainLoop(_ctx_app);
  
  return true;
}
