#pragma once
#include <datatypes.h>

class VertexBuffer {
private:
	u4 m_RendererID;
public:
	
	VertexBuffer(const void* data, u4 size);
	~VertexBuffer();
	
	void Bind() const;
	void UnBind() const;
};