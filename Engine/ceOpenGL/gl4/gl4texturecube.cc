
#include <ceOpenGL/gl4/gl4texturecube.hh>
#include <ceOpenGL/gl4/gl4pixelformatmap.hh>
#include <ceCore/graphics/image.hh>
#include <ceCore/graphics/isampler.hh>
#include <ceCore/math/math.hh>
#include <GL/glew.h>

namespace ce::opengl
{
GL4TextureCube::GL4TextureCube()
        : iTextureCube()
        , m_size(0)
        , m_sampler(nullptr)
{
  CE_CLASS_GEN_CONSTR;
  glGenTextures(1, &m_name);
}

GL4TextureCube::~GL4TextureCube()
{
  glDeleteTextures(1, &m_name);
  m_name = 0;
}

void GL4TextureCube::Bind()
{
  glBindTexture(GL_TEXTURE_CUBE_MAP, m_name);
}

void GL4TextureCube::Unbind()
{
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

bool GL4TextureCube::Initialize(uint16_t size, ePixelFormat format, bool generateMipMaps)
{
  m_size = size;
  m_format = format;
  Bind();

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  uint8_t level = 0;

  while (true)
  {
    Level lvl;
    lvl.Size = size;
    m_level.push_back(lvl);
    for (GLenum i=0; i<6; i++)
    {
      glTexImage2D(
              GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
              level,
              GL4PixelFormatInternal[format],
              size,
              size,
              0,
              GL4PixelFormatClient[format],
              GL4PixelFormatClientDataType[format],
              nullptr
      );
    }
    if (!generateMipMaps || size == 1)
    {
      break;
    }

    size = ceMax(size / 2, 1);
    level++;
  }
  return true;
}

void GL4TextureCube::Data(eCubeFace face, const Image* image)
{
  for (uint16_t l=0; l<image->GetNumberOfLayers(); l++)
  {
    Data(face, l, image->GetPixelFormat(), image->GetData(l));
  }
}

void GL4TextureCube::Data(eCubeFace face, uint16_t level, const Image* image)
{
  Data(face, level, image->GetPixelFormat(), image->GetData(level));
}

void GL4TextureCube::Data(eCubeFace face, uint16_t level, ePixelFormat format, const void* data)
{
  if (level >= m_level.size())
  {
    return;
  }


  Level& lvl = m_level[level];
  glTexSubImage2D(
          GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<GLenum>(face),
          level,
          0, 0,
          lvl.Size, lvl.Size,
          GL4PixelFormatClient[format],
          GL4PixelFormatClientDataType[format],
          data
  );
}

void GL4TextureCube::Data(eCubeFace face, uint16_t level, uint16_t x, uint16_t y, uint16_t width, uint16_t height, ePixelFormat format, const void* data)
{
  if (level >= m_level.size())
  {
    return;
  }

  glTexSubImage2D(
          GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<GLenum>(face),
          level,
          x, y,
          width, height,
          GL4PixelFormatClient[format],
          GL4PixelFormatClientDataType[format],
          data
  );
}


void GL4TextureCube::SetSampler(iSampler* sampler)
{
  CE_SET(m_sampler, sampler);
}

iSampler* GL4TextureCube::GetSampler()
{
  return m_sampler;
}

const iSampler* GL4TextureCube::GetSampler() const
{
  return m_sampler;
}
ePixelFormat GL4TextureCube::GetFormat() const
{
  return m_format;
}

}
