#include "default_scripts.hpp"
#include "../render/buffer.hpp"
#include "../application/application.hpp"

#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

spriterenderer::spriterenderer(const shaderprogram& prg)
  : program{prg} {
  
}

typedef unsigned short ushort;

uint __num_of_sprite_renderers = 0;

buffer __spr_buff_indices;
buffer __spr_buff_vertices;

glm::mat4 _pvm;

void spriterenderer::onStart() {
  if(__num_of_sprite_renderers == 0) {
    std::cout<<"[SpriteRenderer] Generating sprite buffers\n";
    __spr_buff_vertices = buffer({
	  0.f, 0.f, 0.f,
	  1.f, 0.f, 0.f,
	  1.f, 1.f, 0.f,
	  0.f, 1.f, 0.f}, BUFFER_VERTEX, BUFFER_STATIC);

    __spr_buff_indices  = buffer({
	  ushort(0), ushort(1), ushort(2),
	  ushort(2), ushort(3), ushort(0)}, BUFFER_ELEMENT, BUFFER_STATIC);
  }

  _matid = glGetUniformLocation(program.glid(), "PVM");
  
  __num_of_sprite_renderers++;
}

void spriterenderer::onUpdate(float delta) {

}

void spriterenderer::onDraw(float delta) {
  glEnableVertexAttribArray(0);

  _pvm = parent->app()->getOrtho();

  _pvm *= glm::translate(glm::mat4(1.f),
			 glm::vec3(parent->position.x,
				   parent->position.y,
				   parent->position.z));

  _pvm *= glm::scale(glm::mat4(1.f),
		     glm::vec3(parent->scale.x,
			       parent->scale.y,
			       parent->scale.z));

  glBindBuffer(GL_ARRAY_BUFFER, __spr_buff_vertices);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void*)0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, __spr_buff_indices);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);

  glUniformMatrix4fv(_matid, 1, false, &_pvm[0][0]);

  glDisableVertexAttribArray(0);
}

void spriterenderer::onExit() {
  __num_of_sprite_renderers--;

  if(__num_of_sprite_renderers == 0) {
    std::cout<<"[SpriteRenderer] No current renderers exist, destroying buffers\n";
    
    __spr_buff_indices.destroy ();
    __spr_buff_vertices.destroy();
  }
}
