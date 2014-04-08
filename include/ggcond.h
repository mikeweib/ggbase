#ifndef __GG_BASE_EVENT_H__
#define __GG_BASE_EVENT_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
	typedef HANDLE gg_cond_t;
#else
	struct gg_cond_t_;
	typedef struct gg_cond_t_* gg_cond_t;
#endif

    gg_cond_t GG_BASE_API gg_cond_create();

    void GG_BASE_API gg_cond_destroy(gg_cond_t event);

    void GG_BASE_API gg_cond_signal(gg_cond_t event);

    void GG_BASE_API gg_cond_wait(gg_cond_t event);


#ifdef __cplusplus
}
#endif

#endif /* __CN_BASE_EVENT_H__ */
