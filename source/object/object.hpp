#ifndef H_OBJECT_HPP
#define H_OBJECT_HPP

#include "../units/units.hpp"

#include <string>
#include <vector>

class object;

class script {
protected:
  friend class object;
  object* parent;
  
public:
  virtual const std::string& name() const { }
  
  script();

  virtual void onStart (           ) = 0;
  virtual void onUpdate(float delta) { }
  virtual void onDraw  (float delta) { }
  virtual void onExit  (           ) { }
};

class application;

class object {
protected:
  friend class application;
  
  float3d __pos;
  float3d __rot;
  float3d __siz;

  object* __parent;

  std::vector<object>  __children;
  std::vector<script*> __scripts;
public:
  std::string name;
  
  const float3d& position() const;
  const float3d& rotation() const;
  const float3d& scale   () const;

  object&  parent        ();
  
  object();
  object(const std::string&);

  void translate(const float3d&);
  void rotate   (const float3d&);
  void scale    (const float3d&);

  void setParent(object*);

  void    addChild(const object&);
  bool    delChild(const std::string&);
  object& getChild(const std::string&);

  void    __addScript(script*);

  template<typename T>
  void    addScript(const T& scr) {
    T* dat = new T(scr);

    __addScript(dat);
  }
  bool    delScript(const std::string&);
  script* getScript(const std::string&);

  std::vector<object>&  children();
  std::vector<script*>& scripts ();
};

#endif
