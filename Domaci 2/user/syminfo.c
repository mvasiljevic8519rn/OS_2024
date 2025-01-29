// #include "kernel/types.h"
// #include "kernel/stat.h"
// #include "user.h"
// #include "kernel/fcntl.h"



// int
// main(int argc, char *argv[])
// {
// 	int fd, i;

// 	if(argc <= 1){
// 		printf("cat: cannot open %s\n", argv[i]);
// 		exit();
// 	}

// 	for(i = 1; i < argc; i++){
// 		if((fd = open(argv[i], O_NOFOLLOW)) < 0){
// 			printf("cat: cannot open %s\n", argv[i]);
// 			exit();
// 		}
// 		cat(fd,argv[i]);
// 		close(fd);
// 	}
// 	exit();
// }

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"



void
cat(int fd)
{
  int n;
  char buf[512];

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    if (write(1, buf+1, n-1) != n-1) {
      printf(1, "ls: write error\n");
      exit();
    }
	printf("\n");
  }
  if(n < 0){
    printf(1, "ls: read error\n");
    exit();
  }
}
char*
fmtname(char *path)
{
	static char buf[DIRSIZ+1];
	char *p;

	for(p=path+strlen(path); p >= path && *p != '/'; p--)
		;
	p++;

	// Return blank-padded name.
	if(strlen(p) >= DIRSIZ)
		return p;
	memmove(buf, p, strlen(p));
	memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
	return buf;
}

void
ls(char *path)
{
	char buf[512];
	char *p;
	int fd;
	int fd1;
	struct dirent de;
	struct stat st;
	// int flag=0;
	if((fd = open(path, O_NOFOLLOW)) < 0){
		fprintf(2, "ls: cannot open %s\n", path);
		return;
	}

	if(fstat(fd, &st) < 0){
		fprintf(2, "ls: cannot stat %s\n", path);
		close(fd);
		return;
	}

	switch(st.type){
	case T_SYMLINK:{
			
			printf("%s ->", fmtname(path));
			int fd1 = open(path, O_NOFOLLOW);
			if(fd1 >= 0) {
			cat(fd1);
			close(fd1);
			}
			
		// printf("%s ", fmtname(path));
		
	}
		break;
	case T_FILE:
		printf("nije symlink!!!\n");
		break;
	
	case T_DIR:
		if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
			printf("ls: path too long\n");
			break;
		}
		strcpy(buf, path);
		p = buf+strlen(buf);
		*p++ = '/';
		while(read(fd, &de, sizeof(de)) == sizeof(de)){
			if(de.inum == 0)
				continue;
			memmove(p, de.name, DIRSIZ);
			p[DIRSIZ] = 0;
			stat(buf, &st);
		
			if(st.type==T_SYMLINK){
				printf("%s ->", fmtname(buf));
			int fd1 = open(buf, O_NOFOLLOW);
			if(fd1 >= 0) {
			cat(fd1);
			close(fd1);
			}
			}

		}
		break;
	}
	close(fd);
}

int
main(int argc, char *argv[])
{
	int i;

	if(argc < 2){
		ls(".");
		exit();
	}
	for(i=1; i<argc; i++)
		//printf(argv[i]);
		ls(argv[i]);
	exit();
}
