#include "ggbase.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef WIN32
gg_cond_t GG_BASE_API gg_cond_create() {
	gg_cond_t event = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (event == NULL) {

	}
	return event;
}

void GG_BASE_API gg_cond_destroy(gg_cond_t event) {
	CloseHandle(event);
}

void GG_BASE_API gg_cond_signal(gg_cond_t event) {
	SetEvent(event);
}

void GG_BASE_API gg_cond_wait(gg_cond_t event) {
	WaitForSingleObject(event, INFINITE);
}
#else

struct gg_cond_t_ {
	pthread_cond_t gg_cond;
	pthread_mutex_t gg_mutex;
};

gg_cond_t gg_cond_create() {
	gg_cond_t event = new gg_cond_t_;
    
    pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    
	pthread_cond_init(&event->gg_cond, 0);

	pthread_mutex_init(&event->gg_mutex, &attr);
    
    pthread_mutexattr_destroy(&attr);

	return event;
}

void gg_cond_wait(gg_cond_t event) {
	pthread_mutex_lock(&event->gg_mutex);
    pthread_cond_wait(&event->gg_cond, &event->gg_mutex);
	pthread_mutex_unlock(&event->gg_mutex);
}

void gg_cond_destroy(gg_cond_t event) {
	pthread_cond_destroy(&event->gg_cond);
	pthread_mutex_destroy(&event->gg_mutex);
	delete event;
}

void gg_cond_signal(gg_cond_t event) {
	pthread_mutex_lock(&event->gg_mutex);
    pthread_cond_signal(&event->gg_cond);
    pthread_mutex_unlock(&event->gg_mutex);
}

#endif
    
#ifdef __cplusplus
}
#endif
