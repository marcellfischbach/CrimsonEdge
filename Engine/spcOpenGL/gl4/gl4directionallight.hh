

#pragma once

#include <spcOpenGL/openglexport.hh>
#include <spcCore/graphics/idirectionallight.hh>

namespace spc
{


SPC_CLASS()
class SPC_OGL_API GL4DirectionalLight : public SPC_SUPER(iDirectionalLight)
{
  SPC_CLASS_GEN_OBJECT;
public:
  GL4DirectionalLight();
  virtual ~GL4DirectionalLight();

  void SetChangeMode(eLightChangeMode changeMode) override;
  eLightChangeMode GetChangeMode() const override;

  void SetCastShadow(bool castShadow) override;
  bool IsCastShadow() const;

  void SetColor(const Color4f & color) override;
  const Color4f& GetColor() const override;

  void SetDirection(const Vector3f & direction) override;
  const Vector3f& GetDirection() const override;


private:

  eLightChangeMode m_changeMode;
  bool m_castShadow;
  Color4f m_color;

  Vector3f m_direction;

};

}
