
#include <ceCore/graphics/projector.hh>
#include <ceCore/graphics/idevice.hh>

namespace ce
{

Projector::Projector()
  : m_mode(ePM_Perspective), m_left(-1.0f), m_right(1.0f), m_bottom(-1.0f), m_top(1.0f), m_near(1.0f), m_far(1024.0)
{
  CE_CLASS_GEN_CONSTR;
}

void Projector::UpdatePerspective(float angleRad, float aspect, float near, float far)
{
  m_mode = ePM_Perspective;

  float halfAngle = angleRad / 2.0f;
  m_right = near * ceTan(halfAngle);
  m_left  = -m_right;

  m_top    = m_right * aspect;
  m_bottom = -m_top;

  m_near = near;
  m_far  = far;

}

void Projector::UpdatePerspective(float left, float right, float bottom, float top, float near, float far)
{
  m_mode   = ePM_Perspective;
  m_left   = left;
  m_right  = right;
  m_bottom = bottom;
  m_top    = top;
  m_near   = near;
  m_far    = far;
}

void Projector::UpdateOrtho(float left, float right, float bottom, float top, float near, float far)
{
  m_mode   = ePM_Orthographic;
  m_left   = left;
  m_right  = right;
  m_bottom = bottom;
  m_top    = top;
  m_near   = near;
  m_far    = far;
}

void Projector::Bind(iDevice* device) const
{

  Matrix4f projection, projectionInv;
  switch (m_mode)
  {
  case ePM_Perspective:
    device->GetPerspectiveProjection(m_left, m_right, m_bottom, m_top, m_near, m_far, projection);
    device->GetPerspectiveProjectionInv(m_left, m_right, m_bottom, m_top, m_near, m_far, projectionInv);
    break;
  case ePM_Orthographic:
    device->GetOrthographicProjection(m_left, m_right, m_bottom, m_top, m_near, m_far, projection);
    device->GetOrthographicProjectionInv(m_left, m_right, m_bottom, m_top, m_near, m_far, projectionInv);
    break;
  }

  device->SetProjectionMatrix(projection, projectionInv);

}

Matrix4f Projector::GetProjectionMatrix(iDevice* device) const
{

  Matrix4f matrix;
  switch (m_mode)
  {
  case ePM_Perspective:
    device->GetPerspectiveProjection(m_left, m_right, m_bottom, m_top, m_near, m_far, matrix);
    break;
  case ePM_Orthographic:
    device->GetOrthographicProjection(m_left, m_right, m_bottom, m_top, m_near, m_far, matrix);
    break;
  }

  return matrix;
}


Matrix4f Projector::GetProjectionMatrixInv(iDevice* device) const
{

  Matrix4f matrix;
  switch (m_mode)
  {
  case ePM_Perspective:
    device->GetPerspectiveProjectionInv(m_left, m_right, m_bottom, m_top, m_near, m_far, matrix);
    break;
  case ePM_Orthographic:
    device->GetOrthographicProjectionInv(m_left, m_right, m_bottom, m_top, m_near, m_far, matrix);
    break;
  }

  return matrix;
}


void Projector::GetPoints(float depth, Vector3f* out) const
{
  float depth_factor = 1.0f;
  switch (m_mode)
  {
  case ePM_Perspective:
    depth_factor = depth / m_near;
    break;
  case ePM_Orthographic:
    depth_factor = 1.0f;
    break;
  }

  float l = m_left * depth_factor;
  float r = m_right * depth_factor;
  float b = m_bottom * depth_factor;
  float t = m_top * depth_factor;

  out[0] = Vector3f(l, b, depth);
  out[1] = Vector3f(l, t, depth);
  out[2] = Vector3f(r, b, depth);
  out[3] = Vector3f(r, t, depth);

}

float Projector::GetNear() const
{
  return m_near;
}

float Projector::GetFar() const
{
  return m_far;
}

float Projector::GetLeft() const
{
  return m_left;
}

float Projector::GetRight() const
{
  return m_right;
}

float Projector::GetBottom() const
{
  return m_bottom;
}

float Projector::GetTop() const
{
  return m_top;
}

}