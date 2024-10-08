
#include <csOpenGL/gl4/csGL4RenderTarget2D.hh>
#include <csOpenGL/gl4/csGL4Texture2D.hh>
#include <csOpenGL/gl4/csGL4Texture2DArray.hh>
#include <csOpenGL/gl4/csGL4TextureCube.hh>
#include <GL/glew.h>

namespace cryo::opengl
{

csGL4RenderTarget2D::csGL4RenderTarget2D()
    : iRenderTarget2D()
    , m_name(0)
    , m_width(0)
    , m_height(0)
    , m_depthBuffer(0)
    , m_depthTexture(nullptr)
{
  CS_CLASS_GEN_CONSTR;
  glGenFramebuffers(1, &m_name);
}

csGL4RenderTarget2D::~csGL4RenderTarget2D()
{
  glDeleteFramebuffers(1, &m_name);
  m_name = 0;

  CS_RELEASE(m_depthTexture.texture);
  CS_RELEASE(m_depthTexture.textureCube);

  if (m_depthBuffer)
  {
    glDeleteRenderbuffers(1, &m_depthBuffer);
    m_depthBuffer = 0;
  }
  for (auto color: m_colorTextures)
  {
    CS_RELEASE(color.texture);
    CS_RELEASE(color.textureCube);
  }
  m_colorTextures.clear();
}

void csGL4RenderTarget2D::Bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_name);
}

uint16_t csGL4RenderTarget2D::GetWidth() const
{
  return m_width;
}


uint16_t csGL4RenderTarget2D::GetHeight() const
{
  return m_height;
}

bool csGL4RenderTarget2D::Initialize(uint16_t width, uint16_t height)
{
  m_width  = width;
  m_height = height;
  Bind();

  return true;
}

void csGL4RenderTarget2D::SetDepthTexture(iTexture2D *depthTexture)
{
  if (!depthTexture)
  {
    return;
  }


  auto txt = depthTexture->Query<csGL4Texture2D>();
  if (!txt)
  {
    return;
  }


  GLenum attachment;
  switch (depthTexture->GetFormat())
  {
    case ePF_Depth:
      attachment = GL_DEPTH_ATTACHMENT;
      break;
    case ePF_DepthStencil:
      attachment = GL_DEPTH_STENCIL_ATTACHMENT;
      break;
    default:
      return;
  }


  CS_SET(m_depthTexture.texture, txt);
  CS_RELEASE(m_depthTexture.textureArray);
  CS_RELEASE(m_depthTexture.textureCube);


  glFramebufferTexture(GL_FRAMEBUFFER,
                       attachment,
                       txt->GetName(),
                       0);

}

void csGL4RenderTarget2D::SetDepthTexture(iTexture2DArray *depthTexture, size_t layer)
{
  if (!depthTexture)
  {
    return;
  }


  auto txt = depthTexture->Query<csGL4Texture2DArray>();
  if (!txt)
  {
    return;
  }


  GLenum attachment;
  switch (depthTexture->GetFormat())
  {
    case ePF_Depth:
      attachment = GL_DEPTH_ATTACHMENT;
      break;
    case ePF_DepthStencil:
      attachment = GL_DEPTH_STENCIL_ATTACHMENT;
      break;
    default:
      return;
  }


  CS_SET(m_depthTexture.textureArray, txt);
  CS_RELEASE(m_depthTexture.texture);
  CS_RELEASE(m_depthTexture.textureCube);


  m_depthTexture.textureArrayLayer = layer;
  glFramebufferTextureLayer(GL_FRAMEBUFFER,
                            attachment,
                            txt->GetName(),
                            0,
                            static_cast<GLint>(layer));

}


void csGL4RenderTarget2D::SetDepthTexture(iTextureCube *depthTexture, eCubeFace face)
{
  if (!depthTexture)
  {
    return;
  }


  auto txt = depthTexture->Query<csGL4TextureCube>();
  if (!txt)
  {
    return;
  }

  GLenum attachment;
  switch (depthTexture->GetFormat())
  {
    case ePF_Depth:
      attachment = GL_DEPTH_ATTACHMENT;
      break;
    case ePF_DepthStencil:
      attachment = GL_DEPTH_STENCIL_ATTACHMENT;
      break;
    default:
      return;
  }


  m_depthTexture.textureCubeFace = face;
  CS_SET(m_depthTexture.textureCube, txt);
  CS_RELEASE(m_depthTexture.textureArray);
  CS_RELEASE(m_depthTexture.texture);


  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         attachment,
                         GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
                         txt->GetName(),
                         0);

}


void csGL4RenderTarget2D::SetDepthBuffer(ePixelFormat format)
{

  GLenum attachment     = 0;
  GLenum internalFormat = 0;
  switch (format)
  {
    case ePF_Depth:
      internalFormat = GL_DEPTH_COMPONENT;
      attachment     = GL_DEPTH_ATTACHMENT;
      break;
    case ePF_DepthStencil:
      internalFormat = GL_DEPTH_STENCIL;
      attachment     = GL_DEPTH_STENCIL_ATTACHMENT;
      break;
    default:
      return;
  }
  glGenRenderbuffers(1, &m_depthBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, m_width, m_height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, m_depthBuffer);

  CS_RELEASE(m_depthTexture.textureCube);
  CS_RELEASE(m_depthTexture.texture);

}

