//
// Created by manan on 05/08/2021.
//

#ifndef CRESCENTENGINE_RESOURCE_H
#define CRESCENTENGINE_RESOURCE_H

#include <string>
#include <memory>

namespace crescent
{

    class Resource {
    protected:
        std::string                                    m_FilePath;
    public:
        Resource() = default;

        Resource(const std::string &filePath);

        virtual ~Resource() {};
        virtual void                                    Release();

    };

    typedef std::shared_ptr<Resource>                   ResourcePtr;

}

#endif //CRESCENTENGINE_RESOURCE_H
