#pragma once

namespace BMF {

class Mesh;

class Scene {
public:
    Scene();
    ~Scene();

    void AddMesh(std::unique_ptr<Mesh> mesh);
    void Update();
    void Render(class Renderer* renderer);

private:
    std::vector<std::unique_ptr<Mesh>> m_meshes;
};

} // namespace BMF 