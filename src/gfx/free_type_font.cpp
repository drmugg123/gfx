#include "gfx/free_type_font.hpp"

gfx::FreeTypeFont::FreeTypeFont() {
}
gfx::FreeTypeFont::~FreeTypeFont() {
}

bool gfx::FreeTypeFont::loadFromFile(const std::string& path, unsigned int size) {
    this->path = path;

    FT_Library fl;
    FT_GlyphSlot fg;
    FT_Face ff;

    if(FT_Init_FreeType(&fl)) {
        std::string errMsg("failed to initialize freetype when loading font ");
        errMsg += path;
        errMsg += "\n";
        throw std::runtime_error(errMsg);
        return false;
    }

    if(FT_New_Face(fl, path.c_str(), 0, &ff) == FT_Err_Unknown_File_Format) {
        std::string errMsg("failed to open font ");
        errMsg += path;
        errMsg += ", unsupported format\n";
        throw std::runtime_error(errMsg);
        return false;
    } else {
        std::string errMsg("failed to open font ");
        errMsg += path;
        errMsg += ", damaged, insufficient priviliges, or missing file\n";
        throw std::runtime_error(errMsg);
        return false;
    }

    FT_Set_Pixel_Sizes(ff, 0, size);

    fg = ff->glyph;

    glm::vec2 glyph_res;

    //cache the most common characters
    for(int i = 32; i < 127; i++) {
        if(FT_Load_Char(ff, i, FT_LOAD_RENDER)) {
            printf("failed to load character %c from font %s\n", (char)i, path.c_str());
            continue;
        }

        glyph_res.x += fg->bitmap.width;
        glyph_res.y = std::max(glyph_res.y, (float)fg->bitmap.rows);

        this->res.x = glyph_res.x;
        this->res.y = glyph_res.y;

        this->glyphs.push_back(gfx::Glyph(
            glm::vec2(fg->bitmap.width, fg->bitmap.rows), //resolution
            glm::vec2(fg->advance.x >> 6, fg->advance.y >> 6), //advance
            fg->bitmap_left,
            fg->bitmap_top,
            (float)glyph_res.x / glyph_res.y
        ));
    }

    FT_Done_Face(ff);
    FT_Done_FreeType(fl);

    return true;
}