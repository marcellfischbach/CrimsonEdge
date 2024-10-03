
#pragma once

#include <ceCore/coreexport.hh>
#include <ceCore/class.hh>
#include <ceCore/math/vector3f.hh>
#include <ceCore/math/quaternion.hh>

namespace cryo
{

class Skeleton;

CS_CLASS()
class CS_CORE_API SkeletonAnimation : public CS_SUPER(iObject)
{
CS_CLASS_GEN_OBJECT;

public:
  struct FrameRotation
  {
    float     frame;
    Quaternion rotation;
  };
  struct FramePosition
  {
    float   frame;
    Vector3f position;
  };
  struct FrameScale
  {
    float   frame;
    Vector3f scale;
  };


  struct Channel
  {
    std::string                name;
    std::vector<FrameRotation> rotations;
    std::vector<FramePosition> positions;
    std::vector<FrameScale>    scales;
  };


public:
  SkeletonAnimation();
  ~SkeletonAnimation() override;

  void SetName(const std::string &name);
  const std::string &GetName() const;

  void SetNumberOfFrames(float numberOfFrames);
  float GetNumberOfFrames() const;
  
  void SetFramesPerSecond(float framesPerSecond);
  float GetFramesPerSecond () const;

  void SetLoop(bool loop);
  bool IsLoop () const;

  float GetDuration() const;


  void PushSkeleton(cryo::Skeleton *skeleton, float frame, float blendFactor) const;

  void AddRotationFrame(const std::string &channelName,
                        float frame,
                        const Quaternion &rotation);

  void AddPositionFrame(const std::string &channelName,
                        float frame,
                        const Vector3f &position);

  void AddScaleFrame(const std::string &channelName,
                        float time,
                        const Vector3f &scale);

private:

  std::string m_name;
  float       m_numberOfFrames;
  float       m_framesPerSecond;
  bool        m_loop;
  Channel &GetChannel(const std::string &channelName);
  std::vector<Channel> m_channels;
};


CS_CLASS()
class CS_CORE_API SkeletonAnimationPack : public CS_SUPER(iObject)
{
CS_CLASS_GEN_OBJECT;
public:
  SkeletonAnimationPack() = default;
  ~SkeletonAnimationPack() override = default;

  void AddAnimation(SkeletonAnimation *animation);
  SkeletonAnimation *Get(const std::string &name);


private:
  std::vector<SkeletonAnimation *> m_animations;

};

}