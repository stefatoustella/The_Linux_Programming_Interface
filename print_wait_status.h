#ifndef PRINT_WAIT_STATUS_H
#define PRINT_WAIT_STATUS_H

/* print_wait_status.h
 * Declaration for printWaitStatus() which examines a wait(2) status
 * value using the W* macros and prints a human-readable message.
 */

#ifdef __cplusplus
extern "C"
{
#endif

    /* Examine a wait() status using the W* macros and print a message.
     * 'msg' may be NULL. 'status' is the value returned in the status
     * parameter from wait()/waitpid().
     */
    void printWaitStatus(const char *msg, int status);

#ifdef __cplusplus
}
#endif

#endif /* PRINT_WAIT_STATUS_H */