#pragma once

#include <ceOpenGL/openglexport.hh>
#include <ceCore/graphics/shading/ishaderattribute.hh>
#include <GL/glew.h>

namespace ce::opengl
{


class GL4ShaderAttribute : public iShaderAttribute
{
public:
	GL4ShaderAttribute(GLint location, const std::string &name);

	const std::string& GetName() const override;

	bool IsValid() const override;

	void SetArrayIndex(Size idx) override;
	void Bind(float x) override;
	void Bind(float x, float y) override;
	void Bind(float x, float y, float z) override;
	void Bind(float x, float y, float z, float w) override;
	void Bind(int x) override;
	void Bind(int x, int y) override;
	void Bind(int x, int y, int z) override;
	void Bind(int x, int y, int z, int w) override;
	void Bind(const Vector2f& v) override;
	void Bind(const Vector3f& v) override;
	void Bind(const Vector4f& v) override;
	void Bind(const Color4f& v) override;
	void Bind(const Matrix3f& v) override;
	void Bind(const Matrix3f* v, Size count) override;
	void Bind(const Matrix4f& v) override;
	void Bind(const Matrix4f* v, Size count) override;

private:
	GLint m_location;
	GLint m_arrayIndex;
	GLint m_absLocation;
	std::string m_name;
};


}

