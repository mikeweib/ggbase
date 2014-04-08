#ifndef Base_ggthread_h
#define Base_ggthread_h

#ifdef __cplusplus
extern "C" {
#endif
    
#ifdef WIN32
	typedef HANDLE gg_thread_t;
	typedef unsigned (__stdcall* THREAD_ENTRANCE)(void*);

	gg_thread_t GG_BASE_API gg_thread_create(THREAD_ENTRANCE callfunc, void* data);
#else
	typedef pthread_t* gg_thread_t;

	gg_thread_t GG_BASE_API gg_thread_create(void* (callfunc)(void*), void* data);
#endif
    
    void GG_BASE_API gg_thread_wait(gg_thread_t thread);
    
    void GG_BASE_API gg_thread_destroy(gg_thread_t thread);
    
#ifdef __cplusplus
}
#endif

#endif // Base_ggthread_h
