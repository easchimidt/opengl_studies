//
// Created by Emanuel Schimidt on 23/10/16.
//

#ifndef ESTUDOSOPENGL_UNIFORMTYPE_H
#define ESTUDOSOPENGL_UNIFORMTYPE_H


#include <string>
#include "Shader.h"
#include <glm/glm.hpp>

struct VEC_2 {
    void set(Shader *shader, std::string name, glm::vec2 value) {
        shader->setUniform(name, value);
    }
};

struct MAT_4 {
    void set(Shader *shader, std::string name, glm::mat4 value) {
        shader->setUniform(name, value);
    }
};


class UniformType {
  class UniformTypeConcept {
    public:
      virtual const void set (Shader* shader, std::string name) const = 0;
    };

  template <typename T>
  class UniformTypeModel : public UniformTypeConcept {
    private:
      T m_type;

    public:
      virtual ~UniformTypeModel() {}
      UniformTypeModel(const T *type) : m_type(type) {}

      virtual const void set(Shader* shader, std::string name) const {
        //m_type->set(shader, name, value);
          shader->setUniform(name, m_type);
      }
  };

  UniformTypeConcept *uniformType;

  public:
    template <typename T>
    UniformType (const T& ut) : uniformType( new UniformTypeModel<T>(ut) ) { }
    ~UniformType () { delete uniformType; }

    void set (Shader* shader, std::string name) const {
        uniformType->set(shader, name);
    }

};


#endif //ESTUDOSOPENGL_UNIFORMTYPE_H
