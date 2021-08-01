#ifndef __MTD_H__
#define __MTD_H__

#include <mtd/mtd-abi.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef bool (*cb_mtd)(int i, const char* name, struct mtd_info_user* mtd, void* ctx);

void print_mtd_info();
char* open_mtdblock(int i, int* fd, uint32_t size, int flags);
void enum_mtd_info(void* ctx, cb_mtd cb);
bool mtd_write(int mtd, uint32_t offset, uint32_t erasesize, const char* data, size_t size);

#endif // !__MTD_H__
