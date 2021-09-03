//
// Created by manan on 16/08/2021.
//

#include "Model.h"

namespace crescent

{

    void Model::LoadModel(const std::string &path) {

        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            CRESCENT_CORE_ERROR("Model loading error: {}", importer.GetErrorString() );
            return;
        }
        else
            CRESCENT_CORE_INFO("Loaded model: {}", path);
        m_ModelFilePath = path.substr(0, path.find_last_of('/'));

        ProcessNode(scene->mRootNode, scene);
    }

    void Model::ProcessNode(aiNode *node, const aiScene *scene) {

        // process all the node's meshes (if any)
        for(auto i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            m_Meshes.push_back(ProcessMesh(mesh, scene));
        }
        // recursive call for all child
        for(auto i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }

    }

    Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {

        std::vector<Vertex>             vertices;
        std::vector<uint32_t>           indices;
        std::vector<OpenGLTexturePtr>   textures;

        // Deal with vertices
        for (auto i = 0; i < mesh->mNumVertices; ++i)
        {
            // create a new vertex object
            Vertex vertex;

            // Retrieve position
            glm::vec3 vec;
            vec.x = mesh->mVertices[i].x;
            vec.y = mesh->mVertices[i].y;
            vec.z = mesh->mVertices[i].z;
            vertex.Position = vec;
            vertex.Color = glm::vec3(1.0f, 1.0f, 1.0f);

            // Retrieve Normals
            vec.x = mesh->mNormals[i].x;
            vec.y = mesh->mNormals[i].y;
            vec.z = mesh->mNormals[i].z;
            vertex.Normal = vec;

            // Retrieve Texture UVs (if any)
            if( mesh->mTextureCoords[0] )
            {
                glm::vec2 texcoord;
                texcoord.x = mesh->mTextureCoords[0][i].x;
                texcoord.y = mesh->mTextureCoords[0][i].y;
                vertex.TexUV = texcoord;
            } else // else just give it default coords
            {
                vertex.TexUV = glm::vec2(0.0f, 0.0f);
            }

            // Push this vertex to the vertices list
            vertices.push_back(vertex);
        }

        // Deal with indices
        for (auto i = 0; i < mesh->mNumFaces; ++i)
        {
            aiFace face = mesh->mFaces[i];
            for (auto j = 0; j < face.mNumIndices; ++j)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        Mesh _mesh(vertices, indices);
        // Deal with materials
        if ( mesh->mMaterialIndex >= 0 )
        {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<OpenGLTexturePtr> diffuseMaps = LoadTextures(material, aiTextureType_DIFFUSE, "diffuse");
            //m_Textures.insert(m_Textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            std::vector<OpenGLTexturePtr> specularMaps = LoadTextures(material, aiTextureType_SPECULAR, "specular");
            //m_Textures.insert(m_Textures.end(), specularMaps.begin(), specularMaps.end());

            // TODO: improve this
            for (auto & diffuseTex : diffuseMaps)
            {
                _mesh.AddTexture(diffuseTex);
            }

            for (auto& texture : specularMaps)
            {
                _mesh.AddTexture(texture);
            }


        }
        return _mesh;

    }

    std::vector<OpenGLTexturePtr>
    Model::LoadTextures(aiMaterial *material, aiTextureType type, const std::string &typeName) {

        std::vector<OpenGLTexturePtr> ModelTextures;

        for (auto i = 0; i < material->GetTextureCount(type); ++i )
        {
            aiString str;
            material->GetTexture(type, i, &str);
            std::string textureStr = std::string (str.C_Str()); // convert aiString to std::string cuz our TextureManager deals with std::strings

            ModelTextures.push_back(  m_pTextureManager->CreateTextureFromFile((m_ModelFilePath + "/" + textureStr), typeName) );
        }

        return ModelTextures;

    }

    void Model::Draw(ShaderProgram &shader) {

        for (auto& mesh : m_Meshes)
        {
            mesh.Draw(shader);
        }

    }

    void Model::CleanUp() {
        for (auto& mesh : m_Meshes)
        {
            mesh.CleanUp();
        }

    }
}