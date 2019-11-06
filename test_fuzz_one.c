#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;

#define FATAL(x...) do { \
    printf("\n[-] PROGRAM ABORT : " x); \
    printf("\n         Location : %s(), %s:%u\n\n", \
         __FUNCTION__, __FILE__, __LINE__); \
    exit(1); \
  } while (0)

static u8 (*afl_init)(char *cmdline);

static u8 (*afl_get_file)(char *dst_path);

static u8 (*afl_fuzz_one)(u8 *fname, u32 stage_num);

static u8 (*afl_close)();

static u32 *afl_result;

enum {
  /* 00 */ RET_COVERAGE,
  /* 01 */ RET_CRASH,
  /* 02 */ RET_EXEC_US,
  /* 03 */ RET_NEW_PATH
};


int main(int argc, char **argv){

	void* dh;

	dh = dlopen("afl-fuzz.so", RTLD_NOW);
	if (!dh)
		FATAL("%s", dlerror());

	afl_init = dlsym(dh, "afl_init");
	if (!afl_init)
		FATAL("Symbol 'afl_init' not found.");

	afl_get_file = dlsym(dh, "afl_get_file");
	if (!afl_get_file)
		FATAL("Symbol 'afl_get_file' not found.");

	afl_fuzz_one = dlsym(dh, "afl_fuzz_one");
	if (!afl_fuzz_one)
		FATAL("Symbol 'afl_fuzz_one' not found.");

	afl_close = dlsym(dh, "afl_close");
	if (!afl_close)
		FATAL("Symbol 'afl_close' not found.");

	afl_result = dlsym(dh, "afl_result");
	if (!afl_result)
		FATAL("Symbol 'afl_result' not found.");


	if( afl_init("-o out -S S1 -- ./objdump -g @@") )
		return -1;

  printf("\n======test1======\n");
  if( afl_fuzz_one(argv[1], 1) )
  	return -2;

  printf("coverage=%d\n", afl_result[RET_COVERAGE]);
  printf("crash=%d\n", afl_result[RET_CRASH]);
  printf("exec_us=%dus\n", afl_result[RET_EXEC_US]);
  printf("new_path=%d\n", afl_result[RET_NEW_PATH]);

  printf("\n======test2======\n");
  if( afl_fuzz_one(argv[1], 1) )
  	return -2;

  printf("coverage=%d\n", afl_result[RET_COVERAGE]);
  printf("crash=%d\n", afl_result[RET_CRASH]);
  printf("exec_us=%dus\n", afl_result[RET_EXEC_US]);
  printf("new_path=%d\n", afl_result[RET_NEW_PATH]);

  afl_get_file("new_seed");

  afl_close();

  dlclose(dh);

	printf("test fuzz_one successfully.");

	return 0;
}
