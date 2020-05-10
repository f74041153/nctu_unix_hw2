#include <dirent.h>
#include <dlfcn.h>
#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

bool access_granted(const char *path, char *func_name) {
  char *basedir = getenv("BASEDIR");
  char abs_path[256], abs_basedir[256];
  realpath(basedir, abs_basedir);
  realpath(path, abs_path);
  // printf("basedir: %s\n", abs_basedir);
  // printf("opendir: %s\n", abs_path);
  if (strncmp(abs_basedir, abs_path, strlen(abs_basedir))) {
    fprintf(stderr, "[sandbox] %s: access to %s is not allowed\n", func_name,
            path);
    //	errno = EACCES;
    return false;
  }
  return true;
}

int chdir(const char *pathname) {
  int rtn = -1;
  if (access_granted(pathname, "chdir")) {
    int (*_chdir)(const char *pathname) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _chdir = dlsym(handle, "chdir");
      if (_chdir != NULL) {
        rtn = _chdir(pathname);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int chmod(const char *pathname, mode_t mode) {
  int rtn = -1;
  if (access_granted(pathname, "chmod")) {
    int (*_chmod)(const char *pathname, mode_t mode) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _chmod = dlsym(handle, "chmod");
      if (_chmod != NULL) {
        rtn = _chmod(pathname, mode);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int chown(const char *pathname, uid_t owner, gid_t group) {
  int rtn = -1;
  if (access_granted(pathname, "chown")) {
    int (*_chown)(const char *pathname, uid_t owner, gid_t group) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _chown = dlsym(handle, "chown");
      if (_chown != NULL) {
        rtn = _chown(pathname, owner, group);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int creat(const char *path, mode_t mode) {
  int rtn = -1;
  if (access_granted(path, "creat")) {
    int (*_creat)(const char *path, mode_t mode) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _creat = dlsym(handle, "creat");
      if (_creat != NULL) {
        rtn = _creat(path, mode);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int creat64(const char *path, mode_t mode) {
  int rtn = -1;
  if (access_granted(path, "creat64")) {
    int (*_creat64)(const char *path, mode_t mode) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _creat64 = dlsym(handle, "creat64");
      if (_creat64 != NULL) {
        rtn = _creat64(path, mode);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

FILE *fopen(const char *pathname, const char *mode) {
  FILE *rtn = NULL;
  if (access_granted(pathname, "fopen")) {
    FILE *(*_fopen)(const char *pathname, const char *mode) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _fopen = dlsym(handle, "fopen");
      if (_fopen != NULL) {
        rtn = _fopen(pathname, mode);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

FILE *fopen64(const char *pathname, const char *mode) {
  FILE *rtn = NULL;
  if (access_granted(pathname, "fopen64")) {
    FILE *(*_fopen64)(const char *pathname, const char *mode) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _fopen64 = dlsym(handle, "fopen64");
      if (_fopen64 != NULL) {
        rtn = _fopen64(pathname, mode);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int link(const char *oldpath, const char *newpath) {
  int rtn = -1;
  if (access_granted(oldpath, "link") && access_granted(newpath, "link")) {
    int (*_link)(const char *oldpath, const char *newpath) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _link = dlsym(handle, "link");
      if (_link != NULL) {
        rtn = _link(oldpath, newpath);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int mkdir(const char *pathname, mode_t mode) {
  int rtn = -1;
  if (access_granted(pathname, "mkdir")) {
    int (*_mkdir)(const char *pathname, mode_t mode) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _mkdir = dlsym(handle, "mkdir");
      if (_mkdir != NULL) {
        rtn = _mkdir(pathname, mode);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int open(const char *pathname, int flags, ...) {
  int rtn = -1;
  if (access_granted(pathname, "open")) {
    int (*_open)(const char *pathname, int flags, mode_t mode) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _open = dlsym(handle, "open");
      if (_open != NULL) {
        mode_t mode = 0;
        va_list arg;
        va_start(arg, flags);
        mode = va_arg(arg, mode_t);
        va_end(arg);
        rtn = _open(pathname, flags, mode);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int open64(const char *pathname, int flags, ...) {
  int rtn = -1;
  if (access_granted(pathname, "open64")) {
    int (*_open64)(const char *pathname, int flags, mode_t mode) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _open64 = dlsym(handle, "open64");
      if (_open64 != NULL) {
        mode_t mode = 0;
        va_list arg;
        va_start(arg, flags);
        mode = va_arg(arg, mode_t);
        va_end(arg);
        rtn = _open64(pathname, flags, mode);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int openat(int dirfd, const char *pathname, int flags, ...) {
  int rtn = -1;
  if (access_granted(pathname, "openat")) {
    int (*_openat)(int dirfd, const char *pathname, int flags, mode_t mode) =
        NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _openat = dlsym(handle, "openat");
      if (_openat != NULL) {
        mode_t mode = 0;
        va_list arg;
        va_start(arg, flags);
        mode = va_arg(arg, mode_t);
        va_end(arg);
        rtn = _openat(dirfd, pathname, flags, mode);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int openat64(int dirfd, const char *pathname, int flags, ...) {
  int rtn = -1;
  if (access_granted(pathname, "openat64")) {
    int (*_openat64)(int dirfd, const char *pathname, int flags, mode_t mode) =
        NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _openat64 = dlsym(handle, "openat64");
      if (_openat64 != NULL) {
        mode_t mode = 0;
        va_list arg;
        va_start(arg, flags);
        mode = va_arg(arg, mode_t);
        va_end(arg);
        rtn = _openat64(dirfd, pathname, flags, mode);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

DIR *opendir(const char *name) {
  DIR *rtn = NULL;
  if (access_granted(name, "opendir")) {
    DIR *(*_opendir)(const char *name) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _opendir = dlsym(handle, "opendir");
      if (_opendir != NULL) {
        rtn = _opendir(name);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

ssize_t readlink(const char *pathname, char *buf, size_t bufsiz) {
  ssize_t rtn = -1;
  if (access_granted(pathname, "readlink")) {
    ssize_t (*_readlink)(const char *pathname, char *buf, size_t bufsiz) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _readlink = dlsym(handle, "readlink");
      if (_readlink != NULL) {
        rtn = _readlink(pathname, buf, bufsiz);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int remove(const char *pathname) {
  int rtn = -1;
  if (access_granted(pathname, "remove")) {
    int (*_remove)(const char *pathname) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _remove = dlsym(handle, "remove");
      if (_remove != NULL) {
        rtn = _remove(pathname);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int rename(const char *oldpath, const char *newpath) {
  int rtn = -1;
  if (access_granted(oldpath, "rename") && access_granted(newpath, "rename")) {
    int (*_rename)(const char *oldpath, const char *newpath) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _rename = dlsym(handle, "rename");
      if (_rename != NULL) {
        rtn = _rename(oldpath, newpath);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int rmdir(const char *pathname) {
  int rtn = -1;
  if (access_granted(pathname, "rmdir")) {
    int (*_rmdir)(const char *pathname) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _rmdir = dlsym(handle, "rmdir");
      if (_rmdir != NULL) {
        rtn = _rmdir(pathname);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int __xstat(int ver, const char *path, struct stat *stat_buf) {
  int rtn = -1;
  if (access_granted(path, "__xstat")) {
    int (*_xstat)(int ver, const char *path, struct stat *stat_buf) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _xstat = dlsym(handle, "__xstat");
      if (_xstat != NULL) {
        rtn = _xstat(ver, path, stat_buf);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int __xstat64(int ver, const char *path, struct stat64 *stat_buf) {
  int rtn = -1;
  if (access_granted(path, "__xstat64")) {
    int (*_xstat64)(int ver, const char *path, struct stat64 *stat_buf) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _xstat64 = dlsym(handle, "__xstat64");
      if (_xstat64 != NULL) {
        rtn = _xstat64(ver, path, stat_buf);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int symlink(const char *target, const char *linkpath) {
  int rtn = -1;
  if (access_granted(target, "symlink") &&
      access_granted(linkpath, "symlink")) {
    int (*_symlink)(const char *target, const char *linkpath) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _symlink = dlsym(handle, "symlink");
      if (_symlink != NULL) {
        rtn = _symlink(target, linkpath);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int unlink(const char *pathname) {
  int rtn = -1;
  if (access_granted(pathname, "unlink")) {
    int (*_unlink)(const char *pathname) = NULL;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle != NULL) {
      _unlink = dlsym(handle, "unlink");
      if (_unlink != NULL) {
        rtn = _unlink(pathname);
      }
      dlclose(handle);
    }
  }
  return rtn;
}

int execl(const char *path, const char *arg, ...) {
  fprintf(stderr, "[sandbox] execl(%s): not allowed\n", path);
  errno = EACCES;
  return -1;
}

int execlp(const char *file, const char *arg, ...) {
  char *path = strdup(getenv("PATH"));
  char *value = strtok(path, ":");
  while (value != NULL) {
    fprintf(stderr, "[sandbox] execlp(%s%s): not allowed\n", value, file);
    value = strtok(NULL, ":");
  }
  if (path)
    free(path);
  errno = EACCES;
  return -1;
}

int execle(const char *path, const char *arg, ...) {
  fprintf(stderr, "[sandbox] execle(%s): not allowed\n", path);
  errno = EACCES;
  return -1;
}

int execv(const char *path, char *const argv[]) {
  fprintf(stderr, "[sandbox] execv(%s): not allowed\n", path);
  errno = EACCES;
  return -1;
}
int execvp(const char *file, char *const argv[]) {
  char *path = strdup(getenv("PATH"));
  char *value = strtok(path, ":");
  while (value != NULL) {
    fprintf(stderr, "[sandbox] execvp(%s%s): not allowed\n", value, file);
    value = strtok(NULL, ":");
  }
  if (path)
    free(path);
  errno = EACCES;
  return -1;
}

int execve(const char *pathname, char *const argv[], char *const envp[]) {
  fprintf(stderr, "[sandbox] execve(%s): not allowed\n", pathname);
  errno = EACCES;
  return -1;
}

int system(const char *command) {
  fprintf(stderr, "[sandbox] system(%s): not allowed\n", command);
  errno = EACCES;
  return -1;
}
