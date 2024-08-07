#include <ceOpenGL/gl4/shading/gl4program.hh>
#include <ceOpenGL/gl4/shading/gl4shader.hh>
#include <ceOpenGL/gl4/shading/gl4shaderattribute.hh>
#include <ceOpenGL/gl4/shading/gl4shaderattributenull.hh>
#include <ceOpenGL/gl4/gl4exceptions.hh>
#include <GL/glew.h>


namespace ce::opengl
{


GL4Program::GL4Program()
{
  CE_CLASS_GEN_CONSTR;
  m_name = glCreateProgram();
}

GL4Program::~GL4Program()
{
  if (m_name)
  {
    glDeleteProgram(m_name);
    m_name = 0;
  }

  for (GL4Shader *shader: m_shaders)
  {
    shader->Release();
  }
  m_shaders.clear();
}

void GL4Program::AttachShader(GL4Shader *shader)
{
  if (!shader)
  {
    return;
  }
  if (std::ranges::find(m_shaders.begin(), m_shaders.end(), shader) != m_shaders.end())
  {
    return;
  }

  shader->AddRef();
  m_shaders.push_back(shader);

  glAttachShader(m_name, shader->GetName());
}

void GL4Program::DetachShader(GL4Shader *shader)
{
  if (!shader)
  {
    return;
  }
  auto it = std::ranges::find(m_shaders.begin(), m_shaders.end(), shader);
  if (it == m_shaders.end())
  {
    return;
  }


  glDetachShader(m_name, shader->GetName());
  m_shaders.erase(it);
  shader->Release();
}

void GL4Program::Link()
{
  glLinkProgram(m_name);
  GLint state;
  glGetProgramiv(m_name, GL_LINK_STATUS, &state);
  if (state == GL_FALSE)
  {
    GLchar  buffer[4096];
    GLsizei length;
    glGetProgramInfoLog(m_name, 4096, &length, buffer);
    buffer[length] = '\0';
    throw GL4ProgramLinkException(std::string(buffer));
  }

  m_attributes.clear();
  RegisterRenderAttributes();
}

uint32_t GL4Program::GetName() const
{
  return m_name;
}


void GL4Program::RegisterRenderAttributes()
{
  RegisterAttribute("ModelMatrix");
  RegisterAttribute("ViewMatrix");
  RegisterAttribute("ProjectionMatrix");
  RegisterAttribute("ModelViewMatrix");
  RegisterAttribute("ViewProjectionMatrix");
  RegisterAttribute("ModelViewProjectionMatrix");
  RegisterAttribute("ModelMatrixInv");
  RegisterAttribute("ViewMatrixInv");
  RegisterAttribute("ProjectionMatrixInv");
  RegisterAttribute("ModelViewMatrixInv");
  RegisterAttribute("ViewProjectionMatrixInv");
  RegisterAttribute("ModelViewProjectionMatrixInv");

  RegisterAttribute("Random");

  RegisterAttribute("ShadowMapViewMatrix");
  RegisterAttribute("ShadowMapProjectionMatrix");
  RegisterAttribute("ShadowMapViewProjectionMatrix");

  RegisterAttribute("RenderLayer");

  RegisterAttribute("LightColor");
  RegisterAttribute("LightVector");
  RegisterAttribute("LightRange");
  RegisterAttribute("LightCount");
  RegisterAttribute("LightCastShadow");
  RegisterAttribute("LightShadowMap");

  RegisterAttribute("PointLightShadowMapMappingBias");
  RegisterAttribute("PointLightShadowMapColor");
  RegisterAttribute("PointLightShadowMapDepth");

  RegisterAttribute("DirectionalLightShadowMapSplitLayers");
  RegisterAttribute("DirectionalLightShadowMapViewProjectionMatrix");
  RegisterAttribute("DirectionalLightShadowMapDepth");
  RegisterAttribute("DirectionalLightShadowMapColor");
  RegisterAttribute("DirectionalLightShadowMapLayersBias");

  RegisterAttribute("SkeletonMatrices");


//  RegisterAttribute("DirectionalLightShadowMapLayersBias");
//  RegisterAttribute("DirectionalLightShadowMapMatrices");
//  RegisterAttribute("DirectionalLightShadowMapColor");
//  RegisterAttribute("DirectionalLightShadowMapDepth");

}

Size GL4Program::RegisterAttribute(const std::string &attributeName)
{
  for (uint32_t i = 0; i < m_attributes.size(); i++)
  {
    iShaderAttribute *attribute = m_attributes[i];
    if (attribute && attribute->GetName() == attributeName)
    {
      return i;
    }
  }

  std::string      locationName = "ce_" + attributeName;
  GLint            location     = glGetUniformLocation(m_name, locationName.c_str());
  iShaderAttribute *attribute   = nullptr;
  if (location != -1)
  {
    attribute = new GL4ShaderAttribute(location, attributeName);
  }
  m_attributes.push_back(attribute);
  return m_attributes.size() - 1;
}

Size GL4Program::GetAttributeId(const std::string &attributeName)
{
  for (uint32_t i = 0; i < m_attributes.size(); i++)
  {
    iShaderAttribute *attribute = m_attributes[i];

    if (attribute && attribute->GetName() == attributeName)
    {
      return i;
    }
  }

  return ~0x00;
}


iShaderAttribute *GL4Program::GetShaderAttribute(uint32_t id)
{
  if (id >= m_attributes.size())
  {
    return nullptr;
  }
  return m_attributes[id];
}


iShaderAttribute *GL4Program::GetShaderAttribute(const std::string &attributeName)
{
  for (auto attribute: m_attributes)
  {
    if (attribute && attribute->GetName() == attributeName)
    {
      return attribute;
    }
  }
  return nullptr;
}


iShaderAttribute *GL4Program::GetShaderAttribute(eShaderAttribute shaderAttribute)
{
  return m_attributes[shaderAttribute];
}


}