/* vi: set sw=4 ts=4: */
/*
   Copyright 2010, Dylan Simon

   Licensed under the GPL v2 or later, see the file LICENSE in this tarball.
*/

#ifndef BB_ANDROID_H
#define BB_ANDROID_H 1

/* for dirname, basename */
#include <libgen.h>

#if ENABLE_FEATURE_DC_LIBM
# include <math.h>
#endif

/* lutimes doesnt exists in libc */
#if ENABLE_FEATURE_TOUCH_NODEREF
# define lutimes utimes
#endif

#define killpg_busybox(P, S) kill(-(P), S)

#define setmntent fopen
#define endmntent fclose

/* defined in bionic/utmp.c */
void endutent(void);

/* defined in bionic/mktemp.c */
char *mkdtemp(char *);

/* defined in bionic/stubs.c */
char *ttyname(int);

/* SYSCALLS */
int    stime(time_t *);
int    swapon(const char *, int);
int    swapoff(const char *);
int    getsid(pid_t);

#ifndef SYS_ioprio_set
#define SYS_ioprio_set __NR_ioprio_set
#define SYS_ioprio_get __NR_ioprio_get
#endif

/* XXX These need to be obtained from kernel headers. See b/9336527 */
#define SWAP_FLAG_PREFER        0x8000
#define SWAP_FLAG_PRIO_MASK     0x7fff
#define SWAP_FLAG_PRIO_SHIFT    0
#define SWAP_FLAG_DISCARD       0x10000

/* local definition in libbb/xfuncs_printf.c */
int fdprintf(int fd, const char *format, ...);

/* local definitions in libbb/android.c */
int ttyname_r(int, char *, size_t);

char *getusershell(void);
void setusershell(void);
void endusershell(void);

struct mntent;
struct __sFILE;
int addmntent(struct __sFILE *, const struct mntent *);
struct mntent *getmntent_r(struct __sFILE *fp, struct mntent *mnt, char *buf, int buflen);
const char *hasmntopt(const struct mntent *, const char *);

#define MNTOPT_NOAUTO "noauto"

/* bionic's vfork is rather broken; for now a terrible bandaid: */
#define vfork fork

#define _SOCKLEN_T_DECLARED
typedef int socklen_t;

/* wait3 was removed in android L */
#ifdef BIONIC_L
#define wait3(status, options, rusage) wait4(-1, status, options, rusage)
#endif

#endif
