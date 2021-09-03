//
// Created by manan on 01/08/2021.
//

#ifndef CRESCENTENGINE_MESH_H
#define CRESCENTENGINE_MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "ShaderProgram.h"
#include "../../engine/core/Resource/Texture/OpenGLTexture.h"
#include "../../engine/core/Vertex.h"
#include "../../engine/core/Log/Log.h"


namespace crescent {

    class Mesh {
    private:
        unsigned int                            m_VAO;
        unsigned int                            m_TextureBuffer;
        unsigned int                            m_IndicesBuffer;
        unsigned int                            m_VertexBuffer;
        uint32_t                                m_VertexCount;

    private:
        std::vector<Vertex>                     m_Vertices;
        std::vector<unsigned int>               m_Indices;
        std::vector<OpenGLTexturePtr>           m_Textures;

    public:
                                                Mesh() = default;
                                                Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
                                                ~Mesh();
    public:
        void                                    AddTexture(const OpenGLTexturePtr & texture );
    public:
        void                                    SetPosition(const glm::vec3 &pos);
        void                                    Draw(ShaderProgram& shader);
        inline GLuint                           GetVAO() const { return m_VAO; }
        void                                    CleanUp();

    };

}

#endif //CRESCENTENGINE_MESH_H
