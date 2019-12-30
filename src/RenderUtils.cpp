#include "RenderUtils.hpp"

using namespace SpaceThing;

SMeshBuffer* SpaceThing::copy(IMeshBuffer* buffer) {
    SMeshBuffer* ret = new SMeshBuffer();

    ret->Vertices.set_used(buffer->getVertexCount());

    if (buffer->getVertexType() == EVT_STANDARD)
        for (int i = 0; i < buffer->getVertexCount(); i++)
            ret->Vertices[i] = static_cast<S3DVertex*>(buffer->getVertices())[i];

    array<u16> indices;
    indices.set_used(buffer->getIndexCount());

    if (buffer->getIndexType() == EIT_16BIT)
        for (int i = 0; i < buffer->getIndexCount(); i++)
            indices[i] = buffer->getIndices()[i];

    ret->Indices = indices;

    ret->Material = buffer->getMaterial();

    return ret;
}

ITexture* SpaceThing::renderTo(ITexture* texture, RenderFunction fun) {
    s32* pixels = static_cast<s32*>(texture->lock());
    fun(pixels);
    texture->unlock();
    return texture;
}

ITexture* SpaceThing::fill(SColor color) {
    return renderTo(1, 1, [&color](s32* pixels) {pixels[0] = color.color;});
}

SMesh* SpaceThing::box(vector3df size,
                       SColor xp,
                       SColor xn,
                       SColor yp,
                       SColor yn,
                       SColor zp,
                       SColor zn) {
    SMesh* mesh = new SMesh();

    SColor colors[6] {xp, xn, yp, yn, zp, zn};

    static vector3df vertices[6][4]{
        { {0, 1, 0}, {1, 1, 0}, {1, 0, 0}, {0, 0, 0} },
        { {0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1} },
        { {0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {0, 0, 1} },
        { {0, 1, 1}, {1, 1, 1}, {1, 1, 0}, {0, 1, 0} },
        { {0, 0, 0}, {0, 0, 1}, {0, 1, 1}, {0, 1, 0} },
        { {1, 1, 0}, {1, 1, 1}, {1, 0, 1}, {1, 0, 0} }
    };

    static vector3df normals[6][4]{
        { {-1,  1, -1}, { 1,  1, -1}, { 1, -1, -1}, {-1, -1, -1} },
        { {-1, -1,  1}, { 1, -1,  1}, { 1,  1,  1}, {-1,  1,  1} },
        { {-1, -1, -1}, { 1, -1, -1}, { 1, -1,  1}, {-1, -1,  1} },
        { { 1, -1, -1}, { 1,  1,  1}, { 1,  1, -1}, {-1,  1, -1} },
        { {-1, -1, -1}, {-1, -1,  1}, {-1,  1,  1}, {-1,  1, -1} },
        { { 1,  1, -1}, { 1,  1,  1}, { 1, -1,  1}, { 1, -1, -1} }
    };

    static vector2d<f32> tuvs[6][4]{
        { {0, 0}, {1, 0}, {1, 1}, {0, 1} },
        { {0, 0}, {1, 0}, {1, 1}, {0, 1} },
        { {0, 0}, {1, 0}, {1, 1}, {0, 1} },
        { {0, 0}, {1, 0}, {1, 1}, {0, 1} },
        { {0, 0}, {1, 0}, {1, 1}, {0, 1} },
        { {0, 0}, {1, 0}, {1, 1}, {0, 1} }
    };

    static array<u16> indices;
    static u16 ind[6]{0,1,2, 0,2,3};

    indices.set_used(6);
    for (int i = 0; i < 6; i++)
        indices[i] = ind[i];

    for (int i = 0; i < 6; i++) {
        SMeshBuffer* buf = new SMeshBuffer();

        buf->Indices = indices;

        buf->Material.MaterialType = EMT_SOLID;

        buf->BoundingBox.reset(0, 0, 0);

        buf->Vertices.set_used(4);
        for (int j = 0; j < 4; j++) {
            vertices[i][j] *= size;

            buf->Vertices[j] = S3DVertex(vertices[i][j],
                                         normals[i][j],
                                         colors[i],
                                         tuvs[i][j]);

            buf->BoundingBox.addInternalPoint(vertices[i][j]);
        }

        buf->setHardwareMappingHint(EHM_DYNAMIC);

        mesh->addMeshBuffer(buf);
    }

    mesh->recalculateBoundingBox();

    return mesh;
}
