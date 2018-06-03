#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jni.h>
#include <jvmti.h>
#include <jni_md.h>

JavaVM* jvm=NULL;
jvmtiEnv* jvmti;
static jvmtiCapabilities capa;
static jvmtiHeapCallbacks callbacks;
static jvmtiEventCallbacks Ecallbacks;

static void JNICALL callbackVMObjectAlloc
    (jvmtiEnv *jvmti_env, JNIEnv* jni_env, jthread thread, 
             jobject object, jclass object_klass, jlong size) 
{	jvmtiError err;
	/*jvmtiFrameInfo frames[5];
	jint count;
	err = (*jvmti)->GetStackTrace(jvmti, thread, 0, 5, frames, &count);
	if (err == JVMTI_ERROR_NONE && count >= 1) {
   		char *methodName;
   		err = (*jvmti)->GetMethodName(jvmti, frames[0].method, &methodName, NULL, NULL);
   		if (err == JVMTI_ERROR_NONE) 
      			printf("Executing method: %s", methodName);
	}*/	
	/*char *className;          
    	err = (*jvmti)->GetClassSignature(jvmti, object_klass, &className, NULL);
     	if (className != NULL) 
        	printf("type %s object allocated with size %d\n", className, (jint)size);*/
}
JNIEXPORT jint JNICALL Agent_OnAttach(JavaVM *jvm, char *options,
		void *reserved) {
	jint result = (*jvm)->GetEnv(jvm,(void** )&jvmti, JVMTI_VERSION_1_1);
	if (result != JNI_OK) {
		printf("ERROR: Unable to access JVMTI!\n");
	}
	jvmtiError err = (jvmtiError) 0;
	jclass *classes;
	jint count;
	memset(&capa,0,sizeof(jvmtiCapabilities));
	capa.can_get_thread_cpu_time=1;
	capa.can_tag_objects=1;
	capa.can_generate_vm_object_alloc_events=1;
	err = (*jvmti)->AddCapabilities(jvmti, &capa);
	if(err!=JVMTI_ERROR_NONE)
		printf("error add capabilities");
	Ecallbacks.VMObjectAlloc = &callbackVMObjectAlloc;
	//Ecallbacks.ObjectFree=;	
	err=(*jvmti)->SetEventCallbacks(jvmti, &Ecallbacks,(jint)sizeof(Ecallbacks));
	if(err!=JVMTI_ERROR_NONE)
                printf("error add event call backs");
	err=(*jvmti)->SetEventNotificationMode(jvmti,JVMTI_ENABLE,JVMTI_EVENT_VM_OBJECT_ALLOC,NULL);
        if(err!=JVMTI_ERROR_NONE)
                printf("error SET event mode");
	//err=(*jvmti)->SetEventNotificationMode(jvmti,JVMTI_ENABLE,JVMTI_EVENT_OBJECT_FREE,NULL);
        //if(err!=JVMTI_ERROR_NONE)
                //printf("error SET event mode");

	/*err = (*jvmti)->GetLoadedClasses(jvmti,&count, &classes);
	if (err) {
		printf("ERROR: JVMTI GetLoadedClasses failed!\n");
	}
	for (int i = 0; i < count; i++) {
		char *sig;
		(*jvmti)->GetClassSignature(jvmti,classes[i], &sig, NULL);
		printf("cls sig=%s\n", sig);
	}*/
	return err;
}

JNIEXPORT void JNICALL Agent_OnUnload(JavaVM *vm) {
	// nothing to do
	printf("successfully unloaded");
}

JNIEnv* create_vm(JavaVM **jvm)
{
    JNIEnv* env;
    JavaVMInitArgs args;
    JavaVMOption options;
    args.version = JNI_VERSION_1_8;
    args.nOptions = 1;
    options.optionString = "-Djava.class.path=./";
    args.options = &options;
    args.ignoreUnrecognized = 0;
    jint rv;
    rv = JNI_CreateJavaVM(jvm, (void**)&env, &args);
    if (rv < 0 || !env)
        printf("Unable to Launch JVM %d\n",rv);
    else
        printf("Launched JVM! :)\n");
    return env;
}

