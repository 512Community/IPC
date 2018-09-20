#ifndef __MY_system_shm_CLASS__
#define __MY_system_shm_CLASS__

#include <sys/sem.h>
#include <base_shm.h>

class system_shm : public base_shm
{
public:
	system_shm();
	system_shm(key_t key);
	system_shm(key_t key, size_t size);
	system_shm(key_t key, size_t size, mode_t mode);
	~system_shm();

	int create();
	int open();
	int close();
	int destroy();

private:

	key_t m_key;
	mode_t m_mode;
	size_t m_size;

	int m_shmid;

};
#endif
