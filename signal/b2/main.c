#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_Handler1(int signo) {
  if (signo == SIGUSR1) {
    printf("SIGUSR1 signal.\n");
  }
}
void signal_Handler2(int signo) {
  if (signo == SIGUSR2) {
    printf("SIGUSR2 signal.\n");
  }
}

int main(void) {
    signal(SIGUSR1, signal_Handler1);
    signal(SIGUSR2, signal_Handler2);
    
    sigset_t new_set, old_set;
    sigemptyset( &new_set);
    sigemptyset( &old_set);
    
    sigaddset( &new_set, SIGINT );
    sigprocmask( SIG_BLOCK, &new_set, &old_set);
    sigprocmask( SIG_SETMASK, &old_set, NULL );
    //sigismember(&new_set, SIGINT);
    if (sigismember (&new_set, SIGINT) == 1) { //đang bị block
        sigprocmask( SIG_UNBLOCK, &new_set, &old_set);
    } else {
        sigprocmask( SIG_BLOCK, &new_set, &old_set);
    }

    while (1);

   return 0;
   }



