package com.kebab.engine

import android.app.Activity
import android.os.Bundle
import android.view.SurfaceHolder
import android.view.SurfaceView

class MainActivity : Activity() {
    private lateinit var surfaceView: SurfaceView
    private val engine = GameEngine()
    @Volatile private var running = false
    private var renderThread: Thread? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        surfaceView = SurfaceView(this)
        setContentView(surfaceView)

        surfaceView.holder.addCallback(object : SurfaceHolder.Callback {
            override fun surfaceCreated(holder: SurfaceHolder) {
                startLoop(holder)
            }

            override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) = Unit

            override fun surfaceDestroyed(holder: SurfaceHolder) {
                running = false
                renderThread?.join(1000)
                renderThread = null
            }
        })
    }

    private fun startLoop(holder: SurfaceHolder) {
        running = true
        renderThread = Thread {
            engine.create(surfaceView.width, surfaceView.height, holder.surface)

            var last = System.nanoTime()
            try {
                while (running) {
                    val now = System.nanoTime()
                    val delta = (now - last) / 1_000_000_000.0f
                    last = now

                    engine.update(delta)
                    engine.render()

                    Thread.sleep(8)
                }
            } finally {
                engine.destroy()
            }
        }.also { it.start() }
    }

    override fun onDestroy() {
        running = false
        renderThread?.join(1000)
        super.onDestroy()
    }
}
