#include <gcutter.h>
#include <glib/gstdio.h>
#include "driver.h"

static gchar *base_directory;
static gchar *tmp_directory;
static grn_ctx *ctx;

void cut_startup()
{
  base_directory = g_get_current_dir();
  tmp_directory = g_build_filename(base_directory, "/tmp", NULL);
  cut_remove_path(tmp_directory, NULL);
  g_mkdir_with_parents(tmp_directory, 0700);
  g_chdir(tmp_directory);
  ctx = (grn_ctx*) g_malloc(sizeof(grn_ctx));
}

void cut_shutdown()
{
  g_chdir(base_directory);
  g_free(tmp_directory);
  g_free(ctx);
}

void cut_setup()
{
  mrn_init();
  grn_ctx_init(ctx,0);
}

void cut_teardown()
{
  grn_ctx_fin(ctx);
  mrn_deinit();
}

void test_mrn_flush_logs()
{
  cut_assert_equal_int(0, mrn_flush_logs(ctx));
}
