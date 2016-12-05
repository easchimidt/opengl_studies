//
// Created by Emanuel Schimidt on 14/11/16.
//

#ifndef ESTUDOSOPENGL_MESHFACTORY_H
#define ESTUDOSOPENGL_MESHFACTORY_H

#include "Mesh.h"

class MeshFactory {
public:
    static Mesh* createSquare();
    static Mesh* createCube();
    static Mesh* createPlane(int depth, int width);
    static Mesh* createSphere(float ratio, int hSlices, int vSlices);
    static Mesh* loadTerrain(std::string filename, float scale);
};


#endif //ESTUDOSOPENGL_MESHFACTORY_H
