//
// Created by manan on 28/07/2021.
//

#ifndef CRESCENTENGINE_SHADERPROGRAM_H
#define CRESCENTENGINE_SHADERPROGRAM_H

#include <gl/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include "../../engine/core/Log/Log.h"

namespace crescent {

    class ShaderProgram {
    private:
        GLuint                                                  m_ProgramId;
        GLuint                                                  m_VertexShaderId;
        GLuint                                                  m_FragmentShaderId;
        std::map<std::string, int>                              m_UniformsMap;
    public:
        ShaderProgram() = default;
        ShaderProgram(const char *vertexPath, const char *fragmentPath);
        virtual ~ShaderProgram();
    public:
        void                                                    Use();
        void                                                    Bind();
        void                                                    Unbind();
        void                                                    CleanUp();
        void                                                    CreateUniform(const std::string& name);
        void                                                    SetUniformMat4(const std::string& name, const glm::mat4& mat) ;
        void                                                    SetUniformInt(const std::string& name, uint32_t unit);
        void                                                    SetUniformVec3(const std::string& name, const glm::vec3& vec);
        void                                                    SetUniformFloat(const std::string& name, float value);
    public:
        std::string                                             LoadShaderFromFile(const char* shaderPath) const;
        std::string                                             GetShaderName(const char* shaderPath) const;
        void                                                    CheckCompilationErrors(GLuint shader, const std::string& type, const std::string& shaderName);
    };

}
#endif //CRESCENTENGINE_SHADERPROGRAM_H
