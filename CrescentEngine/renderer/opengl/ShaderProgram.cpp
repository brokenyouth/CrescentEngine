//
// Created by manan on 28/07/2021.
//

#include "ShaderProgram.h"

namespace crescent
{

    ShaderProgram::ShaderProgram(const char *vertexPath, const char *fragmentPath) {
        m_UniformsMap = std::map<std::string, int>();
        m_ProgramId = 0;
        /* Load shaders from disk */
        std::string vertShaderCode = LoadShaderFromFile(vertexPath);
        std::string fragShaderCode = LoadShaderFromFile(fragmentPath);

        /* Compile shaders */
        const char* vertShaderString = vertShaderCode.c_str();
        const char* fragShaderString = fragShaderCode.c_str();

        int success;
        char log[512];
        /* vertex shader */
        m_VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(m_VertexShaderId , 1 , &vertShaderString , nullptr);
        glCompileShader(m_VertexShaderId);
        CheckCompilationErrors(m_VertexShaderId , "VERTEX" , GetShaderName(vertexPath));
        /* fragment shader */
        m_FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(m_FragmentShaderId , 1 , &fragShaderString , nullptr);
        glCompileShader(m_FragmentShaderId);
        CheckCompilationErrors(m_FragmentShaderId , "FRAGMENT" , GetShaderName(fragmentPath));
        /* program */
        m_ProgramId = glCreateProgram();
        glAttachShader(m_ProgramId , m_VertexShaderId);
        glAttachShader(m_ProgramId , m_FragmentShaderId);
        glLinkProgram(m_ProgramId);
        CheckCompilationErrors(m_ProgramId , "PROGRAM" , "");

        /* clean up */
        CleanUp();

        if(m_ProgramId != -1)
            CRESCENT_CORE_INFO("[SHADER] {} and {} loaded." , GetShaderName(vertexPath) , GetShaderName(fragmentPath));
    }

    void ShaderProgram::Use() {
        Bind();
    }

    void ShaderProgram::Bind() {
        glUseProgram(m_ProgramId);
    }

    void ShaderProgram::Unbind() {
        glUseProgram(0);
    }

    void ShaderProgram::CleanUp() {
        Unbind();
        glDeleteShader(m_VertexShaderId);
        glDeleteShader(m_FragmentShaderId);
    }

    std::string ShaderProgram::LoadShaderFromFile(const char *shaderPath) const {
        std::string shaderCode;
        std::ifstream shaderFile;
        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            shaderFile.open(shaderPath);
            std::stringstream shaderStream;
            shaderStream << shaderFile.rdbuf();
            shaderFile.close();
            shaderCode = shaderStream.str(); // stream to string
        }
        catch (const std::ifstream::failure& e)
        {
            CRESCENT_CORE_ERROR("[SHADER] {} - an error occured while reading this file." , GetShaderName(shaderPath));
        }
        return shaderCode;
    }

    std::string ShaderProgram::GetShaderName(const char *shaderPath) const {
        std::string pathstr = std::string(shaderPath);
        const size_t last_slash_idx = pathstr.find_last_of("/");
        if (std::string::npos != last_slash_idx)
        {
            pathstr.erase(0 , last_slash_idx + 1);
        }
        return pathstr;
    }

    void ShaderProgram::CheckCompilationErrors(GLuint shader, const std::string& type, const std::string& shaderName) {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader , GL_COMPILE_STATUS , &success);
            if (!success)
            {
                glGetShaderInfoLog(shader , 1024 , nullptr , infoLog);
                CRESCENT_CORE_ERROR("[SHADER] {} - compilation error: {}" , shaderName , type);
                CRESCENT_CORE_WARN("[SHADER] {} - info: {}" , shaderName , infoLog);
            }
        }
        else
        {
            glGetProgramiv(shader , GL_LINK_STATUS , &success);
            if (!success)
            {
                glGetProgramInfoLog(shader , 1024 , nullptr , infoLog);
                CRESCENT_CORE_ERROR("[PROGRAM] LINKING: {}" , type);
                CRESCENT_CORE_WARN("[PROGRAM] : {}" , infoLog);
            }
        }
    }


    void ShaderProgram::CreateUniform(const std::string &name) {
            int uniformLoc = glGetUniformLocation(m_ProgramId, name.c_str());
            if (uniformLoc < 0)
                CRESCENT_CORE_ERROR("Uniform {} could not be found in program : {}.", name, m_ProgramId);

            auto temp = m_UniformsMap.find(name.c_str());
            if (temp == m_UniformsMap.end()) {  // if not found
                m_UniformsMap.insert(std::pair<std::string, int>(name, uniformLoc));
                return;
            }
            return;

    }

    void ShaderProgram::SetUniformMat4(const std::string &name, const glm::mat4 &mat)  {
        int location = -1;
        auto temp = m_UniformsMap.find(name.c_str());
        if (temp != m_UniformsMap.end())
            location = temp->second;
        if (location >= 0)
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));

    }

    void ShaderProgram::SetUniformInt(const std::string &name, uint32_t unit)  {
        int location = -1;
        auto temp = m_UniformsMap.find(name.c_str());
        if (temp != m_UniformsMap.end())
            location = temp->second;
        if (location >= 0)
            glUniform1i(location, unit);
    }

    void ShaderProgram::SetUniformVec3(const std::string &name, const glm::vec3& vec) {
        int location = -1;
        auto temp = m_UniformsMap.find(name.c_str());
        if (temp != m_UniformsMap.end())
            location = temp->second;
        if (location >= 0)
            glUniform3fv(location, 1, &vec[0]);
    }

    void ShaderProgram::SetUniformFloat(const std::string &name, float value) {
        int location = -1;
        auto temp = m_UniformsMap.find(name.c_str());
        if (temp != m_UniformsMap.end())
            location = temp->second;
        if (location >= 0)
            glUniform1f(location, value);
    }

    ShaderProgram::~ShaderProgram() {

    }


}