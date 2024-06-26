
#pragma once

#include <ceOpenGL/openglexport.hh>
#include <ceCore/imodule.hh>

namespace ce::opengl
{

class CE_OGL_API OpenGLModule : public iModule
{
public:
  bool Register(const std::vector<std::string> &args, Engine *engine) override;
  bool Initialize(const std::vector<std::string> &args, Engine *engine) override;

};

}

CE_DECLARE_LIBRARY(ceOpenGL);