#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static char *hello_world(ngx_conf_t *cf_st, ngx_command_t *cmd, void *conf);

static ngx_command_t commands[] = {
	{
		ngx_string("print_hello_world"),
		NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
		hello_world,
		0,
		0,
		NULL
	},
	ngx_null_command
};

static ngx_http_module_t  module_context = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

ngx_module_t ngx_module = {
	NGX_MODULE_V1,
	&module_context,
	commands,
	NGX_HTTP_MODULE,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NGX_MODULE_V1_PADDING
};

static ngx_int_t handler(ngx_http_request_t *req)
{
	static u_char ngx_hello_world[] = "Hello World!\n";

	req->headers_out.content_type.len = sizeof("text/plain") - 1;
	req->headers_out.content_type.data = (u_char *) "text/plain";

	req->headers_out.status = NGX_HTTP_OK;
	req->headers_out.content_length_n = sizeof(ngx_hello_world);

	ngx_http_send_header(req);

	ngx_buf_t *new_buf = ngx_pcalloc(req->pool, sizeof(ngx_buf_t));

	ngx_chain_t out;

	out.buf = new_buf;
	out.next = NULL;

	new_buf->pos = ngx_hello_world;
	new_buf->last = ngx_hello_world + sizeof(ngx_hello_world);
	new_buf->memory = 1;
	new_buf->last_buf = 1;

	return ngx_http_output_filter(req, &out);
}

static char *hello_world(ngx_conf_t *cf_st, ngx_command_t *cmd, void *conf)
{
	ngx_http_core_loc_conf_t  *core_loc_conf = ngx_http_conf_get_module_loc_conf(cf_st, ngx_http_core_module);
	core_loc_conf->handler = handler;
	return NGX_CONF_OK;
}
