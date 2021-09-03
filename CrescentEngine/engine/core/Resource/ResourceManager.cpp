//
// Created by manan on 05/08/2021.
//

#include "ResourceManager.h"
#include "../Log/Log.h"

namespace crescent
{

    ResourceManager::ResourceManager() {

    }

    ResourcePtr ResourceManager::CreateResourceFromFile(const std::string &filePath, const std::string& type) {

        auto iterator = m_ResourcesMap.find(filePath);

        // if this file has already been loaded / created, return a ptr to it's resource;
        if ( iterator != m_ResourcesMap.end() )
            return iterator->second;

        // now if it doesn't exist yet, create it.
        Resource* pNewResource = LoadResourceFromFile(filePath, type);

        if (pNewResource)
        {
            ResourcePtr pResource ( pNewResource );
            m_ResourcesMap[filePath] = pResource;
            return pResource;
        }

        return nullptr;
    }

    void ResourceManager::Release() {
        auto iterator = m_ResourcesMap.begin();
        while (iterator != m_ResourcesMap.end())
        {
            iterator->second->Release();
            iterator++;
        }
    }
}