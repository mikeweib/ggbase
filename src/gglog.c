#include "ggbase.h"

#if WIN32

gg_mutex_t m_mutex_log = NULL;

#if __cplusplus
extern "C" {
#endif
    
    void __win_log_print(const char format[], ...) {
		
		int len = 0;
		FILE* file = NULL;
        char buffer[2048];
        va_list args;
        va_start(args, format);

		if (m_mutex_log == NULL) {
			m_mutex_log = gg_mutex_create();
		}

        len = vsnprintf(buffer, 2047, format, args);
        va_end(args);
        
        OutputDebugString(buffer);
        OutputDebugString("\n");
        printf(buffer);
        printf("\n");

		gg_mutex_lock(m_mutex_log);
		file = fopen("lqnetwork_debug.log", "a");
		fwrite(buffer, sizeof(char), len, file);
		fwrite("\n", sizeof(char), 1, file);
		fflush(file);
		fclose(file);
		file = NULL;
		gg_mutex_unlock(m_mutex_log);
    }
    
#if __cplusplus
}
#endif

#endif

