#ifndef __MY_POSIX_SEM_CLASS__
#define __MY_POSIX_SEM_CLASS__
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <base_sem.h>

class posix_sem : public base_sem
{
public:
	posix_sem();
	posix_sem(const char *name);
	posix_sem(const char *name, int value);
	posix_sem(const char *name, int value, mode_t mode);
	~posix_sem();

	int create();
	int open();
	int lock();
	int unlock();
	int close();
	int destroy();

private:

	char m_name[128];
	mode_t m_mode;
	int m_value;

	sem_t *m_sem;

};
#endif
