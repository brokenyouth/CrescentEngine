//
// Created by manan on 05/08/2021.
//

#ifndef CRESCENTENGINE_RESOURCEMANAGER_H
#define CRESCENTENGINE_RESOURCEMANAGER_H

#include <unordered_map>
#include <string>
#include <memory>

#include "Resource.h"

namespace crescent
{

    class ResourceManager {
    protected:
        std::unordered_map<std::string, ResourcePtr>            m_ResourcesMap;
    public:
        ResourceManager();

        virtual ~ResourceManager() = default;
    public:
        ResourcePtr                                             CreateResourceFromFile(const std::string &filePath, const std::string& type);

    protected:
        virtual Resource*                                       LoadResourceFromFile(const std::string& filePath, const std::string& type) = 0;
    public:
        virtual void                                            Release();


    };

}

#endif //CRESCENTENGINE_RESOURCEMANAGER_H
