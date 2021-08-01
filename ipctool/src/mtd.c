#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "mtd.h"

void print_mtd_info()
{
    return;
}

char* open_mtdblock(int i, int* fd, uint32_t size, int flags)
{
    return NULL;
}

void enum_mtd_info(void* ctx, cb_mtd cb)
{
    FILE* fp = NULL;
    char dev[80], name[80];
    int i, es, ee;
    struct mtd_info_user mtd;

    if ((fp = fopen("/proc/mtd", "r"))) {
        bool running = true;
        while (fgets(dev, sizeof(dev), fp) && running) {
            name[0] = 0;
            if (sscanf(dev, "mtd%d: %x %x \"%64[^\"]\"", &i, &es, &ee, name)) {
                snprintf(dev, sizeof(dev), "/dev/mtd%d", i);
                int devfd = open(dev, O_RDWR);
                if (devfd < 0) {
                    continue;
                }
                if (ioctl(devfd, MEMGETINFO, &mtd) >= 0) {
                    if (0 == cb(i, name, &mtd, ctx)) {
                        running = false;
                    }
                }
                close(devfd);
            }
        }
        fclose(fp);
    }
    return;
}

bool mtd_write(int mtd, uint32_t offset, uint32_t erasesize, const char* data, size_t size)
{
    return true;
}
