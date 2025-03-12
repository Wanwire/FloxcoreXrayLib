#include <jni.h>
#include <libxray-go-android.h>
#include <stdlib.h>

JNIEXPORT jlong JNICALL
Java_com_wanwire_libxraygo_XrayGo_libxrayMain(JNIEnv *env, jobject obj, jint argc,
                                              jobjectArray argv, jint envc, jobjectArray envv)
{

        // Convert Java String[] argv to char**
        char **c_argv = malloc(argc * sizeof(char *));
        for (int i = 0; i < argc; i++) {
                jstring jstr = (*env)->GetObjectArrayElement(env, argv, i);
                c_argv[i] = (char *)(*env)->GetStringUTFChars(env, jstr, NULL);
        }

        // Convert Java String[] envv to char**
        char **c_envv = malloc(envc * sizeof(char *));
        for (int i = 0; i < envc; i++) {
                jstring jstr = (*env)->GetObjectArrayElement(env, envv, i);
                c_envv[i] = (char *)(*env)->GetStringUTFChars(env, jstr, NULL);
        }

        // Call the Go function
        long result = libxray_main(argc, c_argv, envc, c_envv);

        // Free allocated memory
        for (int i = 0; i < argc; i++) {
                jstring jstr = (*env)->GetObjectArrayElement(env, argv, i);
                (*env)->ReleaseStringUTFChars(env, jstr, c_argv[i]);
        }
        for (int i = 0; i < envc; i++) {
                jstring jstr = (*env)->GetObjectArrayElement(env, envv, i);
                (*env)->ReleaseStringUTFChars(env, jstr, c_envv[i]);
        }
        free(c_argv);
        free(c_envv);

        return result;
}
