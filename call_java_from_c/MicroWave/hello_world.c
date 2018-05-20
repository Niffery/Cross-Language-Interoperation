#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jni.h>

JNIEnv* create_vm(JavaVM **jvm)
{
    JNIEnv* env;
    JavaVMInitArgs args;
    JavaVMOption options[2];
    args.version = JNI_VERSION_1_8;
    args.nOptions = 2;
    options[0].optionString = "-Djava.class.path=./";
    options[1].optionString="-verbose:jni";
    args.options = options;
    args.ignoreUnrecognized = 0;
    jint rv;
    rv = JNI_CreateJavaVM(jvm, (void**)&env, &args);
    if (rv < 0 || !env)
        printf("Unable to Launch JVM %d\n",rv);
    else
        printf("Launched JVM! :)\n");
    return env;
}
static jvalue* para=NULL;

int calling_method_test(JNIEnv* env)
{
/*   	jclass Microwave_class;
    jmethodID construct_method;
    Microwave_class = (*env)->FindClass(env, "MicroWave");
    construct_method = (*env)->GetMethodID(env,Microwave_class, "<init>", "()V");   
	jobject tmp1=(*env)->NewObject(env,Microwave_class,construct_method);
	//jboject tmp2=(*env)->NewObject(env,Microwave_class,construct_method);
	jmethodID sethour=(*env)->GetMethodID(env,Microwave_class,"addHour","(I)V");
	jvalue p;
	p.i=10;
	(*env)->CallVoidMethodA(env,tmp1,sethour,&p);
	jmethodID gethour=(*env)->GetMethodID(env,Microwave_class,"getHour","()I");
	jint hour=(*env)->CallIntMethod(env,tmp1,gethour);
	printf("Hours %d\n",hour);*/
	jclass Microwave_class;
	jmethodID sum_method;
	Microwave_class = (*env)->FindClass(env, "MicroWave");
	if(Microwave_class==NULL){
		printf("Error loading class\n");
		return -1;
	}
	sum_method=(*env)->GetStaticMethodID(env,Microwave_class,"sum","(II)I");
	if(sum_method==NULL){
		printf("Error finding main method\n");
		return -1;
	}
	para=(jvalue*)malloc(sizeof(jvalue)*2);
	para[0].i=2;
	para[1].i=1;
	jint k=(*env)->CallStaticIntMethodA(env,Microwave_class,sum_method,para);
	printf("result :%d\n",k);
}
int main(int argc, char **argv)
{
    JavaVM *jvm;
    JNIEnv *env;
    env = create_vm(&jvm);
    if(env == NULL)
        return -1;
    calling_method_test(env);
	printf("Memory? %d\n",para[0].i);
	free(para);
	return 0;
}
