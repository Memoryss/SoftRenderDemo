#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <map>
#include <string>
#include <memory>

namespace SoftRenderer {

    class Texture;

    class TextureManager
    {
    public:
        ~TextureManager();

        static TextureManager * Instance();


    private:
        TextureManager();

    private:
        static TextureManager *s_instance;

        std::map<std::string, Texture *> m_textures;
    };

}

#endif