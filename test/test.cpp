#include <stdio.h>
#include <thread_test.h>


int main(int argc, const char *argv[])
{
#ifdef SEM_SHM_THREAD
	sem_shm_thread();
#endif
}

