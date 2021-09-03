//
// Created by manan on 22/08/2021.
//

#ifndef CRESCENTENGINE_SHADERMANAGER_H
#define CRESCENTENGINE_SHADERMANAGER_H

#include <unordered_map>
#include <memory>
#include <string>

#include "../../../renderer/opengl/ShaderProgram.h"
#include "../Log/Log.h"


namespace crescent

{

    class ShaderManager {
    private:
        static ShaderManager *                                                                              m_pInstance;
        std::unordered_map<std::string, ShaderProgram>                                                      m_ShaderMap;
    public:
        ShaderManager() {  };
        void                                                                                                Initialize();
        void                                                                                                AddShader(const std::string& name, ShaderProgram shader);
        void                                                                                                RemoveShader(const std::string& name);
        ShaderProgram*                                                                                      GetShader(const std::string& name) const;
        void                                                                                                Release();
    };
    typedef std::unique_ptr<ShaderProgram> ShaderProgramPtr;


}


#endif //CRESCENTENGINE_SHADERMANAGER_H
