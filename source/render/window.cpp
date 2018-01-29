#include "window.hpp"
#include "head.hpp"

#include <iostream>
#include <exception>

// // // // // // // // // // // //
//                               //
//                               //
// GLFW key callback translator  //
//                               //
//                               //
// // // // // // // // // // // //

static bool _has_init_glfw=false;

bool keyCallSet=false;

char currKey='\0';
const char* currSpecialKey="none";
bool keyStatus=false;
bool keyIsSet=false;
bool specialKey=false;

void _keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {
  UNUSED(scancode);
  UNUSED(mods    );
  UNUSED(window  );
  
  keyIsSet=true;
  
  switch(key) { // Very ugly not-so-funny switch block for GLFW keys
  case GLFW_KEY_Q: currKey='q'; specialKey=false; break; // All alpha keys
  case GLFW_KEY_W: currKey='w'; specialKey=false; break;
  case GLFW_KEY_E: currKey='e'; specialKey=false; break;
  case GLFW_KEY_R: currKey='r'; specialKey=false; break;
  case GLFW_KEY_T: currKey='t'; specialKey=false; break;
  case GLFW_KEY_Y: currKey='y'; specialKey=false; break;
  case GLFW_KEY_U: currKey='u'; specialKey=false; break;
  case GLFW_KEY_I: currKey='i'; specialKey=false; break;
  case GLFW_KEY_O: currKey='o'; specialKey=false; break;
  case GLFW_KEY_P: currKey='p'; specialKey=false; break;
  case GLFW_KEY_A: currKey='a'; specialKey=false; break;
  case GLFW_KEY_S: currKey='s'; specialKey=false; break;
  case GLFW_KEY_D: currKey='d'; specialKey=false; break;
  case GLFW_KEY_F: currKey='f'; specialKey=false; break;
  case GLFW_KEY_G: currKey='g'; specialKey=false; break;
  case GLFW_KEY_H: currKey='h'; specialKey=false; break;
  case GLFW_KEY_J: currKey='j'; specialKey=false; break;
  case GLFW_KEY_K: currKey='k'; specialKey=false; break;
  case GLFW_KEY_L: currKey='l'; specialKey=false; break;
  case GLFW_KEY_Z: currKey='z'; specialKey=false; break;
  case GLFW_KEY_X: currKey='x'; specialKey=false; break;
  case GLFW_KEY_C: currKey='c'; specialKey=false; break;
  case GLFW_KEY_V: currKey='v'; specialKey=false; break;
  case GLFW_KEY_B: currKey='b'; specialKey=false; break;
  case GLFW_KEY_N: currKey='n'; specialKey=false; break;
  case GLFW_KEY_M: currKey='m'; specialKey=false; break;

  case GLFW_KEY_0: currKey='0'; specialKey=false; break;
  case GLFW_KEY_1: currKey='1'; specialKey=false; break;
  case GLFW_KEY_2: currKey='2'; specialKey=false; break;
  case GLFW_KEY_3: currKey='3'; specialKey=false; break;
  case GLFW_KEY_4: currKey='4'; specialKey=false; break;
  case GLFW_KEY_5: currKey='5'; specialKey=false; break;
  case GLFW_KEY_6: currKey='6'; specialKey=false; break;
  case GLFW_KEY_7: currKey='7'; specialKey=false; break;
  case GLFW_KEY_8: currKey='8'; specialKey=false; break;
  case GLFW_KEY_9: currKey='9'; specialKey=false; break;

  case GLFW_KEY_SPACE:        currKey=' ' ; specialKey=false; break;
  case GLFW_KEY_APOSTROPHE:   currKey='\''; specialKey=false; break;
  case GLFW_KEY_COMMA:        currKey=',' ; specialKey=false; break;
  case GLFW_KEY_MINUS:        currKey='-' ; specialKey=false; break;
  case GLFW_KEY_PERIOD:       currKey='.' ; specialKey=false; break;
  case GLFW_KEY_SLASH:        currKey='/' ; specialKey=false; break;
  case GLFW_KEY_SEMICOLON:    currKey=';' ; specialKey=false; break;
  case GLFW_KEY_EQUAL:        currKey='=' ; specialKey=false; break;
  case GLFW_KEY_LEFT_BRACKET: currKey='[' ; specialKey=false; break;
  case GLFW_KEY_BACKSLASH:    currKey='\\'; specialKey=false; break;
  case GLFW_KEY_GRAVE_ACCENT: currKey='`' ; specialKey=false; break;
    
  case GLFW_KEY_ESCAPE:       currSpecialKey="escape"    ; specialKey=true; break;
  case GLFW_KEY_ENTER:        currSpecialKey="return"    ; specialKey=true; break;
  case GLFW_KEY_TAB:          currSpecialKey="tab"       ; specialKey=true; break;
  case GLFW_KEY_BACKSPACE:    currSpecialKey="backspace" ; specialKey=true; break;
  case GLFW_KEY_INSERT:       currSpecialKey="insert"    ; specialKey=true; break;
  case GLFW_KEY_DELETE:       currSpecialKey="delete"    ; specialKey=true; break;
  case GLFW_KEY_RIGHT:        currSpecialKey="right"     ; specialKey=true; break;
  case GLFW_KEY_LEFT:         currSpecialKey="left"      ; specialKey=true; break;
  case GLFW_KEY_DOWN:         currSpecialKey="down"      ; specialKey=true; break;
  case GLFW_KEY_UP:           currSpecialKey="up"        ; specialKey=true; break;
  case GLFW_KEY_PAGE_UP:      currSpecialKey="page_up"   ; specialKey=true; break;
  case GLFW_KEY_PAGE_DOWN:    currSpecialKey="page_down" ; specialKey=true; break;
  case GLFW_KEY_HOME:         currSpecialKey="home"      ; specialKey=true; break;
  case GLFW_KEY_END:          currSpecialKey="end"       ; specialKey=true; break;
  case GLFW_KEY_CAPS_LOCK:    currSpecialKey="l_caps"    ; specialKey=true; break;
  case GLFW_KEY_SCROLL_LOCK:  currSpecialKey="l_scroll"  ; specialKey=true; break;
  case GLFW_KEY_NUM_LOCK:     currSpecialKey="l_num"     ; specialKey=true; break;
  case GLFW_KEY_PRINT_SCREEN: currSpecialKey="print_s"   ; specialKey=true; break;
  case GLFW_KEY_PAUSE:        currSpecialKey="pause"     ; specialKey=true; break;

  case GLFW_KEY_F1: currSpecialKey="f1" ; specialKey=true; break;
  case GLFW_KEY_F2: currSpecialKey="f2" ; specialKey=true; break;
  case GLFW_KEY_F3: currSpecialKey="f3" ; specialKey=true; break;
  case GLFW_KEY_F4: currSpecialKey="f4" ; specialKey=true; break;
  case GLFW_KEY_F5: currSpecialKey="f5" ; specialKey=true; break;
  case GLFW_KEY_F6: currSpecialKey="f6" ; specialKey=true; break;
  case GLFW_KEY_F7: currSpecialKey="f7" ; specialKey=true; break;
  case GLFW_KEY_F8: currSpecialKey="f8" ; specialKey=true; break;
  case GLFW_KEY_F9: currSpecialKey="f9" ; specialKey=true; break;
    
  case GLFW_KEY_F10: currSpecialKey="f10" ; specialKey=true; break;
  case GLFW_KEY_F11: currSpecialKey="f11" ; specialKey=true; break;
  case GLFW_KEY_F12: currSpecialKey="f12" ; specialKey=true; break;

  case GLFW_KEY_KP_0: currSpecialKey="kp0" ; specialKey=true; break;
  case GLFW_KEY_KP_1: currSpecialKey="kp1" ; specialKey=true; break;
  case GLFW_KEY_KP_2: currSpecialKey="kp2" ; specialKey=true; break;
  case GLFW_KEY_KP_3: currSpecialKey="kp3" ; specialKey=true; break;
  case GLFW_KEY_KP_4: currSpecialKey="kp4" ; specialKey=true; break;
  case GLFW_KEY_KP_5: currSpecialKey="kp5" ; specialKey=true; break;
  case GLFW_KEY_KP_6: currSpecialKey="kp6" ; specialKey=true; break;
  case GLFW_KEY_KP_7: currSpecialKey="kp7" ; specialKey=true; break;
  case GLFW_KEY_KP_8: currSpecialKey="kp8" ; specialKey=true; break;
  case GLFW_KEY_KP_9: currSpecialKey="kp9" ; specialKey=true; break;

  case GLFW_KEY_KP_DECIMAL:  currSpecialKey="kp." ; specialKey=true; break;
  case GLFW_KEY_KP_DIVIDE:   currSpecialKey="kp/" ; specialKey=true; break;
  case GLFW_KEY_KP_MULTIPLY: currSpecialKey="kp*" ; specialKey=true; break;
  case GLFW_KEY_KP_SUBTRACT: currSpecialKey="kp-" ; specialKey=true; break;
  case GLFW_KEY_KP_ADD:      currSpecialKey="kp+" ; specialKey=true; break;
  case GLFW_KEY_KP_EQUAL:    currSpecialKey="kp=" ; specialKey=true; break;
    
  case GLFW_KEY_KP_ENTER:    currSpecialKey="kp_return" ; specialKey=true; break;
    
  case GLFW_KEY_LEFT_SHIFT:   currSpecialKey="l_shift"   ; specialKey=true; break;
  case GLFW_KEY_LEFT_CONTROL: currSpecialKey="l_control" ; specialKey=true; break;
  case GLFW_KEY_LEFT_ALT:     currSpecialKey="l_alt"     ; specialKey=true; break;
  case GLFW_KEY_LEFT_SUPER:   currSpecialKey="l_super"   ; specialKey=true; break;

  case GLFW_KEY_RIGHT_SHIFT:   currSpecialKey="r_shift"   ; specialKey=true; break;
  case GLFW_KEY_RIGHT_CONTROL: currSpecialKey="r_control" ; specialKey=true; break;
  case GLFW_KEY_RIGHT_ALT:     currSpecialKey="r_alt"     ; specialKey=true; break;
  case GLFW_KEY_RIGHT_SUPER:   currSpecialKey="r_super"   ; specialKey=true; break;

  case GLFW_KEY_MENU: currSpecialKey="menu" ; specialKey=true; break;

  case GLFW_KEY_UNKNOWN: specialKey=false; break; }

  switch(action) {
  case GLFW_PRESS:
    keyStatus=true;
    break;
  case GLFW_RELEASE:
    keyStatus=false;
    break;
  case GLFW_REPEAT:
    keyStatus=true;
    break;
  default:
    keyStatus=false;
    break;
  }
};

