/* Prevent double inclusion */
#ifndef BECOME_DAEMON_H
#define BECOME_DAEMON_H

/* Bit-mask values for 'flags' argument of becomeDaemon() */
#define BD_NO_CHDIR (1 << 0)          /* Don't chdir("/") */
#define BD_NO_CLOSE_FILES (1 << 1)    /* Don't close all open files */
#define BD_NO_REOPEN_STD_FDS (1 << 2) /* Don't reopen stdin, stdout, stderr to /dev/null */
#define BD_NO_UMASK0 (1 << 3)         /* Don't do a umask(0) */
#define BD_MAX_CLOSE 8192             /* Maximum fds to close if sysconf indeterminate */

/* Become a well-behaved daemon.
 * flags: bitmask controlling optional behavior (see BD_* above).
 * Returns 0 on success, -1 on error (errno is set on failure).
 */
int becomeDaemon(int flags);

#endif /* BECOME_DAEMON_H */