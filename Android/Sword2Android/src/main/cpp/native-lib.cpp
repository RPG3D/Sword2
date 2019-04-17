#include <jni.h>
#include <string>
#include <dlfcn.h>

#include "Game.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_github_rpg3d_sword2android_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_github_rpg3d_sword2android_MainActivity_runGame(JNIEnv* env, jobject /* this */)
{
    void* handle = dlopen("libvulkan.so", RTLD_NOW|RTLD_LOCAL);
    char* loaderror = (char *) dlerror();
    Game game;
    game.run();
}