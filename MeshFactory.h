//
// Created by Emanuel Schimidt on 14/11/16.
//

#ifndef ESTUDOSOPENGL_MESHFACTORY_H
#define ESTUDOSOPENGL_MESHFACTORY_H

#include "Mesh.h"

class MeshFactory {

public:
    static Mesh* createCube();
    static Mesh* createPlane(int depth, int width);
};


#endif //ESTUDOSOPENGL_MESHFACTORY_H
