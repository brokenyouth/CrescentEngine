//
// Created by manan on 01/08/2021.
//

#include "Mesh.h"

namespace crescent
{

    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) :
    m_Vertices(vertices), m_Indices(indices)
    {
        m_VertexCount = static_cast<uint32_t>( m_Indices.size() );
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VertexBuffer);
        glGenBuffers(1, &m_IndicesBuffer);
        glGenBuffers(1, &m_TextureBuffer);

        glBindVertexArray(m_VAO);

        // Vertices
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);

        // Indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int),
                     m_Indices.data(), GL_STATIC_DRAW);


        // Attrib pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Position));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Normal));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Color));
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, TexUV));

    }

    void Mesh::SetPosition(const glm::vec3 &pos) {

    }

    void Mesh::Draw(ShaderProgram& shader) {
        shader.Use();

        for (auto i = 0; i < m_Textures.size(); i++)
        {
            std::string number;
            std::string type = m_Textures[i]->GetType();
            shader.Bind(); // probably not needed
            m_Textures[i]->BindTextureUnit(shader, "material" + type, i);
            shader.SetUniformFloat("material.shininess", 16.f);

        }

        glBindVertexArray(m_VAO);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glDrawElements(GL_TRIANGLES, m_VertexCount, GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);

    }

    void Mesh::CleanUp() {
        glBindVertexArray(m_VAO);
        glDeleteBuffers(1, &m_VertexBuffer);
        glDeleteBuffers(1, &m_IndicesBuffer);
        glDeleteBuffers(1, &m_TextureBuffer);
        glBindTexture(GL_TEXTURE_2D, 0);
        glDeleteVertexArrays(1, &m_VAO);
        glBindVertexArray(0);

    }

    void Mesh::AddTexture(const OpenGLTexturePtr & texture ) {

        m_Textures.push_back(texture);
        texture->GenerateTexture();
    }

    Mesh::~Mesh() {

    }

}