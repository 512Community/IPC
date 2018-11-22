#ifndef __MY_BASE_SEM_CLASS__H__
#define __MY_BASE_SEM_CLASS__H__
#include <errno.h>
#include <string.h>

class base_sem
{
public:
	base_sem(){};
	virtual ~base_sem(){};

	virtual int create() = 0;
	virtual int open() = 0;
	virtual int lock() = 0;
	virtual int unlock() = 0;
	virtual int close() = 0;
	virtual int destroy() = 0;

	inline char *get_err_str() { return strerror(errno);};
};

#endif
