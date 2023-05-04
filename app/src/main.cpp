#include <vector>
#include "imgui.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <rdr/renderer.h>
#include <scn/scene.h>

void printPPM(float* colorBuffer, int width, int height)
{
    // TODO: print ppm format
}

int main(int argc, char* argv[])
{
    unsigned int width  = 8;
    unsigned int height = 12;

    float* colorBuffer = new float[width * height * 4]();
    float* depthBuffer = new float[width * height]();

    rdrImpl* renderer = rdrInit(colorBuffer, depthBuffer, width, height);
    scnImpl* scene = scnCreate();


    scnUpdate(scene, 1.f / 60.f, renderer);


    //printPPM(colorBuffer, width, height);
    

    scnDestroy(scene);
    rdrShutdown(renderer);

    /*glfwDestroyWindow(window);
    glfwTerminate();*/

    delete[] depthBuffer;
    delete[] colorBuffer;

    return 0;
}
