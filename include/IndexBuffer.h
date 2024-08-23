#pragma once
#include <datatypes.h>

class IndexBuffer {
private:
	u4 m_RendererID;
	u4 m_Count;
public:
	
	IndexBuffer(const u4 *data, u4 count);
	~IndexBuffer();
	
	void Bind() const;
	void UnBind() const;
	inline u4 GetCount() const { return m_Count; }
};