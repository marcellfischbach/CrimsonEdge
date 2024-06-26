
#pragma once

#include <ceCore/coreexport.hh>
#include <ceCore/resource/iarchive.hh>

namespace ce
{

CE_CLASS()
class CE_CORE_API FileSystemArchive : public CE_SUPER(iArchive)
{
CE_CLASS_GEN_OBJECT;
public:
  FileSystemArchive(const std::string &rootPath, int priority);
  ~FileSystemArchive() override = default;

  int GetPriority() const override;
  iFile *Open(const std::string &locator, eAccessMode accessMode, eOpenMode openMode) override;

private:
  static std::string Resolve (const std::string &rootPath);

  int         m_priority;
  std::string m_rootPath;
};

} // ce
