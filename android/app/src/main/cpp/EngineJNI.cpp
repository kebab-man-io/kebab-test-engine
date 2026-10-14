#include <jni.h>
#include <cstdint>

#include <android/native_window_jni.h>

#include "Engine.h"

using kebab::Engine;

extern "C" JNIEXPORT jlong JNICALL
Java_com_kebab_engine_GameEngine_nativeCreate(
    JNIEnv* env, jobject, jint width, jint height, jobject surface) {
    if (!surface) return 0;

    ANativeWindow* window = ANativeWindow_fromSurface(env, surface);
    if (!window) return 0;

    auto* engine = new Engine(static_cast<int>(width), static_cast<int>(height), window);
    return static_cast<jlong>(reinterpret_cast<std::uintptr_t>(engine));
}

extern "C" JNIEXPORT void JNICALL
Java_com_kebab_engine_GameEngine_nativeUpdate(
    JNIEnv*, jobject, jlong handle, jfloat deltaTime) {
    auto* engine = reinterpret_cast<Engine*>(static_cast<std::uintptr_t>(handle));
    if (engine) engine->update(deltaTime);
}

extern "C" JNIEXPORT void JNICALL
Java_com_kebab_engine_GameEngine_nativeRender(
    JNIEnv*, jobject, jlong handle) {
    auto* engine = reinterpret_cast<Engine*>(static_cast<std::uintptr_t>(handle));
    if (engine) engine->render();
}

extern "C" JNIEXPORT void JNICALL
Java_com_kebab_engine_GameEngine_nativeDestroy(
    JNIEnv*, jobject, jlong handle) {
    auto* engine = reinterpret_cast<Engine*>(static_cast<std::uintptr_t>(handle));
    delete engine;
}
