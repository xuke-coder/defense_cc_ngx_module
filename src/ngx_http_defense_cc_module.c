#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static ngx_int_t
ngx_http_def_cc_process_init(ngx_cycle_t *cycle);
static void
ngx_http_def_cc_process_exit(ngx_cycle_t *cycle);
static char *
ngx_http_def_cc_set_flag(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);


static ngx_http_module_t ngx_http_def_cc_module_ctx = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

static ngx_command_t ngx_http_def_cc_module_cmd[] = {
	{ ngx_string("defense_cc_flag"),
	  NGX_HTTP_LOC_CONF,
	  ngx_http_def_cc_set_flag,
	  NGX_HTTP_LOC_CONF_OFFSET,
	  0,
	  NULL},

	 ngx_null_command
};

ngx_module_t ngx_http_def_cc_module = {
	NGX_MODULE_V1,
	&ngx_http_def_cc_module_ctx,
	ngx_http_def_cc_module_cmd,
	NGX_HTTP_MODULE,
	NULL,
	NULL,
	ngx_http_def_cc_process_init,
	NULL,
	NULL,
	ngx_http_def_cc_process_exit,
	NULL,
	NGX_MODULE_V1_PADDING
};


static ngx_int_t
ngx_http_def_cc_process_init(ngx_cycle_t *cycle)
{
	return NGX_OK;
}

static void
ngx_http_def_cc_process_exit(ngx_cycle_t *cycle)
{
}

static char *
ngx_http_def_cc_set_flag(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
	return NGX_CONF_OK;
}

