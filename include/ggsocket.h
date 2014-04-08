#ifndef Base_ggsocket_h
#define Base_ggsocket_h

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef int GG_SOCKET;
    
    GG_BASE_API GG_SOCKET gg_socket_create(const int af, const int type, const int protocol);
    
    GG_BASE_API int gg_socket_connect(const GG_SOCKET sock, const char* host, const int port);
    
    GG_BASE_API int gg_socket_shutdown(const GG_SOCKET sock);
    
    GG_BASE_API int gg_socket_close(const GG_SOCKET sock);
    
    GG_BASE_API int gg_socket_send(const GG_SOCKET sock, const char* data, size_t dataSize);
    
    GG_BASE_API const char* gg_socket_recv(const GG_SOCKET sock, const int length);
    
    GG_BASE_API int gg_socket_read_int(const GG_SOCKET sock);
    
    GG_BASE_API long long gg_socket_read_long(const GG_SOCKET sock);
    
#ifdef __cplusplus
}
#endif

#endif // Base_ggsocket_h
