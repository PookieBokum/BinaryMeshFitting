#pragma once

namespace BMF {

class Camera;
class Mesh;

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool Initialize(GLFWwindow* window);
    void Shutdown();
    
    void BeginFrame();
    void EndFrame();
    
    void SetCamera(Camera* camera);
    void RenderMesh(const Mesh* mesh);

private:
    Camera* m_camera;
    GLuint m_defaultShader;
    
    void CreateDefaultShaders();
    void DeleteShaders();
};

} // namespace BMF 