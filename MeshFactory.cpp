//
// Created by Emanuel Schimidt on 14/11/16.
//

#include <iostream>
#include "MeshFactory.h"
#include "MeshBuilder.h"

Mesh *MeshFactory::createCube() {
    return (new MeshBuilder())
            ->addVector3fAttribute("aPosition",
                                   {-0.5f, 0.5f, 0.5f, // 0. top, front, left
                                    -0.5f, -0.5f, 0.5f, // 1. bottom, front, left
                                    0.5f, -0.5f, 0.5f, // 2. bottom, front, right
                                    0.5f, 0.5f, 0.5f, // 3. top, front, right

                                    0.5f, 0.5f, -0.5f, // 4. top, back, right
                                    0.5f, -0.5f, -0.5f, // 5. bottom, back, right

                                    -0.5f, 0.5f, -0.5f, // 6. top, back, left
                                    -0.5f, -0.5f, -0.5f // 7. bottom, back, left)
                                   })
            ->addVector3fAttribute("aColor",
                                   {0.0f, 0.0f, 1.0f,
                                    0.0f, 1.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f,
                                    0.0f, 1.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f,
                                    0.0f, 1.0f, 0.0f}
            )
            ->setIndexBuffer(
                    {// front
                            0, 1, 2,
                            3, 0, 2,
                            // right
                            3, 2, 5,
                            4, 3, 5,
                            // back
                            4, 5, 6,
                            6, 5, 7,
                            // left
                            6, 7, 0,
                            0, 7, 1,
                            // top
                            6, 0, 3,
                            4, 6, 3,
                            // bottom
                            1, 7, 5,
                            2, 1, 5}
            )
            ->loadShader({"/Users/emanuel/ClionProjects/estudosOpenGL/shader/shader"})
            ->create();
}

Mesh* MeshFactory::createPlane(int depth, int width) {
    std::vector<int> indexBuffer;
    indexBuffer.reserve(depth*width);

    std::vector<glm::vec3> vertex;
    vertex.reserve((width - 1) * (depth - 1) * 6); // it is needed 6 indexes to create each small square. we have (width - 1) * (depth - 1) squares in grid
    float scalar = 0.1f;
    float top_left_x = -1 * scalar * (width % 2 == 0 ? (width / 2) - 0.5f : (width / 2));
    float top_left_z = -1 * scalar * (depth % 2 == 0 ? (depth / 2) - 0.5f : (depth / 2));

    // Build vertex array
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < width; j++) {
            vertex.push_back(glm::vec3(top_left_x + (j* scalar), 0.0f, top_left_z + (i* scalar)));
        }
    }

    // Build index buffer based on parameters received
    for (int i = 0; i < depth - 1; i++) {
        for (int j = 0; j < width - 1; j++) {
            int currIndex = (i * width) + j;
            int i1 = currIndex;
            int i2 = currIndex + width;
            int i3 = currIndex + width + 1;
            int i4 = currIndex + 1;

            indexBuffer.push_back(i1);
            indexBuffer.push_back(i2);
            indexBuffer.push_back(i3);

            indexBuffer.push_back(i4);
            indexBuffer.push_back(i1);
            indexBuffer.push_back(i3);
        }
    }

    return (new MeshBuilder())
            ->addVector3fAttribute("aPosition", vertex.size() * 3, &vertex[0].x)
            ->setIndexBuffer(indexBuffer)
            ->loadShader({"/Users/emanuel/ClionProjects/estudosOpenGL/shader/shader"})
            ->create();
}