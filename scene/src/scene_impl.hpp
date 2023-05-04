
#include <vector>

#include <rdr/renderer.h>
#include <scn/scene.h>

struct rdrImpl;

struct scnImpl
{
    scnImpl();
    ~scnImpl();
    void update(float deltaTime, rdrImpl* renderer);

    void showImGuiControls();

private:
    std::vector<rdrVertex> vertices;
};