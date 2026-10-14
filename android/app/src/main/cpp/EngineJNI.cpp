#include <jni.h>
#include <cstdint>

#include "Engine.h"

using kebab::Engine;

extern "C" JNIEXPORT jlong JNICALL
Java_com_kebab_engine_GameEngine_nativeCreate(
    JNIEnv*, jobject, jint width, jint height) {
    auto* engine = new Engine(static_cast<int>(width), static_cast<int>(height));
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
