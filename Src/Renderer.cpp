#include <Renderer.h>
#include <iostream>

// error handling
void GLClearError(void)
{
    while (glGetError() != GL_NO_ERROR);
}

void GLCheckError(void)
{
    while (GLenum error = glGetError()) {
        std::cout << error << std::endl;
    }
}
bool GLogCall(const char* function, const char* file, u2 line)
{
    while (GLenum error = glGetError()) {
        std::cout << "[Opengl Error]: (" << error << ")" << "[" << function
            << "]->(" << file << ") (" << line << ")" << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
