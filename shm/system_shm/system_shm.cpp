#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include <system_sem.h>


#define DEFAULT_KEY 1234
#define DEFAULT_NUM 1
#define DEFAULT_MODE 0666

#ifdef _SEM_SEMUN_UNDEFINED
union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
				    (Linux-specific) */
};
#endif

system_sem::system_sem()
{
	m_key = DEFAULT_KEY;
	m_numsems = DEFAULT_NUM;
	m_mode = DEFAULT_MODE;

	m_semid = -1;
}

system_sem::system_sem(key_t key)
{
	m_key = key;
	m_numsems = DEFAULT_NUM;
	m_mode = DEFAULT_MODE;

	m_semid = -1;
}

system_sem::system_sem(key_t key, int numsems)
{
	m_key = key;
	m_numsems = numsems;
	m_mode = DEFAULT_MODE;

	m_semid = -1;
}

system_sem::system_sem(key_t key, int numsems, mode_t mode)
{
	m_key = key;
	m_numsems = numsems;
	m_mode = mode;

	m_semid = -1;
}

system_sem::~system_sem()
{

}

int system_sem::create()
{
	int semid, rc;
	union semun arg;
	struct sembuf sembuf;

	semid = semget(m_key, m_numsems, IPC_CREAT | IPC_EXCL | m_mode);
	if(semid == -1)
		goto err;

	arg.val = 0;
	rc = semctl(semid, 0, SETVAL, arg);
	if (rc == -1)
		goto err;

	sembuf.sem_num = 0;
	sembuf.sem_op = 1;
	sembuf.sem_flg = 0;

	rc = semop(semid, &sembuf, 1);
	if (rc == -1)
		goto err;

	m_semid = semid;

	return 0;
err:
	return -1;
}

int system_sem::open()
{
	int semid, rc;
	union semun arg;
	struct semid_ds ds;
	int i;

	semid = semget(m_key, 1, m_mode);
	if(semid == -1)
		goto err;

	arg.buf = &ds;

	for (i = 0; i < 10; i++) {
		rc = semctl(semid, 0, IPC_STAT, arg);
		if (rc == -1)
			goto err;

		if(ds.sem_otime != 0)
			break;

		usleep(10 * 1000);
	}

	if (ds.sem_otime == 0)
		goto err;

	m_semid = semid;

	return 0;

err:
	return -1;
}

int system_sem::lock()
{
	struct sembuf sembuf;

	sembuf.sem_num = 0;
	sembuf.sem_op = -1;
	sembuf.sem_flg = SEM_UNDO;

	return m_semid == -1 ? -1 : semop(m_semid, &sembuf, 1);
}

int system_sem::unlock()
{
	struct sembuf sembuf;

	sembuf.sem_num = 0;
	sembuf.sem_op = 1;
	sembuf.sem_flg = SEM_UNDO;

	return m_semid == -1 ? -1 : semop(m_semid, &sembuf, 1);
}

int system_sem::close()
{
	return 0;
}

int system_sem::destroy()
{
	return semctl(m_semid, 0, IPC_RMID);
}
