#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static ngx_int_t
ngx_http_def_cc_process_init(ngx_cycle_t *cycle);
static void
ngx_http_def_cc_process_exit(ngx_cycle_t *cycle);
static char *
ngx_http_def_cc_set_flag(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

typedef struct ngx_http_def_cc_item_s   ngx_http_def_cc_item_t;
typedef struct ngx_http_def_cc_s        ngx_http_def_cc_t;

struct ngx_http_def_cc_item_s {
    ngx_rbtree_t    node;
    ngx_int_t       num_persec;
    time_t          last_time;
};

struct ngx_http_def_cc_s {
    ngx_int_t           use_flag;   // 1: use this module, 0: not use
    ngx_rbtree_t        store_db;
    ngx_int_t           store_size; //how many items to be stored
    ngx_shm_zone_t     *shm_zone;
    
};

static ngx_http_module_t ngx_http_def_cc_module_ctx = {
    ngx_http_def_cc_add_variables,      //preconfig
    ngx_http_def_cc_main,               //postconfig
    NULL,                               //create main config
    NULL,                               //init main config
    ngx_http_def_cc_create_srv,         //create srv confg
    ngx_http_def_cc_merge_srv,          //merge srv config
    NULL,                               //create loc config
    NULL                                //merge loc configs
};

static ngx_command_t ngx_http_def_cc_module_cmd[] = {
    {   ngx_string("defense_cc_flag"),
        NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | 
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,
        ngx_http_def_cc_set_flag,
        NGX_HTTP_LOC_CONF_OFFSET,
        offsetof(ngx_http_def_cc_t, use_flag),
        NULL
    },

    {   ngx_string("defense_cc_store_size"),
        NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF |
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,
        ngx_http_def_cc_set_store_num,
        NGX_HTTP_LOC_CONF_OFFSET,
        offsetof(ngx_http_def_cc_t, store_size),
        NULL
    },

    ngx_null_command
};

ngx_module_t ngx_http_def_cc_module = {
    NGX_MODULE_V1,
    &ngx_http_def_cc_module_ctx,
    ngx_http_def_cc_module_cmd,
    NGX_HTTP_MODULE,
    ngx_http_def_cc_master_init,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ngx_http_def_cc_master_exit,
    NGX_MODULE_V1_PADDING
};


ngx_http_def_cc_t   *defense_cc_mgr;

static ngx_int_t
ngx_http_def_cc_master_init(ngx_cycle_t *cycle)
{
    if (defense_cc_mgr) {
        return NGX_ERROR;
    }

    defense_cc_mgr = 
	return NGX_OK;
}

static void
ngx_http_def_cc_master_exit(ngx_cycle_t *cycle)
{
}

static char *
ngx_http_def_cc_set_flag(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
	ngx_str_t	        *args = NULL;
    ngx_http_def_cc_t   *def_cc_conf = NULL;

	args = cf->args->elts;
    def_cc_conf = conf;

    if (ngx_strcmp(args[1], "on") == 0) {
        def_cc_conf->use_flag = 1;
    } else if (ngx_strcmp(args[1], "off") == 0) {
        def_cc_conf->use_flag = 0;
    } else {
        return NGX_ERROR;
    }
    
	return NGX_CONF_OK;
}

static char *
ngx_http_def_cc_set_store_num(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_str_t           *args = NULL;
    ngx_int_t            store_num = 0;
    ngx_http_def_cc_t   *def_cc_conf = NULL;

    args = cf->args->elts;
    def_cc_conf = conf;

    if ((store_num = ngx_atoi(args[1], ngx_strlen(args[1]))) > 100000) {
        return NGX_CONF_ERROR;
    }

    def_cc_conf->store_size = store_num;

    return NGX_CONF_OK;
}

static ngx_int_t
ngx_http_def_cc_add_variables(ngx_conf_t *cf)
{
    ngx_http_variable_t     *var = NULL;
    ngx_http_variable_t     *var_index = NULL;

}



void *
ngx_http_def_cc_create_srv(ngx_conf_t *cf)
{
    ngx_http_def_cc_t       *defense_cc_t = NULL;

    defense_cc_t = ngx_pcalloc(cf->pool, sizeof(ngx_http_def_cc_t));
    if (!defense_cc_t) {
        return NULL;
    }

    defense_cc_t->use_flag = -1;

    return defense_cc_t;
}

char *
ngx_http_def_cc_merge_srv(ngx_conf_t *cf, void *prev, void *conf)
{
    ngx_http_def_cc_t       *parent_conf = NULL;
    ngx_http_def_cc_t       *child_conf = NULL;

    parent_conf = prev;
    child_conf = conf;

    if (child_conf->use_flag == -1) {
        child_conf->use_flag = (parent_conf->use_flag == -1:
            0; parent_conf->use_flag);
    }

    return NGX_CONF_OK;
}

static ngx_int_t
ngx_http_def_cc_main(ngx_conf_t *cf)
{
}



