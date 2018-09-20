#ifndef __MY_POSIX_SHM_CLASS__
#define __MY_POSIX_SHM_CLASS__

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <base_shm.h>

class posix_shm : public base_shm
{
public:
	posix_shm();
	posix_shm(const char *name);
	posix_shm(const char *name, size_t size);
	posix_shm(const char *name, size_t size, mode_t mode);
	~posix_shm();

	int create();
	int open();
	int close();
	int destroy();

private:

	char m_name[128];
	mode_t m_mode;
	size_t m_size;

	int m_shmfd;

};

#endif
