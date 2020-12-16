#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

// typedefs used in iscan's backend/epkowa_ip_api.h the declarations below use
typedef ssize_t io_callback(void *, size_t);
typedef ssize_t ctrl_callback(size_t a, size_t b, size_t c, size_t d, size_t e, void *f);

// typedefs for function pointers to the entire api
typedef bool (*int_init_t)(int fd, io_callback *read, io_callback *write);
typedef bool (*int_init_with_ctrl_t)(int fd, io_callback *read, io_callback *write, ctrl_callback *ctrl);
typedef void (*int_fini_t)(void);
typedef int (*int_write_t)(void *data, size_t len);
typedef int (*int_read_t)(void *data, size_t len);
typedef void (*int_power_saving_mode_t)(void);
typedef int (*function_s_0_t)(unsigned int offset, unsigned int width, unsigned int resolution,
		unsigned int opt_resolution, double *table);
typedef void (*function_s_1_t)(uint8_t *in_buf, uint8_t *out_buf, unsigned int width,
		bool color, double *table);

static void *get_sym(const char *sym) {
	static void *h;
	if (!h) {
		h = dlopen("/usr/lib/iscan/libiscan-plugin-perfection-v550-real.so", RTLD_LAZY);
	}
	assert(h);
	return dlsym(h, sym);
}

bool int_init(int fd, io_callback *read, io_callback *write) {
	int_init_t orig = (int_init_t)get_sym("int_init");
	return orig(fd, read, write);
}
/*
bool int_init_with_ctrl(int fd, io_callback *read, io_callback *write, ctrl_callback *ctrl) {
	int_init_with_ctrl_t orig = (int_init_with_ctrl_t)get_sym("int_init_with_ctrl");
	return orig(fd, read, write, ctrl);
}*/

void int_fini() {
	int_fini_t orig = (int_fini_t)get_sym("int_fini");
	orig();
}

int int_read(void *data, size_t len) {
	int_read_t orig = (int_read_t)get_sym("int_read");
	int ret = orig(data, len);
	//convert and print
	fprintf(stderr, "R: ");
	for (size_t i = 0; i < len; i++) {
		fprintf(stderr, "%x ", ((unsigned char*)data)[i]);
	}
	fprintf(stderr, "\n");
	return ret;
}

int int_write(void *data, size_t len) {
	//convert and print
	fprintf(stderr, "W: ");
	for (size_t i = 0; i < len; i++) {
		fprintf(stderr, "%x ", ((unsigned char*)data)[i]);
	}
	fprintf(stderr, "\n");
	
	int_write_t orig = (int_write_t)get_sym("int_write");
	int ret = orig(data, len);
	
	return ret;
}

void int_power_saving_mode() {
	int_power_saving_mode_t orig = (int_power_saving_mode_t)get_sym("int_power_saving_mode");
	orig();
}

int function_s_0(unsigned int offset, unsigned int width, unsigned int resolution,
		unsigned int opt_resolution, double *table) {
	function_s_0_t orig = (function_s_0_t)get_sym("function_s_0");
	return orig(offset, width, resolution, opt_resolution, table);
}

void function_s_1(uint8_t *in, uint8_t *out, unsigned int width,
		bool color, double *table) {
	function_s_1_t orig = (function_s_1_t)get_sym("function_s_1");
	orig(in, out, width, color, table);
}
