

#pragma once

#include <ceCore/coreexport.hh>
#include <ceCore/class.hh>
#include <ceCore/math/matrix4f.hh>
#include <ceCore/math/vector3f.hh>

namespace ce
{

struct iDevice;

CE_CLASS()
class CE_CORE_API Camera : public CE_SUPER(iObject)
{
  CE_CLASS_GEN_OBJECT;
public:
  Camera();
  virtual ~Camera();

  void SetEye(const Vector3f & eye);
  const Vector3f &GetEye() const;

  void SetSpot(const Vector3f & spot);
  const Vector3f &GetSpot() const;

  void SetUp(const Vector3f & up);
  const Vector3f &GetUp() const;


  void Bind(iDevice * device) const;
  Matrix4f GetViewMatrix () const;
  Matrix4f GetViewMatrixInv () const;

private:

  Vector3f m_eye;
  Vector3f m_spot;
  Vector3f m_up;

};


}