jint HeapIterCallBack(
     jvmtiHeapReferenceKind reference_kind, 
     const jvmtiHeapReferenceInfo* reference_info, 
     jlong class_tag, 
     jlong referrer_class_tag, 
     jlong size, 
     jlong* tag_ptr, 
     jlong* referrer_tag_ptr, 
     jint length, 
     void* user_data){
	
	switch(reference_kind){
		case JVMTI_HEAP_REFERENCE_CLASS:
			printf("Reference kind:JVMTI_HEAP_REFERENCE_CLASS\n");
			break;
		case JVMTI_HEAP_REFERENCE_FIELD:
			printf("Reference kind:JVMTI_HEAP_REFERENCE_FIELD\n");
                        break;
case JVMTI_HEAP_REFERENCE_ARRAY_ELEMENT:
                        printf("Reference kind:JVMTI_HEAP_REFERENCE_ARRAY_ELEMENT\n");
                        break;

case JVMTI_HEAP_REFERENCE_CLASS_LOADER:
                        printf("Reference kind:JVMTI_HEAP_REFERENCE_CLASS_LOADER\n");
                        break;

case JVMTI_HEAP_REFERENCE_SIGNERS:
                        printf("Reference kind:JVMTI_HEAP_REFERENCE_SIGNERS\n");
                        break;

case JVMTI_HEAP_REFERENCE_PROTECTION_DOMAIN:
                        printf("Reference kind:JVMTI_HEAP_REFERENCE_PROTECTION_DOMAIN\n");
                        break;

case JVMTI_HEAP_REFERENCE_INTERFACE:
                        printf("Reference kind:JVMTI_HEAP_REFERENCE_INTERFACE\n");
                        break;

case JVMTI_HEAP_REFERENCE_STATIC_FIELD:
                        printf("Reference kind:JVMTI_HEAP_REFERENCE_STATIC_FIELD\n");
                        break;

case JVMTI_HEAP_REFERENCE_CONSTANT_POOL:
                        printf("Reference kind:JVMTI_HEAP_REFERENCE_CONSTANT_POOL\n");
                        break;

case JVMTI_HEAP_REFERENCE_SUPERCLASS:
                        printf("Reference kind:JVMTI_HEAP_REFERENCE_SUPERCLASS\n");
                        break;

case JVMTI_HEAP_REFERENCE_MONITOR:
                        printf("Reference kind:JVMTI_HEAP_REFERENCE_MONITOR\n");
                        break;

case JVMTI_HEAP_REFERENCE_STACK_LOCAL:
                        printf("Reference kind:JVMTI_HEAP_REFERENCE_STACK_LOCAL\n");
                        break;

case JVMTI_HEAP_REFERENCE_JNI_LOCAL:
                        printf("Reference kind:JVMTI_HEAP_REFERENCE_JNI_LOCAL\n");
                        break;

case JVMTI_HEAP_REFERENCE_THREAD:
                        printf("Reference kind:JVMTI_HEAP_REFERENCE_THREAD\n");
                        break;

case JVMTI_HEAP_REFERENCE_OTHER:
                        printf("Reference kind:JVMTI_HEAP_REFERENCE_OTHER\n");
                        break;

		default:
			break;
	}
	return JVMTI_VISIT_OBJECTS;
}


int calling_method_test(JNIEnv* env)
{
   	jclass Microwave_class1;
    jmethodID construct_method;
    Microwave_class1 = (*env)->FindClass(env, "MicroWave");
    construct_method = (*env)->GetMethodID(env,Microwave_class1, "<init>", "()V");   
	jobject tmp1=(*env)->NewObject(env,Microwave_class1,construct_method);
	
	jvmtiError err;
	callbacks.heap_reference_callback=HeapIterCallBack;
	err=(*jvmti)->FollowReferences(jvmti,0,Microwave_class1,NULL,&callbacks,NULL);
	printf("heap error %d\n",err);
	jint thread_count;
	jthread* threads_pool;

	err=(*jvmti)->GetAllThreads(jvmti,&thread_count,&threads_pool);
	if(err==JVMTI_ERROR_NONE)
		printf("Threads count:%d\n",thread_count);
	else
		printf("Unexpected Error happened%d\n",err);
	jvmtiThreadInfo info;
	for(int i=0;i<thread_count;i++){
		(*jvmti)->GetThreadInfo(jvmti,threads_pool[i],&info);
		printf("Threads name:%s\n",info.name);
	}
	jclass Microwave_class;
	jmethodID sum_method;
	Microwave_class = (*env)->FindClass(env, "MicroWaveMain");
	if(Microwave_class==NULL){
		printf("Error loading class\n");
		return -1;
	}
	sum_method=(*env)->GetStaticMethodID(env,Microwave_class,"main","([Ljava/lang/String;)V");
	if(sum_method==NULL){
		printf("Error finding main method\n");
		return -1;
	}
	jint k=(*env)->CallStaticIntMethod(env,Microwave_class,sum_method);
	
	

}
int main(int argc, char **argv)
{
    //JavaVM *jvm;
    JNIEnv *env;
    env = create_vm(&jvm);
    if(env == NULL)
        return -1;
 	Agent_OnAttach(jvm,NULL,NULL);
    calling_method_test(env);
    jclass Microwave_class1;
    jmethodID construct_method;
    Microwave_class1 = (*env)->FindClass(env, "MicroWave");
	jvmtiError err=(*jvmti)->FollowReferences(jvmti,0,Microwave_class1,NULL,&callbacks,NULL);
        printf("heap error %d\n",err);

        jint thread_count;
        jthread* threads_pool;

        err=(*jvmti)->GetAllThreads(jvmti,&thread_count,&threads_pool);
        if(err==JVMTI_ERROR_NONE)
                printf("Threads count:%d\n",thread_count);
        else
                printf("Unexpected Error happened%d\n",err);
        jvmtiThreadInfo info;
        for(int i=0;i<thread_count;i++){
                (*jvmti)->GetThreadInfo(jvmti,threads_pool[i],&info);
                printf("Threads name:%s\t",info.name);
		jlong runtime;
		err=(*jvmti)->GetThreadCpuTime(jvmti,threads_pool[i],&runtime);
		if(err==JVMTI_ERROR_NONE)
			printf("running for %ld us\n",runtime/1000);
		else
			printf("Error code %d\n",err);
        }

	return 0;
}
