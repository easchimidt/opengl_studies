//
// Created by Emanuel Schimidt on 14/11/16.
//

#include <iostream>
#include <fstream>
#include <iostream>
#include <math.h>
#include "MeshFactory.h"
#include "MeshBuilder.h"
#include "Utils.h"

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

Mesh* MeshFactory::createSphere(float ratio, int hSlices, int vSlices) {
    std::vector<int> indexBuffer;
    indexBuffer.reserve(hSlices*vSlices);

    std::vector<glm::vec3> vertex;
    vertex.reserve((hSlices - 1) * (vSlices - 1) * 6); // it is needed 6 indexes to create each small square. we have (width - 1) * (depth - 1) squares in grid

    float verticalAngleInterval = M_PI / (float) hSlices;
    float horizontalAngleInterval = 2.0f * M_PI / (float) vSlices;

    vertex.push_back(glm::vec3(0.0f, ratio, 0.0f)); //top vertex

    // Build vertex array. Considering phi as the azimuth and theta as the inclination.
    // phi is between 0-2pi (0-360°), and theta is between 0-pi (0-180°)
    for (int i = 1; i < hSlices; i++) {
        double theta = i * verticalAngleInterval;
        double sinTheta = sin(theta);
        double cosTheta = cos(theta);

        for (int j = 0; j < vSlices; j++) {
            double phi = j * horizontalAngleInterval;
            double sinPhi = sin(phi);
            double cosPhi = cos(phi);

            float x = ratio * (float)(sinTheta * cosPhi);
            float z = ratio * (float)(sinTheta * sinPhi);
            float y = ratio * cosTheta;
            vertex.push_back(glm::vec3(x, y, z));
        }
    }
    vertex.push_back(glm::vec3(0.0f, -ratio, 0.0f)); // insert bottom vertex

    // INDEX BUFFER CONFIGURATION
    // vertex 0 = top index
    // vertex 1 = first index on first horizontal slice
    // vertex (vSlices * (hSlices - 2) + 1) - first index on last horizontal slice
    // vertex (vSlices * (hSlices - 1) + 1) = bottom index

    // create index buffer envolving the top vertex
    for (int i = 1; i < vSlices; i++){
        indexBuffer.push_back(0);
        indexBuffer.push_back(i);
        indexBuffer.push_back(i+1);
    }

    // Last one in horizontal slice closes the circle, so, need the first index, which has id 1
    indexBuffer.push_back(0);
    indexBuffer.push_back(vSlices);
    indexBuffer.push_back(1);

    // create index buffer envolving the bottom vertex
    int bottomIndex = vertex.size() - 1;
    int firstIndexLastSlice = vSlices * (hSlices - 2) + 1;
    for (int i = firstIndexLastSlice; i < bottomIndex; i++){
        indexBuffer.push_back(i);
        indexBuffer.push_back(bottomIndex);
        indexBuffer.push_back(i+1);
    }

    // Closes last slice linking with the first one in last slice
    indexBuffer.push_back(bottomIndex-1);
    indexBuffer.push_back(bottomIndex);
    indexBuffer.push_back(firstIndexLastSlice);

    // Build index buffer based on parameters received
    for (int i = 0; i < hSlices-2; i++) {
        // Why -2 above? One of the -1 is because we need to ignore conections with the bottom vertex,
        // done above. Also, e.g., if there are 6 horizontal slices, then there are 5 horizontal lines, one
        // unity lower the horizontal slice size. This is the another -1.
        for (int j = 1; j < vSlices; j++) {
            int currIndex = (i * vSlices) + j;
            int i1 = currIndex;
            int i2 = currIndex + vSlices;
            int i3 = currIndex + vSlices + 1;
            int i4 = currIndex + 1;

            indexBuffer.push_back(i1);
            indexBuffer.push_back(i2);
            indexBuffer.push_back(i3);

            indexBuffer.push_back(i1);
            indexBuffer.push_back(i3);
            indexBuffer.push_back(i4);
        }

        int currIndex = (i+1) * vSlices;
        int i1 = currIndex;
        int i2 = currIndex + vSlices;
        int i3 = currIndex + 1;
        int i4 = (currIndex - vSlices) + 1;

        indexBuffer.push_back(i1);
        indexBuffer.push_back(i2);
        indexBuffer.push_back(i3);

        indexBuffer.push_back(i1);
        indexBuffer.push_back(i3);
        indexBuffer.push_back(i4);
    }

    return (new MeshBuilder())
            ->addVector3fAttribute("aPosition", vertex.size() * 3, &vertex[0].x)
            ->setIndexBuffer(indexBuffer)
            ->loadShader({"/Users/emanuel/ClionProjects/estudosOpenGL/shader/shader"})
            ->create();
}

Mesh* MeshFactory::loadTerrain(std::string filename, float scale) {
    struct Utils::Image image;

    try {
        Utils::readImageFile(filename, &image);
    }
    catch (const std::string& ex) {
        std::cout << "Exception reading file in MeshFactory::loadTerrain. Error: " << ex << std::endl;
        return NULL;
    }
    int h_width = image.width / 2;
    int h_height = image.height / 2;
    std::vector<int> indexBuffer;
    indexBuffer.reserve(image.width * image.height);

    std::vector<glm::vec3> vertex;
    vertex.reserve(image.width * image.height * 6); // it is needed 6 indexes to create each small square. we have (width - 1) * (depth - 1) squares in grid

    int max_value = 0;
    if (image.rgb != NULL) {
        for (long i = 0; i < image.height * image.width * image.bpp; i+=image.bpp) { // increments image.bpp bytes (bpp means bytes per pixel)
            int pixel_value = (int) image.rgb[i];
            if (max_value < pixel_value)
                max_value = pixel_value;
        }
    }

    std::cout << max_value << std::endl;

    // Build vertex array
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            int value = (int) image.rgb[(x * image.bpp) + (y * image.width)];
            vertex.push_back(glm::vec3(x - h_width, value * scale, y - h_height));
        }
    }

    // Build index buffer based on parameters received
    for (int i = 0; i < image.height - 1; i++) {
        for (int j = 0; j < image.width - 1; j++) {
            int currIndex = (i * image.width) + j;
            int i1 = currIndex;
            int i2 = currIndex + image.width;
            int i3 = currIndex + image.width + 1;
            int i4 = currIndex + 1;

            indexBuffer.push_back(i1);
            indexBuffer.push_back(i2);
            indexBuffer.push_back(i3);

            indexBuffer.push_back(i4);
            indexBuffer.push_back(i1);
            indexBuffer.push_back(i3);
        }
    }

    Utils::freeStb( image.rgb );

    return (new MeshBuilder())
            ->addVector3fAttribute("aPosition", vertex.size() * 3, &vertex[0].x)
            ->setIndexBuffer(indexBuffer)
            ->loadShader({"/Users/emanuel/ClionProjects/estudosOpenGL/shader/shader"})
            ->create();
}

