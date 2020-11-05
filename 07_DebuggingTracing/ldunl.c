#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

typedef int (*orig_unlinkat_f_type)(int, const char*, int);

int unlinkat(int fd, const char* filename, int flag) {
    if (strstr(filename, "FIX")) {
        errno = EPERM;
        return 1;
    }

    return ((orig_unlinkat_f_type)dlsym(RTLD_NEXT, "unlinkat"))(fd, filename, flag);
}

