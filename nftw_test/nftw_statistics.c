/* Exercise 18-7: walk a directory tree and gather various statistics */

#include <sys/types.h>  /* Type definitions used by many programs */
#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Prototypes of commonly used library functions,
                           plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <errno.h>      /* Declares errno and defines error constants */
#include <string.h>     /* Commonly used string-handling functions */


#define _XOPEN_SOURCE 600
#include <ftw.h>
/*#include "tlpi_hdr.h"*/

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))


//int walker (const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

int max_depth = 0;
int directories = 0;
int unreadable_directories = 0;
int normal_files = 0;
int symbolic_links = 0;
int broken_links = 0;
int other_files = 0;
int stat_failed = 0;

int walker (const char *fpath, const struct stat *sb,
            int typeflag, struct FTW *ftwbuf) {
  max_depth = max(max_depth, ftwbuf->level);

  if (sb == NULL) {
    stat_failed++;
    return 0;
  }

  if (S_ISDIR(sb->st_mode)) {
    directories++;
    if (typeflag & FTW_DNR) { unreadable_directories++; }
  } else if (S_ISREG(sb->st_mode)) {
    normal_files++;
  } else if (S_ISLNK(sb->st_mode)) {
    symbolic_links++;
    if (typeflag & FTW_SL) { broken_links++; }
  } else {
    other_files++;
  }

  return 0;
}

int main (int argc, char *argv[]) {
  if (nftw(".", walker, 20, FTW_PHYS) != 0) {
    printf("tree walk failed\n");
    return -1;
  }
  printf("Maximum depth:  %d\n", max_depth);
  printf("Directories:    %d\n", directories);
  printf(" - unreadable:  %d\n", unreadable_directories);
  printf("Regular files:  %d\n", normal_files);
  printf("Symbolic links: %d\n", symbolic_links);
  printf(" - broken:      %d\n", broken_links);
  printf("Other files:    %d\n", other_files);
  printf("Stat failed:    %d\n", stat_failed);
  return 0;
}
