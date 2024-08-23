#pragma once

#include "Renderer.h"
#include "datatypes.h"

class Texture {
private:
	u4 m_RenderID;
	std::string m_FilePath;
	u1* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(u4 slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; };

};