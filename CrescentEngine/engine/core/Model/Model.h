//
// Created by manan on 16/08/2021.
//

#ifndef CRESCENTENGINE_MODEL_H
#define CRESCENTENGINE_MODEL_H

#include "../../../renderer/opengl/Mesh.h"
#include "../../../renderer/opengl/ShaderProgram.h"
#include "../Resource/Texture/TextureManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Log/Log.h"

namespace crescent {

    class Model {

    protected:
        std::vector<Mesh>                                                           m_Meshes;
        std::string                                                                 m_ModelFilePath;
        std::vector<OpenGLTexturePtr>                                               m_Textures;
        TextureManager*                                                             m_pTextureManager;
    public:
        void                                                                        LoadModel(const std::string &path);
    private:
        void                                                                        ProcessNode(aiNode *node, const aiScene *scene);
        Mesh                                                                        ProcessMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<OpenGLTexturePtr>                                               LoadTextures(aiMaterial *material, aiTextureType type, const std::string &typeName);
    public:
        Model() = default;
        explicit Model(TextureManager* pTm) { m_pTextureManager = pTm; } ;
        virtual ~Model() {};
    public:
        void                                                                        Draw(ShaderProgram &shader);
        void                                                                        CleanUp();

    };

}

#endif //CRESCENTENGINE_MODEL_H
