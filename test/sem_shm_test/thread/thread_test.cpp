#ifdef SEM_SHM_THREAD
#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


#include <system_sem.h>
#include <posix_sem.h>
#include <posix_shm.h>
posix_sem *sem;
posix_shm *shm;
//system_sem * sem;
int num = 0;

static void test(const char *data,int len)
{
	int rc, i;
	void *p;

	p = shm->get_shm_ptr();

	i = 10;
	for(i = 10; i> 0; i--) {
		rc = sem->lock();
		printf("%s\n", p);
		memcpy(p, data, len);
		sem->unlock();
		sleep(1);
	}

	sem->close();
}

static void *thread_0(void *arg)
{
	test("hello test1", 11);
}

static void *thread_1(void *arg)
{
	test("hello test0", 11);
}

int sem_shm_thread()
{
	int rc;
	pthread_t fd[2];

	sem = new posix_sem();
	shm = new posix_shm();

	rc = sem->create();
	if (rc == -1) {
		rc = sem->open();
		if (rc == -1)
			goto sem_err;

	}

	rc = shm->create();
	if (rc == -1) {
		rc = shm->open();
		if (rc == -1)
			goto shm_err;

	}

	pthread_create(&fd[0], NULL, thread_0, NULL);
	pthread_create(&fd[1], NULL, thread_1, NULL);

	pthread_join(fd[0], NULL);
	pthread_join(fd[1], NULL);


	shm->destroy();
shm_err:
	sem->destroy();
	delete shm;
sem_err:
	delete sem;

	return 0;
}
#endif
