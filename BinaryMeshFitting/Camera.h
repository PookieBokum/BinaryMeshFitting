#pragma once

namespace BMF {

class Camera {
public:
    Camera();
    ~Camera();

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    void SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane);

    void Update();
    
    const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
    const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    
    float m_fov;
    float m_aspectRatio;
    float m_nearPlane;
    float m_farPlane;
};

} // namespace BMF 