#pragma once

#include <dirent.h>
#include <stdio.h>
#include <fcntl.h>
#ifndef SVB_WIN32
#include <pthread.h>
#endif
#if defined(SVB_WIN32) && !defined(SVB_MINGW)
#include <poll.h>
#endif

#ifdef SVB_MINGW
#include "libnt.h"
#endif

#ifndef SVB_WIN32
pid_t xfork();
int xsetns(int fd, int nstype);
int xunshare(int flags);
int xmount(const char *source, const char *target,
           const char *filesystemtype, unsigned long mountflags,
           const void *data);
int xumount(const char *target);
int xumount2(const char *target, int flags);
int xinotify_init1(int flags);
int xmknod(const char *pathname, mode_t mode, dev_t dev);
long xptrace(int request, pid_t pid, void *addr = nullptr, void *data = nullptr);
static inline long xptrace(int request, pid_t pid, void *addr, uintptr_t data) {
    return xptrace(request, pid, addr, reinterpret_cast<void *>(data));
}
int xsocket(int domain, int type, int protocol);
int xbind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);9
int xconnect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int xlisten(int sockfd, int backlog);
int xaccept4(int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags);
ssize_t xsendmsg(int sockfd, const struct msghdr *msg, int flags);
ssize_t xrecvmsg(int sockfd, struct msghdr *msg, int flags);
int xpthread_create(pthread_t *thread, const pthread_attr_t *attr,
                    void *(*start_routine) (void *), void *arg);
#else
int xxsymlink(const char *target, const char *file);
#endif

#if defined(SVB_WIN32) && !defined(SVB_MINGW)
int xpoll(struct pollfd *fds, nfds_t nfds, int timeout);
int xopenat(int dirfd, const char *pathname, int flags);
int xopenat(int dirfd, const char *pathname, int flags, mode_t mode);
DIR *xfdopendir(int fd);
int xpipe2(int pipefd[2], int flags);
int xdup3(int oldfd, int newfd, int flags);
int xsymlink(const char *target, const char *linkpath);
int xsymlinkat(const char *target, int newdirfd, const char *linkpath);
int xlinkat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath, int flags);
ssize_t xreadlinkat(int dirfd, const char *pathname, char *buf, size_t bufsiz);
int xmkdirat(int dirfd, const char *pathname, mode_t mode);
char *xrealpath(const char *path, char *resolved_path);
int xfstatat(int dirfd, const char *pathname, struct stat *buf, int flags);
#endif

ssize_t xreadlink(const char *pathname, char *buf, size_t bufsiz);
FILE *xfopen(const char *pathname, const char *mode);
FILE *xfdopen(int fd, const char *mode);
int xopen(const char *pathname, int flags);
int xopen(const char *pathname, int flags, mode_t mode);
ssize_t xwrite(int fd, const void *buf, size_t count);
ssize_t xread(int fd, void *buf, size_t count);
ssize_t xxread(int fd, void *buf, size_t count);
off_t xlseek(int fd, off_t offset, int whence);

DIR *xopendir(const char *name);
struct dirent *xreaddir(DIR *dirp);
void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);
void *xrealloc(void *ptr, size_t size);
pid_t xsetsid();
int xaccess(const char *path, int mode);
int xstat(const char *pathname, struct stat *buf);
int xlstat(const char *pathname, struct stat *buf);
int xfstat(int fd, struct stat *buf);
int xdup(int fd);
int xdup2(int oldfd, int newfd);
int xfaccessat(int dirfd, const char *pathname);
int xrename(const char *oldpath, const char *newpath);
int xmkdir(const char *pathname, mode_t mode);
int xmkdirs(const char *pathname, mode_t mode);
void *xmmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
ssize_t xsendfile(int out_fd, int in_fd, off_t *offset, size_t count);
#define WEVENT(s) (((s) & 0xffff0000) >> 16)
