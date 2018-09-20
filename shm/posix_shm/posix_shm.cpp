#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */

#include <sys/stat.h>        /* For mode constants */
#include <sys/mman.h>
#include <sys/types.h>


#include <posix_shm.h>


#define DEFAULT_NAME "/test"
#define DEFAULT_SIZE 1024
#define DEFAULT_MODE 0666

posix_shm::posix_shm()
{
	strcpy(m_name, DEFAULT_NAME);
	m_size = DEFAULT_SIZE;
	m_mode = DEFAULT_MODE;
	m_shmfd = -1;
}

posix_shm::posix_shm(const char *name)
{
	strcpy(m_name, name);
	m_size = DEFAULT_SIZE;
	m_mode = DEFAULT_MODE;
	m_shmfd = -1;
}

posix_shm::posix_shm(const char *name, size_t size)
{
	strcpy(m_name, name);
	m_size = size;
	m_mode = DEFAULT_MODE;
	m_shmfd = -1;
}

posix_shm::posix_shm(const char *name, size_t size, mode_t mode)
{
	strcpy(m_name, name);
	m_size = size;
	m_mode = mode;
	m_shmfd = -1;
}

posix_shm::~posix_shm()
{

}

int posix_shm::create()
{
	int fd, rc;
	void *p;

	fd = shm_open(m_name, O_CREAT | O_EXCL | O_RDWR, m_mode);
	if (-1 == fd)
		goto err;

	rc = ftruncate(fd, m_size);
	if(-1 == rc)
		goto err;


	p = mmap(NULL, m_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(MAP_FAILED == p)
		goto err;

	m_ptr = p;

	return 0;
err:
	return -1;
}

int posix_shm::open()
{
	void *p;
	int fd, rc;
	struct stat buf;

	fd = shm_open(m_name, O_RDWR, 0);
	if (-1 == fd)
		goto err;

	rc = fstat(fd, &buf);
	if (-1 == rc)
		goto err;

	m_size = buf.st_size;

	p = mmap(NULL, m_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(MAP_FAILED == p)
		goto err;

	m_ptr = p;

	return 0;
err:
	return -1;
}

int posix_shm::close()
{
	return m_ptr ? munmap(m_ptr, m_size) : -1;
}

int posix_shm::destroy()
{
	return  shm_unlink(m_name);
}
