#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <fcntl.h>
#include <getopt.h>
#include <iostream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;

struct SYS_CMD {
  vector<char *> argv;
};

struct SB_CMD {
  string sopath;
  string basedir;
  struct SYS_CMD sys_cmd;
};

int sb_separate(int argc, char *argv[], struct SB_CMD &sb_cmd) {

  string help =
      "usage: ./sandbox [-p sopath] [-d basedir] [--] cmd [cmd args ...]\n \
        -p: set the path to sandbox.so, default = ./sandbox.so\n \
        -d: the base directory that is allowed to access, default = .\n \
        --: seperate the arguments for sandbox and for the executed command";

  int separator = argc;
  for (int i = 0; i < argc; i++) {
    if (!strcmp(argv[i], "--")) {
      separator = i;
      break;
    }
  }

  int c;
  while ((c = getopt(separator, argv, "p:d:")) != -1) {
    switch (c) {
    case 'p':
      sb_cmd.sopath = optarg;
      break;
    case 'd':
      sb_cmd.basedir = optarg;
      break;
    default:
      cout << help << endl;
      return -1;
      break;
    }
  }

  while (optind < argc) {
    if (optind != separator) {
      sb_cmd.sys_cmd.argv.push_back(argv[optind]);
    }
    optind++;
  }
  return 0;
}

void launch_cmd(struct SB_CMD sb_cmd) {
  vector<char *> cmd = sb_cmd.sys_cmd.argv;
  cmd.push_back(NULL);
  pid_t pid = fork();
  if (pid < 0) {
    cout << "fail to fork!" << endl;
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    setenv("LD_PRELOAD", sb_cmd.sopath.c_str(), 1);
    setenv("BASEDIR", sb_cmd.basedir.c_str(), 1);
    if (execvp(cmd[0], &cmd[0]) < 0) {
      cout << "child fail" << endl;
      exit(EXIT_FAILURE);
    }
  } else {
    int status;
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status)) {
      cout << "child terminal abnormally. signal no: " << WTERMSIG(status) << endl;
    }
  }
}

int main(int argc, char *argv[]) {
  struct SB_CMD sb_cmd;
  sb_cmd.sopath = "./sandbox.so";
  sb_cmd.basedir = ".";

  if (sb_separate(argc, argv, sb_cmd) != -1 && sb_cmd.sys_cmd.argv.size() > 0)
    launch_cmd(sb_cmd);

  return 0;
}
