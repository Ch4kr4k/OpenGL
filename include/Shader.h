#pragma once

#include <string>
#include <datatypes.h>

enum class ShaderType {
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	std::string m_FilePath;
	u4 m_RendererID;
public:
	Shader(const std::string &filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniforms(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniforms1i(const std::string& name, int value);
	void SetUniforms1f(const std::string& name, float value);
private:
	u4 Createshader(const std::string& vertexShader, const std::string& fragmentShader);
	u4 CompileShader(u4 type, const std::string& source);
	ShaderProgramSource ParseShaders(const std::string& filepath);
	int GetUniformLocation(const std::string& name);
};
