package com.kebab.engine

import android.view.Surface

class GameEngine {
    companion object {
        init {
            System.loadLibrary("kebabengine")
        }
    }

    private var handle: Long = 0L

    fun create(width: Int, height: Int, surface: Surface) {
        check(handle == 0L) { "Engine already created" }
        handle = nativeCreate(width, height, surface)
        check(handle != 0L) { "Failed to create native engine" }
    }

    fun update(deltaTime: Float) {
        if (handle != 0L) nativeUpdate(handle, deltaTime)
    }

    fun render() {
        if (handle != 0L) nativeRender(handle)
    }

    fun destroy() {
        if (handle != 0L) {
            nativeDestroy(handle)
            handle = 0L
        }
    }

    private external fun nativeCreate(width: Int, height: Int, surface: Surface): Long
    private external fun nativeUpdate(handle: Long, deltaTime: Float)
    private external fun nativeRender(handle: Long)
    private external fun nativeDestroy(handle: Long)
}
