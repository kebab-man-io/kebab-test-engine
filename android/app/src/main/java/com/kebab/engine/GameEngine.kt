package com.kebab.engine

class GameEngine {
    companion object {
        init {
            System.loadLibrary("kebabengine")
        }
    }

    private var handle: Long = 0L

    fun create(width: Int, height: Int) {
        check(handle == 0L) { "Engine already created" }
        handle = nativeCreate(width, height)
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

    private external fun nativeCreate(width: Int, height: Int): Long
    private external fun nativeUpdate(handle: Long, deltaTime: Float)
    private external fun nativeRender(handle: Long)
    private external fun nativeDestroy(handle: Long)
}
