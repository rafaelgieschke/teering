#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    return 2;
  }
  int size = atoi(argv[2]);
  int pos = 0;
  int fd = open(argv[1], O_RDWR | O_CREAT, 0666);
  if (fd == -1) {
    perror("open");
    return 1;
  }
  if (ftruncate(fd, size) == -1) {
    perror("ftruncate");
    return 1;
  }
  char *file = mmap(0, size, PROT_WRITE, MAP_SHARED, fd, 0);
  close(fd);
  if (file == MAP_FAILED) {
    perror("mmap");
    return 1;
  }
  for (int len; (len = read(0, file + pos, size - pos)) > 0; pos += len, pos = pos == size ? 0 : pos);
}
