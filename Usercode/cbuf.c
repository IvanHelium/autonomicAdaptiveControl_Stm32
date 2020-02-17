#include "cbuf.h"
#include <string.h>

void cbuf_init(cbuf_t *buf, char *data_ptr, int size)
{
	buf->size = size;
	buf->cnt = 0;
	buf->data = data_ptr;
	buf->rdptr = data_ptr;
	buf->wrptr = data_ptr;
}

void cbuf_write(cbuf_t *buf, const void *data, int len)
{
	int i;
	char *_data = (char  *)data;
	for (i = 0; i < len; ++i)
	{
		*(buf->wrptr)++ = _data[i];
		if (buf->wrptr == buf->data + buf->size) {
			buf->wrptr = buf->data;
		}
		buf->cnt++;
	}
}

void cbuf_write_byte(cbuf_t *buf, uint8_t val)
{
	cbuf_write(buf, &val, 1);
}

void cbuf_write_bool(cbuf_t *buf, char val)
{
	cbuf_write(buf, &val, 1);
}

void cbuf_write_short(cbuf_t *buf, uint16_t val)
{
	cbuf_write(buf, &val, 2);
}

void cbuf_write_int(cbuf_t *buf, int32_t val)
{
	cbuf_write(buf, &val, 4);
}

void cbuf_write_int64(cbuf_t *buf, int64_t val)
{
	cbuf_write(buf, &val, 8);
}

void cbuf_write_float(cbuf_t *buf, float val)
{
	cbuf_write(buf, &val, 4);
}

void cbuf_write_double(cbuf_t *buf, double val)
{
	cbuf_write(buf, &val, 8);
}

void cbuf_write_string(cbuf_t *buf, const char * val)
{
	if (!val)
	{
		char z=0;
		cbuf_write(buf, &z, sizeof(z));
	}
	else
	{
		cbuf_write(buf, val, (int)(strlen(val)+1));
	}
}

void cbuf_read(cbuf_t *buf, void *data, int len)
{
	int i;
	char *_data = (char *)data;
	for (i = 0; i < len; ++i)
	{
		_data[i] = *(buf->rdptr)++;
		if (buf->rdptr == buf->data + buf->size) {
			buf->rdptr = buf->data;
		}
		buf->cnt--;
	}
}

char cbuf_read_bool(cbuf_t *buf)
{
	char val = 0;
	cbuf_read(buf, &val, 1);
	return val;
}

uint8_t cbuf_read_byte(cbuf_t *buf)
{
	unsigned char val = 0;
	cbuf_read(buf, &val, 1);
	return val;
}

uint16_t cbuf_read_short(cbuf_t *buf)
{
	unsigned short val = 0;
	cbuf_read(buf, &val, 2);
	return val;
}

int32_t cbuf_read_int(cbuf_t *buf)
{
	int val = 0;
	cbuf_read(buf, &val, 4);
	return val;
}

int64_t cbuf_read_int64(cbuf_t *buf)
{
	unsigned long long val = 0;
	cbuf_read(buf, &val, 8);
	return val;
}

float cbuf_read_float(cbuf_t *buf)
{
	float val = 0;
	cbuf_read(buf, &val, 4);
	return val;
}

double cbuf_read_double(cbuf_t *buf)
{
	double val = 0;
	cbuf_read(buf, &val, 8);
	return val;
}

void cbuf_clear(cbuf_t *buf) {
	buf->cnt = 0;
	buf->rdptr = buf->data;
	buf->wrptr = buf->data;
}

void cbuf_seek(cbuf_t *buf, int offset) {
	int n = buf->rdptr - buf->data - offset;
	buf->cnt += n;
	buf->rdptr = buf->data + offset;
}

char cbuf_bs(cbuf_t *buf) {
	char data = *buf->wrptr--;
	buf->cnt--;
	if (buf->wrptr == buf->data - 1) {
		buf->wrptr = buf->data + buf->size - 1;
	}
	return data;
}

int cbuf_data_count(cbuf_t *buf) {
	return buf->cnt;
}

char *cbuf_data_ptr(cbuf_t *buf) {
	return buf->rdptr;
}

int cbuf_skip(cbuf_t *buf, int n)
{
	int k = buf->data + buf->size - buf->rdptr;
	if (n > k)
	{
		buf->cnt -= k;
		buf->rdptr = buf->data;
		return n-k;
	}
	else
	{
		buf->cnt -= n;
		buf->rdptr += n;
		return 0;
	}
}
