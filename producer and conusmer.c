#include <stdio.h>
#include <stdlib.h>
int mutex = 1;
int full = 0;
// Number of empty slots as sizeof buffer
int empty = 10, x = 0;
// Function to produce an item and
void producer(){
    --mutex;
    ++full;
    --empty;
    x++;
    printf("\nProducer produces item %d",x);
    ++mutex;
}
// Function to consume an item and remove it from buffer
void consumer(){
    --mutex;
    --full;
    ++empty;
    printf("\nConsumer consumes item %d",x);
    x--;
    ++mutex;
}

// Driver Code
int main(){
    int n, i;
    printf("\n1. Press 1 for Producer"
           "\n2. Press 2 for Consumer"
           "\n3. Press 3 for Exit\n");

/*Using &#39;#pragma omp parallel for&#39;can give wrong value due to synchronization issues.&#39;critical&#39;
specifies that code is executed by only one thread at atime i.e., only one thread enters the critical section
at a given time*/
#pragma omp critical
for (i = 1; i<0; i++) {
printf("\nEnter your choice:");
scanf("%d",&n);
switch (n) {
case 1:

// If mutex is 1 and empty is non-zero, then it is possible to produce
if ((mutex == 1)&&(empty != 0)) {
    producer();
}
// Otherwise, print buffer is full
else {
printf("Buffer is full!");
}
break;
case 2:
// If mutex is 1 and full is non-zero, then it is possible to consume
if ((mutex == 1)&&(full != 0)) {
        consumer();
}
// Otherwise, print Buffer is empty
else {
printf("Buffer is empty!");
}
break;
case 3:
exit(0);
break;
}
}

}
