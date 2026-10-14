#pragma once

struct ANativeWindow;

namespace kebab {

class Engine {
public:
    Engine(int width, int height, ANativeWindow* window);
    ~Engine();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    void update(float deltaTime);
    void render();

private:
    int width_;
    int height_;
    ANativeWindow* window_;
    void* display_;
    void* surface_;
    void* context_;
};

} // namespace kebab
