/**
 * TODO: implementation of the multilevel feedback queue scheduling
 */
#include "../lib/kqueue.h"

#define DOWNGRADE_TIME  30
#define UPGRADE_TIME    20

/**
 *        ready queue all are Round Robin
 *     ==========================
 *            Q1 (pri) 1
 *  ->  --------------------   Qt = 2 unit
 *      --------------------    >>-------------------->> | CPU |
 *            Q2 (pri) 2                                 |     |
 *      --------------------   Qt = 4 unit >----------------> ^
 *      --------------------                                  |
 *            Q3 (pri) 3                                      |
 *      --------------------   Qt = 8 unit >-------------------
 *      --------------------
 * 
 *     ==========================
 * 
 * NOTE: if the process has exceeded the Qt of that queue and not yet finished 
 *        then: moves to below queue
 *      also then specific time as passed it cannot remain in same queue even if O/P
 *        for o/p within Qt it will remain in the queue
 * 
 *      if the process has been on the lower queue for a long time it 
 *        needs to be upgraded to the first queue after certain time
 */

struct readyQueue {
  struct __LinkListHeaders    *Q1;
  int                         priQ1;
  struct __LinkListHeaders    *Q2;
  int                         priQ2;
  struct __LinkListHeaders    *Q3;
  int                         priQ3;
};

int 
main(int argc, char const *argv[])
{
  return 0;
}
