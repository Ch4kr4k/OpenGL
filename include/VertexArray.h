#pragma once

#include "VertexBuffer.h"


class VertexBufferLayout;

class VertexArray {
private:
	u4 m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void UnBind() const;
};