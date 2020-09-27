#include "GrassBlade.hh"

GrassBlade::GrassBlade()
{
}

void GrassBlade::initGrass (SharedUniformMatrix4f mpUniformModelViewProjectionMatrix, SharedTexture sizeDepth, SharedTexture sizeColour)
{

renderObj = RenderObjectControl(
        VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
    ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
        uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
        uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("grass.png"))).create()).
        create(),
    FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
    create();
}

void GrassBlade::paint()
{

    renderObj->render();
}
