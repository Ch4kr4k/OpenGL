#pragma once

#include "datatypes.h"
#include <vector>
#include "GL/glew.h"
#include "Renderer.h"

struct VertexBufferElement {
	u4 type;
	u4 count;
	u1 normalized;

	VertexBufferElement(u4 type, u4 count, u1 normalized)
		: type(type), count(count), normalized(normalized) {}

	static u4 GetSizeOfType(u4 type) {
		switch (type) {
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}

};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements;
	u4 m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0) {}

	template<typename T>
	void Push(u4 count)
	{ 
		static_assert(false);
		
	}

	template<>
	void Push<float>(u4 count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<u4>(u4 count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<u1>(u4 count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline u4 GetStride() const { return m_Stride; }
};