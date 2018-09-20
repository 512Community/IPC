#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#include <system_shm.h>


#define DEFAULT_KEY 1234
#define DEFAULT_SIZE 1024
#define DEFAULT_MODE 0666

system_shm::system_shm()
{
	m_key = DEFAULT_KEY;
	m_size = DEFAULT_SIZE;
	m_mode = DEFAULT_MODE;

	m_shmid = -1;
}

system_shm::system_shm(key_t key)
{
	m_key = key;
	m_size = DEFAULT_SIZE;
	m_mode = DEFAULT_MODE;

	m_shmid = -1;
}

system_shm::system_shm(key_t key, size_t size)
{
	m_key = key;
	m_size = size;
	m_mode = DEFAULT_MODE;

	m_shmid = -1;
}

system_shm::system_shm(key_t key, size_t size, mode_t mode)
{
	m_key = key;
	m_size = size;
	m_mode = mode;

	m_shmid = -1;
}

system_shm::~system_shm()
{

}

int system_shm::create()
{
	int shmid, rc;
	struct shmid_ds buf;

begin:
	shmid = shmget(m_key, m_size, IPC_CREAT | IPC_EXCL | m_mode);
	if (shmid == -1 && errno != EEXIST)
		goto err;

	if(errno == EEXIST) {
		errno = 0;
		shmid = shmget(m_key, 0, 0);
		if (shmid == -1)
			goto err;


		rc = shmctl(shmid, IPC_STAT, &buf);
		if (rc == -1)
			goto err;

		if (buf.shm_nattch == 0) {
			rc = shmctl(shmid, IPC_RMID, 0);
			if (rc == -1)
				goto err;

			goto begin;
		}
	} else {
		goto err;
	}


	m_ptr = shmat(shmid, NULL, 0);
	if (m_ptr == (void *)-1)
		goto err;
	
	m_shmid = shmid;
	 
	return 0;
err:
	return -1;
}

int system_shm::open()
{
	int shmid;

	shmid = shmget(m_key, 0, 0);
	if (shmid == -1)
		goto err;

	m_ptr = shmat(shmid, NULL, 0);
	if (m_ptr == (void *)-1)
		goto err;

	m_shmid = shmid;

	return 0;

err:
	return -1;
}

int system_shm::close()
{
	return 0;
}

int system_shm::destroy()
{
	return shmctl(m_shmid, IPC_RMID, 0);
}
