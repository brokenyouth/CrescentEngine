//
// Created by manan on 06/08/2021.
//

#ifndef CRESCENTENGINE_OPENGLTEXTURE_H
#define CRESCENTENGINE_OPENGLTEXTURE_H

#include <GL/glew.h>
#include "Texture.h"

#include "../../Log/Log.h"
#include "../../../../renderer/opengl/ShaderProgram.h"

namespace crescent

{
    class OpenGLTexture : public Texture
    {
    protected:
        unsigned char*                                              m_Data = nullptr;
        uint32_t                                                    m_TextureID; // this is opengl texture id
        int                                                         m_Width;
        int                                                         m_Height;

    public:
        OpenGLTexture() = default;
        OpenGLTexture(const std::string& filePath, const std::string& type);
        OpenGLTexture(int width, int height, GLenum gl_format);
    public:
        void                                                        GenerateTexture();
        void                                                        BindTextureUnit(ShaderProgram& shader, const std::string& name, uint32_t unit);
        void                                                        Release() override;
        inline unsigned char*                                       GetData() const { return m_Data; }
        inline uint32_t                                             GetTextureID() const { return m_TextureID; }

    };
    typedef std::shared_ptr<OpenGLTexture> OpenGLTexturePtr;
}


#endif //CRESCENTENGINE_OPENGLTEXTURE_H
