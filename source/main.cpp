#include "application/application.hpp"
#include "comfyscript/comfyscript.hpp"
#include "object/default_scripts.hpp"
#include "object/object.hpp"
#include "render/render.hpp"
#include "error/error.hpp"
#include "units/units.hpp"
#include "log/log.hpp"

#include <iostream>
#include <math.h>

class testscript : public script {
public:
  std::string _name = "testscript";

  const std::string& name() const { return _name; }
  
  void onStart() {
    std::cout<<"Script started!\n";
  }
};

class testapp : public application {
public:
  vao    vobject;
  
  shader fshad;
  shader vshad;

  shaderprogram prog;

  cfs::scriptrunner tscript;
  
  void onStart() {
    object to("obj1");

    tscript.load("assets/scripts/thing.cfs");

    tscript.interpret();
    tscript.run();
    
    vobject.create();
    glBindVertexArray(vobject);

    fshad = shader("assets/shaders/basic.frag", SHADER_FRAGMENT);
    vshad = shader("assets/shaders/basic.vert", SHADER_VERTEX  );

    prog = shaderprogram{fshad, vshad};

    to.scale = float3d(100, 100, 1);

    world.addChild(to);
    world.getChild("obj1").addScript(spriterenderer(prog));

    to.name = "testobject2";
    
    world.addChild(to);
    world.getChild("testobject2").addScript(spriterenderer(prog));
    
    glUseProgram(prog);

    glEnableVertexAttribArray(0);
  }

  unsigned int frame = 0;

  void onUpdate(float delta) {
    event& e = win.pollEvents();

    if(e.status && e.type == EVENT_KEYDOWN) {
      std::cout<<"[Key Pressed] '"<<e.key<<"'\n";
    }

    object& testobj = world.getChild("obj1");

    testobj.position.x = (sin(frame / 10.f) * 100) + (win.getSize().x / 2) - 50;
    testobj.position.y = (cos(frame / 10.f) * 100) + (win.getSize().y / 2) - 50;

    frame++;
  }

  void onDraw(float delta) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void onExit(float delta) {

  }
};

int main(int argc,char *argv[]) {
  try {
    testapp t;

    t.run(uint2d(0, 0), uint2d(1280, 720), "Test Application (Spark)");
    
  } catch(std::exception &e) {
    errorwindow ewin("Spark Error", std::string("[Error] : ") + e.what());
  }

  return 0;
}
