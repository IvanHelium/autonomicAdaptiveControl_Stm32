/*
 * cbuf.h
 *
 * Created: 18.10.2014 20:07:09
 *  Author: MiF
 */


#ifndef CBUF_H_
#define CBUF_H_

#include <stdint.h>

//#define CBUF_SIZE	1024

typedef struct _cbuf_t {
	char *data;
	char *wrptr;
	char *rdptr;
	int cnt;
	int size;
} cbuf_t;

void cbuf_init(cbuf_t *buf, char *data_ptr, int size);
void cbuf_write(cbuf_t *buf, const void *data, int len);
void cbuf_write_byte(cbuf_t *buf, uint8_t val);
void cbuf_write_bool(cbuf_t *buf, char val);
void cbuf_write_short(cbuf_t *buf, uint16_t val);
void cbuf_write_int(cbuf_t *buf, int32_t val);
void cbuf_write_int64(cbuf_t *buf, int64_t val);
void cbuf_write_float(cbuf_t *buf, float val);
void cbuf_write_double(cbuf_t *buf, double val);
void cbuf_write_string(cbuf_t *buf, const char * val);

void cbuf_read(cbuf_t *buf, void *data, int len);
char cbuf_read_bool(cbuf_t *buf);
uint8_t cbuf_read_byte(cbuf_t *buf);
uint16_t cbuf_read_short(cbuf_t *buf);
int32_t cbuf_read_int(cbuf_t *buf);
int64_t cbuf_read_int64(cbuf_t *buf);
float cbuf_read_float(cbuf_t *buf);
double cbuf_read_double(cbuf_t *buf);

void cbuf_clear(cbuf_t *buf);
void cbuf_seek(cbuf_t *buf, int offset);
char cbuf_bs(cbuf_t *buf);
int cbuf_data_count(cbuf_t *buf);
char *cbuf_data_ptr(cbuf_t *buf);
int cbuf_skip(cbuf_t *buf, int n);

#endif /* CBUF_H_ */
