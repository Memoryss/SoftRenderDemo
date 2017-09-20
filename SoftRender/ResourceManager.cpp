#include "ResourceManager.h"

#include <io.h>

ResourceManager * ResourceManager::m_resourceMgr = NULL;

ResourceManager * ResourceManager::Instance()
{
    if (NULL == m_resourceMgr)
    {
        m_resourceMgr = new ResourceManager;
    }

    return m_resourceMgr;
}

void ResourceManager::AddPath(const std::string &path)
{
    m_resourcePaths.push_back(path);
}

std::shared_ptr<IFile> ResourceManager::OpenFile(const std::string &filename)
{
    std::shared_ptr<IFile> ptr;
    for each (auto dir in m_resourcePaths)
    {
        std::string path = dir + '/' + filename;
        if (hasFile(path))
        {
            ptr = std::make_shared<DiskFile>(path);
            break;
        }
    }

    return ptr;
}

bool ResourceManager::IsExit(const std::string &filename)
{
    for each (auto dir in m_resourcePaths)
    {
        std::string path = dir + '/' + filename;
        if (hasFile(path))
        {
            return true;
        }
    }

    return false;
}

bool ResourceManager::hasFile(const std::string &file)
{
    return _access(file.c_str(), 0) != -1;
}
