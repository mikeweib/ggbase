#include "ggbase.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    GG_BASE_API const char*  gg_copy_char(const char* src) {
		char* c = NULL;
		size_t len = 0;

        if (src == NULL) return c;
        
        len = strlen(src);
        c = (char*)calloc(len + 1, sizeof(char));
        memcpy(c, src, len);
        return c;
    }
    
    GG_BASE_API const char*  gg_copy_char_length(const char* src, int len) {
        char* c = NULL;

        if(src == NULL)
            return c;
        
        c = (char*)calloc(len + 1, sizeof(char));
        memcpy(c, src, len);
        return c;
    }



#ifdef __cplusplus
}
#endif