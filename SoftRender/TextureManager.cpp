#include "TextureManager.h"

namespace SoftRenderer {

    TextureManager::~TextureManager()
    {

    }

    SoftRenderer::TextureManager * TextureManager::Instance()
    {
        if (NULL = s_instance)
        {
            s_instance = new TextureManager;
        }

        return s_instance;
    }

    TextureManager::TextureManager()
    {

    }

    SoftRenderer::TextureManager * TextureManager::s_instance = NULL;

}