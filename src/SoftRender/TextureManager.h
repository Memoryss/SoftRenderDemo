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

        std::shared_ptr<Texture> GetTexture(const std::string &name);

    private:
        TextureManager();

    private:
        static TextureManager *s_instance;

        std::map<std::string, std::shared_ptr<Texture>> m_textures;
    };

}

#endif