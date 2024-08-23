#pragma once
#include <GL/glew.h>
#include <datatypes.h>
#include <VertexArray.h>
#include <IndexBuffer.h>
#include <Shader.h>

// Macros
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLogCall(#x, __FILE__, __LINE__))

// Error Handling

void GLClearError(void);
void GLCheckError(void);
bool GLogCall(const char* function, const char* file, u2 line);

// Renderer Class

class Renderer {
public:
    void Clear() const;
    void Draw(const VertexArray &va, const IndexBuffer& ib, const Shader &shader) const;
};