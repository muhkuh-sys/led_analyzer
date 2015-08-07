#ifndef __SLEEP_MS_H__
#define __SLEEP_MS_H__


#if defined(_WIN32)
#       define sleep_ms(ms) Sleep(ms)
#else
#       include <unistd.h>
#       define sleep_ms(ms) usleep(1000*ms)
#endif


#endif  /* __SLEEP_MS_H__ */

