#ifndef __MY_BASE_SHM_CLASS__H__
#define __MY_BASE_SHM_CLASS__H__
#include <errno.h>
#include <string.h>

class base_shm
{
public:
	base_shm(){};
	~base_shm(){};

	virtual int create() = 0;
	virtual int open() = 0;
	virtual int close() = 0;
	virtual int destroy() = 0;

	inline char *get_err_str() { return strerror(errno);};
	void *get_shm_ptr(){ return m_ptr; };

	void *m_ptr;
};

#endif
