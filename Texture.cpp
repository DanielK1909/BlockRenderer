#include "Texture.h"

#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "Log.h"

Texture::Texture() {
    loaded_ = false;
}

bool Texture::loadPNG(const char* path) {
    stbi_set_flip_vertically_on_load(true);

    // Load texture from stb
    auto data = stbi_load(path, &width_, &height_, &channels_, 0);

    if (!data) {
        Log::error("Could not load texture.");
        return false;
    }

    // Generate the texture in OpenGL and save ID
    glGenTextures(1, &gl_id_);
    glBindTexture(GL_TEXTURE_2D, gl_id_);

    // Add data to OpenGL texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return true;
}

void Texture::apply() {
    if (loaded_) {
        glBindTexture(GL_TEXTURE_2D, gl_id_);
    }
    else {
        //glBindTexture(GL_TEXTURE_2D, 0);
    }
}
