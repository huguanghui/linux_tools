#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <unistd.h>

#include "backup.h"
#include "mtd.h"

static void handle_signale(int signal)
{
    printf("Ignore %s\n", strsignal(signal));
    return;
}

static void skip_signals()
{
    struct sigaction sa = {
        .sa_handler = &handle_signale,
        .sa_flags = SA_RESTART,
    };
    // Block every signal during the handler
    sigfillset(&sa.sa_mask);
    sigaction(SIGHUP, &sa, NULL);
    sigaction(SIGKILL, &sa, NULL);
    return;
}

#define MAX_NAME 32
#define MAX_MTDBLOCKS 20

typedef struct
{
    ssize_t totalsz;
    size_t erasesize;
    struct
    {
        char name[MAX_NAME];
        size_t size;
    } part[MAX_MTDBLOCKS];
    bool skip_env;
    size_t env_offset;
} mtd_restore_ctx_t;

static size_t mtd_size_by_name(mtd_restore_ctx_t* ctx, const char* name)
{
    for (int i = 0; i < MAX_MTDBLOCKS; i++) {
        if (!strcmp(ctx->part[i].name, name)) {
            return ctx->part[i].size;
        }
    }
    return -1;
}

static bool cb_mtd_restore(int i, const char* name, struct mtd_info_user* mtd, void* ctx)
{
    return true;
}

int do_upgrade(const char* filename, bool force)
{
    // chipid
    // boardid
    skip_signals();

    mtd_restore_ctx_t mtd;
    memset(&mtd, 0, sizeof(mtd));
    enum_mtd_info(&mtd, cb_mtd_restore);

    return 0;
}
