#pragma once

namespace BMF {

// Forward declarations
class Renderer;
class Scene;
class Camera;
class Mesh;

// Core application class
class Application {
public:
    Application();
    ~Application();

    bool Initialize();
    void Run();
    void Shutdown();

private:
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Scene> m_scene;
    std::unique_ptr<Camera> m_camera;
    
    bool m_isRunning;
    GLFWwindow* m_window;
};

// Global functions
bool InitializeGLFW();
bool InitializeGLEW();
void ErrorCallback(int error, const char* description);

} // namespace BMF 