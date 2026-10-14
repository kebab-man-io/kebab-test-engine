#pragma once

namespace kebab {

class Engine {
public:
    Engine(int width, int height);
    ~Engine() = default;

    void update(float deltaTime);
    void render();

private:
    int width_;
    int height_;
};

} // namespace kebab
