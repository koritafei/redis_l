#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

size_t zmalloc_get_rss() {
  int    page = sysconf(_SC_PAGESIZE);
  size_t rss;
  char   buf[4096];
  char   filename[256];
  int    fd, count;
  char * p, *x;

  snprintf(filename, 256, "/proc/%d/stat", getpid());
  if (-1 == (fd = open(filename, O_RDONLY))) {
    printf("open file error\n");
    close(fd);
    return 0;
  }
  if (0 >= read(fd, buf, 4096)) {
    return 0;
  }
  close(fd);

  count = 23;
  p     = buf;
  while (p && count--) {
    p = strchr(p, ' ');
    if (p) {
      p++;
    }
  }
  if (! p) {
    return 0;
  }
  x = strchr(p, ' ');
  if (! x) {
    return 0;
  }
  *x = '\0';

  rss = strtoll(p, NULL, 10);
  rss *= page;
  return rss;
}

size_t get_phy_memeory() {
  return (size_t) sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE);
}

int main(int argc, char **argv) {
  size_t rss = zmalloc_get_rss();
  printf("This pid memory is %zu bytes\n", rss);
  size_t memory = get_phy_memeory();
  printf("This machine memory is %zu bytes\n", memory);
}