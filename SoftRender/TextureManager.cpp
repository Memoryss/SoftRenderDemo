#include "TextureManager.h"
#include "Texture.h"

namespace SoftRenderer {

    TextureManager::~TextureManager()
    {

    }

    SoftRenderer::TextureManager * TextureManager::Instance()
    {
        if (NULL == s_instance)
        {
            s_instance = new TextureManager;
        }

        return s_instance;
    }

    std::shared_ptr<SoftRenderer::Texture> TextureManager::GetTexture(const std::string &name)
    {
        if (name.empty())
        {
            return NULL;
        }

        auto iter = m_textures.find(name);
        if (iter != m_textures.end()) {
            return iter->second;
        }

        auto texture = std::make_shared<Texture>();
        if (!texture->LoadTexture(name.c_str()))
        {
            texture.reset();
            return NULL;
        }

        m_textures.emplace(name, texture);
        return texture;
    }

    TextureManager::TextureManager()
    {

    }

    SoftRenderer::TextureManager * TextureManager::s_instance = NULL;

}