#ifndef __MY_SYSTEM_SEM_CLASS__
#define __MY_SYSTEM_SEM_CLASS__

#include <sys/sem.h>
#include <base_sem.h>

class system_sem : public base_sem
{
public:
	system_sem();
	system_sem(key_t key);
	system_sem(key_t key, int numsems);
	system_sem(key_t key, int numsems, mode_t mode);
	~system_sem();

	int create();
	int open();
	int lock();
	int unlock();
	int close();
	int destroy();

private:

	key_t m_key;
	mode_t m_mode;
	int m_numsems;

	int m_semid;

};
#endif