// // // // // // // // // //
//                         //
//                         //
// The actual window stuff //
//                         //
//                         //
// // // // // // // // // //

void glDebugStuff(GLenum src,GLenum type,GLuint id,
		  GLenum severity,GLsizei len,
		  const GLchar* message,const void* param) {
  UNUSED(src); UNUSED(type    );
  UNUSED(id ); UNUSED(severity);
  UNUSED(len); UNUSED(param   );
  
  std::cout<<"[GL Debug] "<<message<<"\n"; }

struct window::_windowIMPL {
public:
  GLFWwindow* win;
  event e;

  const uint2d getPos () {
    int x,y;
    glfwGetWindowPos (win,&x,&y);
    return uint2d(x,y);
  }
  
  const uint2d getSize() {
    int w,h;
    glfwGetWindowSize(win,&w,&h);
    return uint2d(w,h);
  }

  void setPos (const uint2d&  pos) { glfwSetWindowPos (win,pos.x ,pos.y ); }
  void setSize(const uint2d& size) { glfwSetWindowSize(win,size.x,size.y); }

  bool create(const uint2d& pos, const uint2d& size,
	      const std::string& name) {
    if(!_has_init_glfw) {
      std::cout<<"Initializing GLFW\n";
      _has_init_glfw=true;
      if(!glfwInit()) {
	throw std::runtime_error("GLFW Initialization Failed!");
	return false;
      }
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER,1);

    if(size.x == 0 || size.y == 0) {
      throw std::length_error("GLFW Window size not allowed to be 0!");
      return false;
    }
    
    win=glfwCreateWindow(size.x,size.y,name.c_str(),NULL,NULL);

    if(win==NULL) {
      throw std::runtime_error("Could not create a GLFW window!");
      return false;
    }
    
    glfwSetWindowPos(win,pos.x,pos.y);

    glfwMakeContextCurrent(win);

    glewExperimental=GL_TRUE;
    if(glewInit()!=GLEW_OK) {
      throw std::runtime_error("Failed to initialize GLEW!");
      return false;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(glDebugStuff,(void*)0);

    return true;
  }

  void destroy() {
    glfwDestroyWindow(win);
  }

  bool rename(const std::string& name) {
    glfwSetWindowTitle(win,name.c_str());
    return true;
  }

  bool isOpen() {
    return !glfwWindowShouldClose(win);
  }

  event& pollEvents() {
    if(!keyCallSet) {
      keyCallSet=true;

      glfwSetKeyCallback(win,_keyCallback);
    }
    
    glfwPollEvents();

    if(keyIsSet) {
      e.type=EVENT_KEY;

      if(keyStatus) {
	e.type=EVENT_KEYDOWN;
      } else {
	e.type=EVENT_KEYUP;
      }
      
      keyIsSet=false;
      e.key        = currKey;
      e.specialKey = currSpecialKey;
      e.status     = keyStatus;
      e.special    = specialKey;
    }

    return e;
  }

  bool makeCurrent() {
    glfwMakeContextCurrent(win);
    return true;
  }

  void close() {
    glfwSetWindowShouldClose(win,true);
  }

  void swap() {
    glfwSwapBuffers(win);
  }
};

void window::setPosition(const uint2d& pos)  { _impl->setPos (pos ); }
void window::setSize    (const uint2d& size) { _impl->setSize(size); }

const uint2d window::getPosition() { return _impl->getPos (); };
const uint2d window::getSize    () { return _impl->getSize(); };

window::window()
  : _impl{new _windowIMPL()} { }

window::window(const uint2d& pos, const uint2d& size,
	       const std::string& name)
  : _impl{new _windowIMPL()} {
  
  create(pos,size,name);
}

window::window(unsigned int X,unsigned int Y,
	       unsigned int W,unsigned int H,
	       const std::string& name)
  : _impl{new _windowIMPL()} {
  
  create(uint2d(X,Y),uint2d(W,H),name);
}

bool window::create(const uint2d& pos,const uint2d& size,
		    const std::string& name) {
  return _impl->create(pos,size,name);
}

void window::destroy()                       { _impl->destroy();    }
void window::rename(const std::string& name) { _impl->rename(name); }

bool window::isOpen()      { return _impl->isOpen();      }
bool window::makeCurrent() { return _impl->makeCurrent(); }

void window::close() { return _impl->close(); }
void window::swap()  { return _impl->swap();  }

event& window::pollEvents() {
  return _impl->pollEvents();
}
