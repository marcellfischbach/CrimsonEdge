#pragma  once

#include <ceCore/graphics/erenderpass.hh>

namespace ce
{

class GfxMesh;
namespace opengl
{

extern bool material_shader_compare_less(const GfxMesh *mesh0, const GfxMesh *mesh1, eRenderPass pass);
extern bool material_shader_compare_less_forward(const GfxMesh *mesh0, const GfxMesh *mesh1);

}

}