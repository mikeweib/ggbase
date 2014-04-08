#include "ggbase.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#ifdef WIN32 
    
gg_thread_t GG_BASE_API gg_thread_create(THREAD_ENTRANCE callfunc, void* data) {
    gg_thread_t thread = (gg_thread_t)_beginthreadex(NULL, 0, callfunc, data, 0, NULL);
    return thread;
}
    
void GG_BASE_API gg_thread_wait(gg_thread_t thread) {
    WaitForMultipleObjects(1, &thread, TRUE, INFINITE);
}
    
void GG_BASE_API gg_thread_destroy(gg_thread_t thread) {
    // now donothing
}

#else
    
gg_thread_t GG_BASE_API gg_thread_create(void* (callfunc)(void*), void* data) {
    gg_thread_t thread = (gg_thread_t)malloc(sizeof(pthread_t));
    pthread_create(thread, NULL, callfunc, data);
    return thread;
}

void GG_BASE_API gg_thread_wait(gg_thread_t thread) {
    pthread_join(*thread, NULL);
}
    
void GG_BASE_API gg_thread_destroy(gg_thread_t thread) {
    free(thread);
    thread = NULL;
}
#endif
    
#ifdef __cplusplus
}
#endif