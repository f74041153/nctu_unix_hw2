#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <getopt.h>
#include <vector>
#include <dlfcn.h>

using namespace std;

struct SYS_CMD{
	vector<string> argv;
};

struct SB_CMD{
	string sopath;
	string basedir;
	struct SYS_CMD sys_cmd;
};

int sb_separate(int argc, char* argv[], struct SB_CMD& sb_cmd){
	
	string help = "usage: ./sandbox [-p sopath] [-d basedir] [--] cmd [cmd args ...]\n \
        -p: set the path to sandbox.so, default = ./sandbox.so\n \
        -d: the base directory that is allowed to access, default = .\n \
        --: seperate the arguments for sandbox and for the executed command";
	
	int separator = argc;
	for(int i = 0; i < argc; i++){
		if(!strcmp(argv[i],"--")){
				separator = i;	
				break;
		}
	}

	int c;
	while((c = getopt(separator,argv,"p:d:")) != -1){
			switch(c){
					case 'p':
						cout << optarg << endl;
						sb_cmd.sopath = optarg;
						break;
					case 'd':
						cout << optarg << endl;
						sb_cmd.basedir = optarg;
						break;
					default:
						cout << help << endl;
						return -1;
						break;
			}
	}

	while(optind < argc){
		if(optind != separator){
			cout << "exec: "<<argv[optind] << endl;
			sb_cmd.sys_cmd.argv.push_back(argv[optind]);
		}
		optind++;
	}
	return 0;
}

static void (*set_up_filter)(void) = NULL;

int main(int argc, char* argv[]){
	struct SB_CMD sb_cmd;
	sb_cmd.sopath = "./sandbox.so";
	sb_cmd.basedir = ".";

	if(sb_separate(argc,argv,sb_cmd) == -1) return 0;

	if(set_up_filter == NULL){
		void* handle = dlopen(sb_cmd.sopath.c_str(),RTLD_LAZY);
		if(handle!=NULL){
			set_up_filter = (void(*)(void))dlsym(handle,"set_up_filter");
		}
	}

	if(set_up_filter != NULL){ 
		set_up_filter();
	}
	return 0;
}
