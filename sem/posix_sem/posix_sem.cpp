#include <stdio.h>
#include <string.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#include <posix_sem.h>


#define DEFAULT_NAME "/test"
#define DEFAULT_VALUE 1
#define DEFAULT_MODE 0666

posix_sem::posix_sem()
{
	strcpy(m_name, DEFAULT_NAME);
	m_value = DEFAULT_VALUE;
	m_mode = DEFAULT_MODE;
	m_sem = SEM_FAILED;
}

posix_sem::posix_sem(const char *name)
{
	strcpy(m_name, name);
	m_value = DEFAULT_VALUE;
	m_mode = DEFAULT_MODE;
	m_sem = SEM_FAILED;
}

posix_sem::posix_sem(const char *name, int value)
{
	strcpy(m_name, name);
	m_value = value;
	m_mode = DEFAULT_MODE;
	m_sem = SEM_FAILED;
}

posix_sem::posix_sem(const char *name, int value, mode_t mode)
{
	strcpy(m_name, name);
	m_value = value;
	m_mode = mode;
	m_sem = SEM_FAILED;
}

posix_sem::~posix_sem()
{

}

int posix_sem::create()
{
	sem_t *sem;
	sem = sem_open(m_name, O_CREAT | O_EXCL ,m_mode, m_value);
	if (SEM_FAILED == sem)
		return -1;

	m_sem = sem;

	return 0;
}

int posix_sem::open()
{
	sem_t *sem;

	sem = sem_open(m_name, 0);
	if (SEM_FAILED == sem)
		return -1;

	m_sem = sem;

	return 0;
}

int posix_sem::lock()
{
	return m_sem == SEM_FAILED ? -1 : sem_wait(m_sem);
}

int posix_sem::unlock()
{
	return m_sem == SEM_FAILED ? -1 : sem_post(m_sem);
}

int posix_sem::close()
{
	return m_sem == SEM_FAILED ? -1 : sem_close(m_sem);
}

int posix_sem::destroy()
{
	return  sem_unlink(m_name);
}
