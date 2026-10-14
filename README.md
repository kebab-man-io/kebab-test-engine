# Gradle properties
low ram usage setup:
org.gradle.jvmargs=-Xmx256m -XX:MaxMetaspaceSize=128m -XX:+UseSerialGC

org.gradle.workers.max=2
org.gradle.parallel=true

org.gradle.daemon.idletimeout=60000

kotlin.compiler.execution.strategy=in-process
