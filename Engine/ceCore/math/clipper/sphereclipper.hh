
#pragma  once

#include <ceCore/coreexport.hh>
#include <ceCore/math/iclipper.hh>
#include <ceCore/defs.hh>

namespace ce
{


class CE_CORE_API SphereClipper : public iClipper
{
public:
  SphereClipper(const Vector3f &center, float radius);
  ~SphereClipper() override = default;

  CE_NODISCARD eClippingResult Test(const BoundingBox& bbox) const override;
  CE_NODISCARD eClippingResult Test(const Sphere& sphere) const override;
  CE_NODISCARD eClippingResult Test(const Vector3f& p) const override;

private:

  Vector3f m_center;
  float m_radius;
  float m_radiusSqr;
};


}