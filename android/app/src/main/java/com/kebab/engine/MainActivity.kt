package com.kebab.engine

import android.app.Activity
import android.os.Bundle
import android.view.SurfaceHolder
import android.view.SurfaceView

class MainActivity : Activity() {
    private lateinit var surfaceView: SurfaceView
    private val engine = GameEngine()
    private var running = false
    private var renderThread: Thread? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        surfaceView = SurfaceView(this)
        setContentView(surfaceView)
        surfaceView.holder.addCallback(object : SurfaceHolder.Callback {
            override fun surfaceCreated(holder: SurfaceHolder) {
                engine.create(surfaceView.width, surfaceView.height)
                startLoop()
            }

            override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) = Unit

            override fun surfaceDestroyed(holder: SurfaceHolder) {
                running = false
                renderThread?.join(500)
                engine.destroy()
            }
        })
    }

    private fun startLoop() {
        running = true
        renderThread = Thread {
            var last = System.nanoTime()
            while (running) {
                val now = System.nanoTime()
                val delta = (now - last) / 1_000_000_000.0f
                last = now
                engine.update(delta)
                // EGL/Surface integration will be added in the next renderer milestone.
                Thread.sleep(8)
            }
        }.also { it.start() }
    }

    override fun onDestroy() {
        running = false
        super.onDestroy()
    }
}
