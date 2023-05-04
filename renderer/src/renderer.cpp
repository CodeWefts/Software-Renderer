
#include <cassert>
#include <cmath>

#include "renderer_impl.hpp"

rdrImpl* rdrInit(float* colorBuffer32Bits, float* depthBuffer, int width, int height)
{
    // TODO: Store buffers and display size
    // TODO: Init renderer
    rdrImpl* renderer = new rdrImpl();

    return renderer;
}

void rdrShutdown(rdrImpl* renderer)
{
    delete renderer;
}

void rdrSetProjection(rdrImpl* renderer, float* projectionMatrix)
{
    assert(renderer != nullptr);
    // TODO(later): Store
}

void rdrSetView(rdrImpl* renderer, float* viewMatrix)
{
    assert(renderer != nullptr);
    // TODO(later): Store
}

void rdrSetModel(rdrImpl* renderer, float* modelMatrix)
{
    assert(renderer != nullptr);
    // TODO(later): Store
}

void rdrSetViewport(rdrImpl* renderer, int x, int y, int width, int height)
{
    assert(renderer != nullptr);
    // TODO(later): Store
}

void rdrSetTexture(rdrImpl* renderer, float* colors32Bits, int width, int height)
{
    assert(renderer != nullptr);
    // TODO(later): Store
}

static void drawPixel(float* colors, int width, int height, int x, int y)
{
    // TODO: Draw a white pixel in the color buffer at the x, y coordinates
}

static void drawLine(float* colors, int width, int height, int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;) {
        drawPixel(colors, width, height, x0, y0);
        if (x0 == x1 && y0 == y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

void rdrDrawTriangles(rdrImpl* renderer, rdrVertex* vertices, int count)
{
    assert(renderer != nullptr);

    // For each triangles
    // TODO: Convert vertex local coords to screen coords
    // TODO: Draw triangle with lines (using drawLine)
    // Transform vertex list to triangle into colorBuffer
}