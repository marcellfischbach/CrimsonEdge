
#include <csOpenGL/gl4/loading/csGL4ProgramLoader.hh>
#include <csOpenGL/gl4/shading/csGL4Program.hh>
#include <csOpenGL/gl4/shading/csGL4Shader.hh>
#include <csOpenGL/gl4/csGL4Exceptions.hh>
#include <csCore/resource/csAssetManager.hh>
#include <csCore/resource/csResourceLocator.hh>
#include <csCore/resource/csVFS.hh>

#include <tinyxml2/tinyxml2.h>


using namespace tinyxml2;

namespace cryo::opengl
{
csGL4ProgramLoader::csGL4ProgramLoader()
  : csBaseCSFAssetLoader()
{
  AddValidFile(csGL4Program::GetStaticClass(), "SHADER");
}

iObject* csGL4ProgramLoader::Load(const csCryoFile* file, const csClass* cls, const csResourceLocator& locator) const
{

  const csCryoFileElement * programElement = file->Root()->GetChild("program");
  if (!programElement)
  {
    return nullptr;
  }

  const csCryoFileElement * shadersElement = programElement->GetChild("shaders");
  if (!shadersElement)
  {
    return nullptr;
  }

  csGL4Program * program = new csGL4Program();
  for (Size i = 0, in = shadersElement->GetNumberOfChildren(); i < in; i++)
  {
    const csCryoFileElement * shaderElement = shadersElement->GetChild(i);
    if (shaderElement && shaderElement->GetTagName() == "shader")
    {
      csResourceLocator shaderResourceLocator = csResourceLocator(locator, shaderElement->GetAttribute(0)->GetValue());

      csGL4Shader * shader = csAssetManager::Get()->Load<csGL4Shader>(shaderResourceLocator);
      program->AttachShader(shader);
    }
  }
  try
  {
    program->Link();
  }
  catch (csGL4ProgramLinkException& ple)
  {
    printf("Unable to link program [%s]:\n%s\n", locator.Encoded().c_str(), ple.what());
    program->Release();
    return nullptr;
  }

  const csCryoFileElement * attributesElement = programElement->GetChild("attributes");
  if (attributesElement)
  {
    for (Size i = 0, in = attributesElement->GetNumberOfChildren(); i < in; i++)
    {
      const csCryoFileElement * attributeElement = attributesElement->GetChild(i);
      if (attributeElement && attributeElement->GetTagName() == std::string("attribute")
        && attributeElement->GetNumberOfAttributes() >= 1)
      {
        program->RegisterAttribute(attributeElement->GetAttribute(0)->GetValue());
      }
    }
  }

  return program;

}

}