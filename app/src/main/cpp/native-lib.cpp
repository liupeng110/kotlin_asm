#include <jni.h>
#include <string>

extern "C" {
JNIEXPORT jstring

JNICALL Java_com_example_kotlin_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT int JNICALL MyAdd(int a, int b) {
    return a + b;
}


JNIEXPORT jint JNICALL Java_com_example_kotlin_MainActivity_intFromJNI(JNIEnv *env, jobject thiz) {
    int aa = 1;
    int bb = 5;
    int cc = 2;
//%0表示输入输出列表的第几个变量，序号从0开始
    asm(
    "mov r0,%0\n"//传入 MyAdd 第一个参数(aa)
            "mov r1,%1\n"// 传入 MyAdd 第二个参数(bb)
            "BLX MyAdd\n"//调用函数 MyAdd
            "mov %0,r0\n"// MyAdd返回值赋值给cc
    :"=r"(cc)          //C语言输出 列表
    :"r"(bb), "r"(aa)// C语言 输入列表
    :"r0", "r3", "r4"//可能改变的值
    );
    return cc;
}

}

