//
// Created by mcel on 30.04.2024.
//

#pragma once

#include <ceCore/coreexport.hh>
#include <vector>

namespace ce
{

struct iDevice;
struct iModule;
struct iFrameRenderer;
struct iWindow;

class CE_CORE_API  Engine
{
public:
  void SetWindow(iWindow *window);
  iWindow *GetWindow();

  void SetDevice(iDevice *device);
  iDevice *GetDevice();

  void SetFrameRenderer(iFrameRenderer *frameRenderer);
  iFrameRenderer *GetFrameRenderer();

  bool Initialize(int argc, char** argv, ce::iModule *application);

private:
  iWindow        *m_window        = nullptr;
  iDevice        *m_device        = nullptr;
  iFrameRenderer *m_frameRenderer = nullptr;

  std::vector<iModule*> m_modules;

public:
  static Engine *Get();
private:
  Engine();

  static Engine *s_instance;
};

} // ce
