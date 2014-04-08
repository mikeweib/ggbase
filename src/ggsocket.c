#include "ggbase.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    GG_BASE_API GG_SOCKET gg_socket_create(const int af, const int type, const int protocol) {
		int sock;
#ifdef WIN32
		WSADATA WSAData;
		if (WSAStartup(MAKEWORD(2,0), &WSAData) != 0) {
			return 0;
		}
#endif
        sock = socket(af, type, protocol);
        if (sock == -1) {
            ggLogE("%s() socket create fail %d", __FUNCTION__, errno);
            return 0;
        }
        return (GG_SOCKET)sock;
    }
    
    GG_BASE_API int gg_socket_connect(const GG_SOCKET sock, const char* host, const int port) {
		int ret = 0;
		struct sockaddr_in client_addr  = {0};
        if (!sock) {
            ggLogE("%s() error socket.", __FUNCTION__);
            return ret;
        }
        client_addr.sin_family = AF_INET;
        client_addr.sin_port = htons(port);
        client_addr.sin_addr.s_addr = inet_addr(host);
        if (connect(sock, (const struct sockaddr*)&client_addr, sizeof(client_addr)) != 0) {
            ggLogE("%s() socket connect fail %d", __FUNCTION__, errno);
            return ret;
        }
#ifdef DEBUG
        ggLogD("%s() socket connect success {%s: %d}", __FUNCTION__ , host, port);
#endif
		ret = 1;
        return ret;
    }
    
    // shutdown socket
    GG_BASE_API int gg_socket_shutdown(const GG_SOCKET sock) {
#ifdef WIN32
        return shutdown(sock, SD_SEND);
#else
        return shutdown(sock, SHUT_WR);
#endif
    }
    
    // close socket
    GG_BASE_API int gg_socket_close(const GG_SOCKET sock) {
#ifdef WIN32
        return closesocket(sock);
#else
        return close(sock);
#endif
    }
    
    // send
    GG_BASE_API int gg_socket_send(const GG_SOCKET sock, const char* data, size_t dataSize) {
        
        size_t dataToSent = dataSize;
        char* pDataToSent = (char*)data;
        int ret;
		ssize_t dataSent;
		fd_set writeSet;
        while (1) {
            if (dataToSent == 0)
                return 1;

            FD_ZERO(&writeSet);
            FD_SET(sock, &writeSet);
            ret = select(sock + 1, NULL, &writeSet, NULL, NULL) >= 0;
            if(ret > 0) {
                if(FD_ISSET(sock, &writeSet)) {
                    dataSent = send(sock, pDataToSent, dataToSent, 0);
#ifdef DEBUG
                    ggLogD("%s() send(...) with return %d", __FUNCTION__ , dataSent);
#endif
                    if(dataSent == -1) {
                        ggLogE("%s() data send error %d", __FUNCTION__ , errno);
                        return 0;
                    } else {
                        dataToSent -= dataSent;
                        pDataToSent += dataSent;
                    }
                }
            } else if(ret == -1) {
                ggLogE("%s() select error %d", __FUNCTION__, errno);
                return 0;
            }
        }
    }
    
    
    // receive data
    GG_BASE_API const char* gg_socket_recv(const GG_SOCKET sock, const int length) {
        int readAvailable = 0;
        int bufSize = length;
        int writeAvailable;
		int bytesRead;
        char* bufBegin = (char*)calloc(bufSize, sizeof(char));
        char* bufWrite = bufBegin;
        
        while (1) {
            writeAvailable = bufSize - readAvailable;
            bytesRead = (int)recv(sock, bufWrite, writeAvailable, 0);
            if (bytesRead > 0) {
                bufWrite += bytesRead;
                readAvailable += bytesRead;
#ifdef DEBU
                ggLogD("%s() return read bytes : %d\n", __FUNCTION__, readAvailable);
#endif
                if (readAvailable == bufSize) {
                    break;
                }
            }
        }
        return bufBegin;
    }
    
    GG_BASE_API int gg_socket_read_int(const GG_SOCKET sock) {
		int ret;
        int* read = (int*)gg_socket_recv(sock, sizeof(int));
        ret = ntohl(*read);
        free((void*)read);
        return ret;
    }
    
    GG_BASE_API long long gg_socket_read_long(const GG_SOCKET sock) {
		int64_t ret;
        int64_t* read = (int64_t*)gg_socket_recv(sock, sizeof(int64_t));
        ret = ntohll(*read);
        free((void*)read);
        return ret;
    }
#ifdef __cplusplus
}
#endif
