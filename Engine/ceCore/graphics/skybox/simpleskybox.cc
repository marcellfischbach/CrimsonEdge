
#include <ceCore/graphics/skybox/simpleskybox.hh>
#include <ceCore/graphics/idevice.hh>
#include <ceCore/graphics/shading/ishader.hh>
#include <ceCore/graphics/shading/ishaderattribute.hh>
#include <ceCore/resource/assetmanager.hh>

namespace ce
{

void SimpleSkybox::Render(iDevice *device)
{
  if (!Prep(device))
  {
    return;
  }


  device->SetRenderTarget(m_skyboxTarget);
  device->SetRenderBuffer(0);
  device->SetColorWrite(true, true, true, true);
  device->SetDepthWrite(false);
  device->SetDepthTest(false);
  device->SetBlending(false);
//  device->Clear(true, Color4f(0.0f, 0.0f, 0.0f, 1.0f), false, 1.0f, false, 0);

  device->SetShader(m_prepShader);
  device->RenderFullscreen();


}


bool SimpleSkybox::Prep(iDevice *device)
{
  return PrepShader() && PrepRenderTarget(device);
}

bool SimpleSkybox::PrepShader()
{
  if (m_prepShader)
  {
    return true;
  }

  m_prepShader = AssetManager::Get()->Get<iShader>("/shaders/gl4/skybox/simple/simple_skybox.shader");
  return m_prepShader;
}

bool SimpleSkybox::PrepRenderTarget(ce::iDevice *device)
{
  if (m_skyboxTexture && m_skyboxTarget)
  {
    return true;
  }

  uint16_t skyboxSize = 2048;

  CE_RELEASE(m_skyboxTarget);
  CE_RELEASE(m_skyboxTexture);

  iTextureCube::Descriptor txtDesc {
      ePF_RGBA,
      skyboxSize,
      false // maybe later
  };

  iSampler *sampler = device->CreateSampler();
  sampler->SetFilterMode(eFM_MinMagNearest);
  sampler->SetAnisotropy(1);
  sampler->SetMinLOD(0);
  sampler->SetMaxLOD(0);
  sampler->SetAddressU(eTAM_Clamp);
  sampler->SetAddressV(eTAM_Clamp);
  sampler->SetAddressW(eTAM_Clamp);
  m_skyboxTexture = device->CreateTexture(txtDesc);
  m_skyboxTexture->SetSampler(sampler);



  iRenderTargetCube::Descriptor trgtDesc { skyboxSize };
  m_skyboxTarget = device->CreateRenderTarget(trgtDesc);
  m_skyboxTarget->AddColorTexture(m_skyboxTexture);
  return m_skyboxTarget->Compile();
}


iTextureCube *SimpleSkybox::GetTexture() const
{
  return m_skyboxTexture;
}

} // ce