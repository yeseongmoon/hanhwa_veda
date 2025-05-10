#include <stdio.h>
#include <sys/sysinfo.h>

int main(int argc, char *argv[]) {
  struct sysinfo system;
  sysinfo(&system);

  // uptime
  printf("Uptime: %ld\n", system.uptime);

  // 1min, 5mins, 15mins
  printf("load average 1min: %lu\n", system.loads[0]);
  printf("load average 5min: %lu\n", system.loads[1]);
  printf("load average 10min: %lu\n", system.loads[2]);

  // memory
  printf("Total Mem: %ld, Free Mem: %lu\n", system.totalram, system.freeram);

  // sway
  printf("Total swap: %ld, Free swap: %lu\n", system.totalswap,
         system.freeswap);

  // processors
  printf("A number of Processors: %d\n", system.procs);
  return 0;
}
