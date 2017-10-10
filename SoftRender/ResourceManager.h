#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <vector>
#include <memory>
#include <string>

#include "IFile.h"

class ResourceManager
{
public:
    static ResourceManager * Instance();

    void AddPath(const std::string &path);

    std::string GetFilePath(const std::string &filename);

    std::shared_ptr<IFile> OpenFile(const std::string &filename);

    bool IsExist(const std::string &filename);

private:
    ResourceManager() {};
    ~ResourceManager() {};

protected:
    bool hasFile(const std::string &path);

protected:
    std::vector<std::string> m_resourcePaths;  //保存文件夹路径

    static ResourceManager *m_resourceMgr;
};

#endif
