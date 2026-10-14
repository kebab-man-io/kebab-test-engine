#include "Engine.h"
#include "Renderer.h"

namespace kebab {

Engine::Engine(int width, int height)
    : width_(width), height_(height) {}

void Engine::update(float deltaTime) {
    (void)deltaTime;
}

void Engine::render() {
    Renderer::clear(0.06f, 0.08f, 0.12f, 1.0f);
}

} // namespace kebab
