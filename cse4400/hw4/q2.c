#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <time.h>
#include    <sys/types.h>
#include    <unistd.h>
#include    <fcntl.h>
#include    <errno.h>

#define     BUF_SIZE    10240

void myerror(char *s)
{
    if (errno) {
        perror(s);
    }
    else {
        fprintf(stderr, "Error: %s (errno==0)\n", s);
    }
    exit(EXIT_FAILURE);
}

void	print_uids()
{
    printf("ruid=%d euid=%d\n", getuid(), geteuid());
}

int	copyfile(int dst_id, int src_fd)
{
    // ok, we only copy once, up to BUF_SIZE bytes.
    char    buf[BUF_SIZE];
    ssize_t sz, sz_w; 

    sz = read(src_fd, buf, sizeof(buf));
    if (sz < 0) 
            return -1;
    sz_w = write(dst_id, buf, sz);
    if (sz_w < 0)
            return -2;
    if (sz != sz_w)
            return -3;	
    return 0;
}

int main(void)
{
    static const char * fn1 = "./secret.txt";
    static const char * fn2 = "./copied.txt";

    print_uids();

    int fd1, fd2;

    fd1 = open(fn1, O_RDONLY);
    if (fd1 < 0)
        myerror("open() for read failed.");

    fd2 = open(fn2, O_WRONLY|O_CREAT, 0600);
    if (fd2 < 0)
        myerror("open() for write failed.");

    int rv = copyfile(fd2, fd1);
    if (rv != 0) {
        myerror("copyfile() returned a non-zero value.");
    }

    close(fd1);
    close(fd2);

    // update secret.txt with current time.
    // Not critical in this exercise.
    fd1 = open(fn1, O_RDWR);
    if (fd1 < 0)
        myerror("open() for secret.txt for update failed.");
    if (lseek(fd1, 0, SEEK_END) == -1) 
        myerror("lseek() failed.");

    time_t  cur_time;
    time(&cur_time);
    
    char *strt = ctime(&cur_time);

    size_t len = strlen(strt);
    if (write(fd1, strt, len) < 0)
        myerror("updating secret.txt failed.");
    close(fd1);

    // drop the privilege permanently here
    
    return 0;
}