void csGL4RenderTarget2D::AddColorTexture(iTexture2D *colorTexture)
{
  if (!colorTexture)
  {
    return;
  }


  auto txt = colorTexture->Query<csGL4Texture2D>();
  if (!txt)
  {
    return;
  }

  CS_ADDREF(txt);


  if (colorTexture->GetFormat() == ePF_DepthStencil)
  {
    return;
  }


  glFramebufferTexture(GL_FRAMEBUFFER,
                       (GLenum) (GL_COLOR_ATTACHMENT0 + m_colorTextures.size()),
                       txt->GetName(),
                       0);
  TextureBind textureBind {
      txt,
      nullptr,
      nullptr,
      0,
      eCF_PosX
  };
  m_colorTextures.push_back(textureBind);
}

void csGL4RenderTarget2D::AddColorTexture(iTexture2DArray *colorTexture, size_t layer)
{
  if (!colorTexture)
  {
    return;
  }


  auto txt = colorTexture->Query<csGL4Texture2DArray>();
  if (!txt)
  {
    return;
  }

  CS_ADDREF(txt);


  if (colorTexture->GetFormat() == ePF_DepthStencil)
  {
    return;
  }


  glFramebufferTextureLayer(GL_FRAMEBUFFER,
                            (GLenum) (GL_COLOR_ATTACHMENT0 + m_colorTextures.size()),
                            txt->GetName(),
                            0,
                            static_cast<GLint>(layer));
  TextureBind textureBind {
      nullptr,
      txt,
      nullptr,
      layer,
      eCF_PosX
  };
  m_colorTextures.push_back(textureBind);
}


void csGL4RenderTarget2D::AddColorTexture(iTextureCube *colorTexture, eCubeFace face)
{
  if (!colorTexture)
  {
    return;
  }


  auto txt = colorTexture->Query<csGL4TextureCube>();
  if (!txt)
  {
    return;
  }
  CS_ADDREF(txt);


  if (colorTexture->GetFormat() == ePF_DepthStencil)
  {
    return;
  }


  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         (GLenum) (GL_COLOR_ATTACHMENT0 + m_colorTextures.size()),
                         (GLenum) (GL_TEXTURE_CUBE_MAP_POSITIVE_X + face),
                         txt->GetName(),
                         0);
  TextureBind textureBind {
      nullptr,
      nullptr,
      txt,
      0,
      face
  };
  m_colorTextures.push_back(textureBind);
}


eTextureType csGL4RenderTarget2D::GetType() const
{
  return eTextureType::Texture2D;
}

bool csGL4RenderTarget2D::Compile()
{
  GLenum res = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  switch (res)
  {
    case GL_FRAMEBUFFER_COMPLETE:
      m_log = "Complete";
      return true;
    case GL_FRAMEBUFFER_UNDEFINED:
      m_log = "Framebuffer undefined";
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
      m_log = "Framebuffer incomplete attachment";
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      m_log = "Framebuffer incomplete missing attachment";
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
      m_log = "Framebuffer incomplete draw buffer";
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
      m_log = "Framebuffer incomplete read buffer";
      break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
      m_log = "Framebuffer unsupported";
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
      m_log = "Framebuffer incomplete multisample";
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
      m_log = "Framebuffer incomplete layer targets";
      break;
  }
  return false;
}

std::string csGL4RenderTarget2D::GetCompileLog() const
{
  return m_log;
}

iTexture2D *csGL4RenderTarget2D::GetDepthTexture()
{
  return m_depthTexture.texture;
}

iTextureCube *csGL4RenderTarget2D::GetDepthTextureCube()
{
  return m_depthTexture.textureCube;
}

const iTexture2D *csGL4RenderTarget2D::GetDepthTexture() const
{
  return m_depthTexture.texture;
}

const iTextureCube *csGL4RenderTarget2D::GetDepthTextureCube() const
{
  return m_depthTexture.textureCube;
}

eCubeFace csGL4RenderTarget2D::GetDepthTextureCubeFace() const
{
  return m_depthTexture.textureCubeFace;
}


Size csGL4RenderTarget2D::GetNumberOfColorTextures() const
{
  return m_colorTextures.size();
}

iTexture2D *csGL4RenderTarget2D::GetColorTexture(Size idx)
{
  if (idx >= m_colorTextures.size())
  {
    return nullptr;
  }
  return m_colorTextures[idx].texture;
}


iTextureCube *csGL4RenderTarget2D::GetColorTextureCube(cryo::Size idx)
{
  if (idx >= m_colorTextures.size())
  {
    return nullptr;
  }
  return m_colorTextures[idx].textureCube;
}


const iTexture2D *csGL4RenderTarget2D::GetColorTexture(Size idx) const
{
  if (idx >= m_colorTextures.size())
  {
    return nullptr;
  }
  return m_colorTextures[idx].texture;
}


const iTextureCube *csGL4RenderTarget2D::GetColorTextureCube(Size idx) const
{
  if (idx >= m_colorTextures.size())
  {
    return nullptr;
  }
  return m_colorTextures[idx].textureCube;
}


eCubeFace csGL4RenderTarget2D::GetColorTextureCubeFace(Size idx) const
{
  if (idx >= m_colorTextures.size())
  {
    return eCF_PosX;
  }
  return m_colorTextures[idx].textureCubeFace;
}


}