#ifndef RENDER_UTILS_HPP
#define RENDER_UTILS_HPP

#include <functional>

#include "Game.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

namespace SpaceThing {
    using RenderFunction = std::function<void(s32*)>;

    SMeshBuffer* copy(IMeshBuffer*);

    inline ITexture* texture(u32 w, u32 h) {
        return session.driver->addRenderTargetTexture({w, h});
    }

    ITexture* renderTo(ITexture*, RenderFunction);

    inline ITexture* renderTo(u32 w, u32 h, RenderFunction fun) {
        return renderTo(texture(w, h), fun);
    }

    ITexture* fill(SColor);

    SMesh* box(vector3df, SColor, SColor, SColor, SColor, SColor, SColor);

    inline SMesh* box(vector3df size, SColor fill) {
        return box(size, fill, fill, fill, fill, fill, fill);
    }
}

#endif
