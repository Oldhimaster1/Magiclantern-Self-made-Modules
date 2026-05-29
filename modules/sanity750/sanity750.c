#include <module.h>
#include <dryos.h>
#include <menu.h>
#include <config.h>
#include <console.h>

/*
 * 750D Dev Sanity module (safe v0.1)
 *
 * Scope intentionally limited to:
 * - Menu entries
 * - Persistent config values
 * - Console output
 *
 * No low-level hooks, no video pipeline internals, no risky property writes.
 */

static int sanity_run_count = 0;
static int sanity_last_status = 0;   /* 0=never, 1=success, 2=log_fail (reserved) */
static int sanity_log_to_file = 0;   /* 0=off, 1=on (reserved for future file logging) */

CONFIG_INT("sanity.run_count", sanity_run_count, 0);
CONFIG_INT("sanity.last_status", sanity_last_status, 0);
CONFIG_INT("sanity.log_to_file", sanity_log_to_file, 0);

static void sanity_wait_for_halfshutter(void)
{
    while (!get_halfshutter_pressed())
    {
        msleep(100);
    }
}

static void sanity_print_status(const char *title)
{
    console_show();
    printf("\n=== %s ===\n", title);
    printf("run_count   : %d\n", sanity_run_count);
    printf("last_status : %d (0=never,1=ok,2=log_fail)\n", sanity_last_status);
    printf("log_to_file : %d (0=off,1=on)\n", sanity_log_to_file);
    printf("\nHalf-shutter to exit...\n");

    sanity_wait_for_halfshutter();
    console_hide();
}

static void sanity_run_task(void *unused)
{
    (void)unused;

    /* short delay to allow menu close / UI settle */
    msleep(200);

    sanity_run_count++;
    sanity_last_status = 1;

    sanity_print_status("750D SANITY CHECK");
}

static void sanity_show_last_task(void *unused)
{
    (void)unused;

    msleep(100);
    sanity_print_status("750D SANITY LAST RESULT");
}

static void sanity_reset_task(void *unused)
{
    (void)unused;

    msleep(100);

    sanity_run_count = 0;
    sanity_last_status = 0;

    sanity_print_status("750D SANITY RESET DONE");
}

static void sanity_menu_run(void *priv, int delta)
{
    (void)priv;
    (void)delta;
    run_in_separate_task(sanity_run_task, NULL);
}

static void sanity_menu_show_last(void *priv, int delta)
{
    (void)priv;
    (void)delta;
    run_in_separate_task(sanity_show_last_task, NULL);
}

static void sanity_menu_reset(void *priv, int delta)
{
    (void)priv;
    (void)delta;
    run_in_separate_task(sanity_reset_task, NULL);
}

static struct menu_entry sanity_menu[] = {
    {
        .name = "Run 750D sanity check",
        .select = sanity_menu_run,
        .help = "Run safe module sanity routine and print status"
    },
    {
        .name = "Show last result",
        .select = sanity_menu_show_last,
        .help = "Show persisted sanity status values"
    },
    {
        .name = "Reset sanity counters",
        .select = sanity_menu_reset,
        .help = "Reset run_count and last_status to defaults"
    },
    {
        .name = "Log to file",
        .priv = &sanity_log_to_file,
        .max = 1,
        .help = "Reserved toggle for future file logging"
    }
};

static unsigned int sanity750_init(void)
{
    menu_add("Debug", sanity_menu, COUNT(sanity_menu));
    printf("sanity750: module loaded\n");
    return 0;
}

static unsigned int sanity750_deinit(void)
{
    printf("sanity750: module unloaded\n");
    return 0;
}

MODULE_INFO_START()
    MODULE_INIT(sanity750_init)
    MODULE_DEINIT(sanity750_deinit)
MODULE_INFO_END()

MODULE_CONFIGS_START()
    MODULE_CONFIG(sanity_run_count)
    MODULE_CONFIG(sanity_last_status)
    MODULE_CONFIG(sanity_log_to_file)
MODULE_CONFIGS_END()
