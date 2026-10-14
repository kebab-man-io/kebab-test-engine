#include "Engine.h"
#include "Renderer.h"

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/native_window.h>

namespace kebab {

Engine::Engine(int width, int height, ANativeWindow* window)
    : width_(width), height_(height), window_(window),
      display_(nullptr), surface_(nullptr), context_(nullptr) {
    if (!window_) return;

    auto display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) return;
    if (!eglInitialize(display, nullptr, nullptr)) return;
    eglBindAPI(EGL_OPENGL_ES_API);

    const EGLint configAttrs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_NONE
    };

    EGLConfig config = nullptr;
    EGLint count = 0;
    if (!eglChooseConfig(display, configAttrs, &config, 1, &count) || count == 0) {
        eglTerminate(display);
        return;
    }

    const EGLint contextAttrs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
    auto surface = eglCreateWindowSurface(display, config, window_, nullptr);
    auto context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttrs);

    if (surface == EGL_NO_SURFACE || context == EGL_NO_CONTEXT ||
        !eglMakeCurrent(display, surface, surface, context)) {
        if (context != EGL_NO_CONTEXT) eglDestroyContext(display, context);
        if (surface != EGL_NO_SURFACE) eglDestroySurface(display, surface);
        eglTerminate(display);
        return;
    }

    display_ = display;
    surface_ = surface;
    context_ = context;
    glViewport(0, 0, width_, height_);
}

Engine::~Engine() {
    auto display = static_cast<EGLDisplay>(display_);
    auto surface = static_cast<EGLSurface>(surface_);
    auto context = static_cast<EGLContext>(context_);

    if (display != EGL_NO_DISPLAY) {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (context != EGL_NO_CONTEXT) eglDestroyContext(display, context);
        if (surface != EGL_NO_SURFACE) eglDestroySurface(display, surface);
        eglTerminate(display);
    }
    if (window_) ANativeWindow_release(window_);
}

void Engine::update(float deltaTime) {
    (void)deltaTime;
}

void Engine::render() {
    auto display = static_cast<EGLDisplay>(display_);
    auto surface = static_cast<EGLSurface>(surface_);
    if (display == EGL_NO_DISPLAY || surface == EGL_NO_SURFACE) return;

    Renderer::clear(0.06f, 0.08f, 0.12f, 1.0f);
    eglSwapBuffers(display, surface);
}

} // namespace kebab
