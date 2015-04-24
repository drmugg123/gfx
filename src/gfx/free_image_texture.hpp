#ifndef FREE_IMAGE_TEXTURE_HPP
#define FREE_IMAGE_TEXTURE_HPP

#include "gfx/texture.hpp"

#include <FreeImage.h>

namespace gfx {
    class FreeImageTexture : public Texture {
        public:
            FreeImageTexture();
            ~FreeImageTexture();

            FREE_IMAGE_FORMAT getFreeImageFormatFromPath(const std::string&);
            bool load(const std::string&);
    };
}

#endif //FREE_IMAGE_TEXTURE_HPP