
#include <spcCore/resource/resourcelocator.hh>

namespace spc
{


ResourceLocator::ResourceLocator(const std::string& encoded)
		: m_locator(encoded)
{
}


const std::string& ResourceLocator::GetLocator() const
{
	return m_locator;
}

}