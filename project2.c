
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
/******************************************************************************
 pthread_sleep takes an integer number of seconds to pause the current thread
 original by Yingwu Zhu
 updated by Muhammed Nufail Farooqi
 updated by Fahrican Kosar
 *****************************************************************************/


int pthread_sleep(int seconds);
int commentor_sleep(double seconds, int index);

typedef struct Commentor {
    pthread_t id;
    pthread_cond_t p_cond;
    pthread_mutex_t p_lock;
    int decided;
    int end;
}Commentor;

struct Commentor commentors[1024];

struct timeval te;

long long start_milliseconds;

int thread_count = 0;
double p = 0.6;
double b = 0.5;
int numOfCommentors = 12;
int t = 5;
int q = 4;

int finish = 0;
int event = 0;

typedef struct Queue {
    int** elements;
    int size;
    int front;
    int rear;
    int capacity;
}Queue;

Queue* tvQueue;
pthread_mutex_t queue_lock;
pthread_mutex_t event_lock;
pthread_mutex_t event_lock2;

int questionPresent = 0;

pthread_t mod_id;
pthread_t event_observer_id;

int end = 0;

int mod_talk_permission = 0;

int current_index = -1;

Queue* createQueue(int size) {
    Queue* Q;
    Q = (Queue*)malloc(sizeof(Queue));
    Q->elements = malloc(sizeof(int) * size + 2);
    Q->capacity = size;
    Q->elements[Q->capacity];
    Q->size = 0;
    Q->front = 0;
    Q->rear = -1;
    return Q;
}

int* pop(Queue* q)
{
    int* c;
    if (q->size == 0) {
        printf("queue is empty\n");
        return NULL;
    }
    else {
        c = q->elements[q->front];
        q->size--;
        q->front++;
        if (q->front == q->capacity) q->front = 0;
    }

    return c;
}

int* front(Queue* q) {
    if (q->size == 0) {
        printf("Queue is empty\n");
        exit(0);
    }
    return q->elements[q->front];
}

void push(Queue* q, int* p) {
    if (q->size == q->capacity) {
        printf("Queue is full\n");
    }
    else {
        q->size++;
        q->rear = q->rear + 1;
        if (q->rear == q->capacity) {
            q->rear = 0;
        }
        q->elements[q->rear] = p;
    }
    return;
}

////////////////////////////////////////////////////////////////

long long getTime() {
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // calculate milliseconds
    milliseconds = milliseconds - start_milliseconds;
    return milliseconds;
}

int check() {
    int flag = 0;
    for (int i = 0; i < numOfCommentors; i++) {
        flag = flag + commentors[i].decided;
    }
    if (flag == numOfCommentors) {
        return 1;
    }
    return 0;
}

int cend() {
    int flag = 0;
    for (int i = 0; i < numOfCommentors; i++) {
        flag = flag + commentors[i].end;
    }
    if (flag == numOfCommentors) {
        return 1;
    }
    return 0;
}

int mc;
void *moderator(void* vargp) {
    for (int w = 0; w < q; w++) {
        mc = w;
        if (w > 0) {
            while (cend() == 0) {
            }
            for (int i = 0; i < numOfCommentors; i++) {
                commentors[i].end = 0;
                commentors[i].decided = 0;
            }
        }
        if (!questionPresent) {

            for (int i = 0; i < numOfCommentors; i++) {
                pthread_mutex_lock((&commentors[i].p_lock));
            }

            while (event == 1) {
            }

            long long milli = getTime();
            printf("[%lld:%lld.%lld] Moderator asks question %d\n", milli / 60000, (milli / 1000) % 60, milli % 1000, w + 1);
            questionPresent = 1;
        }

        while (check() == 0) {
        }
        end = 0;

        while (tvQueue->size != 0) {
            while (mod_talk_permission != 0) {
            }

            while (pthread_mutex_trylock(&event_lock) != 0) {
            }
            pthread_mutex_unlock(&event_lock);

            int com = pop(tvQueue);
            pthread_mutex_unlock(&commentors[com].p_lock);
            mod_talk_permission = 1;
        }
        while (mod_talk_permission != 0) {
        }
        end = 1;
        for (int i = 0; i < numOfCommentors; i++) {
            pthread_mutex_unlock((&commentors[i].p_lock));
        }
        questionPresent = 0;
    }
    finish = 1;
    return NULL;
}


void *commentor(void* vargp) {
    pthread_t k = pthread_self();
    int index = 0;
    for (int i = 0; i < numOfCommentors; i++) {
        if (k == commentors[i].id) {
            index = i;
        }
    }



    for (int w = 0; w < q; w++) {

        while (w != mc) {
        }
        while (questionPresent == 0) {
        }


        long long milli = getTime();
        int r = rand() % 100;
        if (p * 100 >= r) {
            while (pthread_mutex_trylock(&queue_lock) != 0) {
            }
            printf("[%lld:%lld.%lld] Commentator #%d generates answer, position in queue: %d\n", milli / 60000, (milli / 1000) % 60, milli % 1000, index, tvQueue->size);
            push(tvQueue, index);
            pthread_mutex_unlock(&queue_lock);
        }
        commentors[index].decided = 1;

        while (pthread_mutex_trylock((&commentors[index].p_lock)) != 0) {
        }

        pthread_mutex_unlock(&commentors[index].p_lock);

        while (pthread_mutex_trylock(&event_lock) != 0) {
        }
        pthread_mutex_unlock(&event_lock);

        if (end != 1) {
            float ff = ((float)rand() / (float)(RAND_MAX)) * (t-1);
            ff++;
            ff = ff * 1000;
            int g = ff;
            ff = (float)g / 1000.0;
            double tc = ff;

            milli = getTime();
            current_index = index;
            printf("[%lld:%lld.%lld] Commentator #%d's turn to speak for %f seconds\n", milli / 60000, (milli / 1000) % 60, milli % 1000, index, tc);
            commentor_sleep(tc, index);
            if (event == 0) {
                milli = getTime();
                printf("[%lld:%lld.%lld] Commentator #%d finished speaking\n", milli / 60000, (milli / 1000) % 60, milli % 1000, index);
            }
        }
        while (pthread_mutex_trylock(&event_lock2) != 0) {
        }
        current_index = -1;
        mod_talk_permission = 0;
        commentors[index].end = 1;
        pthread_mutex_unlock(&event_lock2);
    }
    return NULL;
}


void *observer(void* vargp) {
    while (finish != 1) {
        if (event == 1) {
            while (pthread_mutex_trylock(&event_lock) != 0) {
            }
            long long milli = getTime();
            printf("[%lld:%lld.%lld] Breaking news!\n", milli / 60000, (milli / 1000) % 60, milli % 1000);
            
            if (current_index != -1) {
                while (pthread_mutex_trylock(&event_lock2) != 0) {
                }
                milli = getTime();
                pthread_cond_signal(&commentors[current_index].p_cond);
                printf("[%lld:%lld.%lld] Commentator #%d is cut short due to a breaking news\n", milli / 60000, (milli / 1000) % 60, milli % 1000, current_index);
                pthread_mutex_unlock(&event_lock2);
            }
            pthread_sleep(5);
            milli = getTime();
            printf("[%lld:%lld.%lld] Breaking news ends\n", milli / 60000, (milli / 1000) % 60, milli % 1000);
            event = 0;
            pthread_mutex_unlock(&event_lock);
            
        }
    }
    return NULL;
}

int pthread_sleep(int seconds) {
    pthread_mutex_t mutex;
    pthread_cond_t conditionvar;
    struct timespec timetoexpire;
    if (pthread_mutex_init(&mutex, NULL))
    {
        return -1;
    }
    if (pthread_cond_init(&conditionvar, NULL))
    {
        return -1;
    }
    struct timeval tp;
    //When to expire is an absolute time, so get the current time and add //it to our delay time
    gettimeofday(&tp, NULL);
    timetoexpire.tv_sec = tp.tv_sec + seconds; timetoexpire.tv_nsec = tp.tv_usec * 1000;

    pthread_mutex_lock(&mutex);
    int res = pthread_cond_timedwait(&conditionvar, &mutex, &timetoexpire);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&conditionvar);

    //Upon successful completion, a value of zero shall be returned
    return res;

}

int commentor_sleep(double seconds, int index) {
    pthread_mutex_t mutex;
    struct timespec timetoexpire;
    if (pthread_mutex_init(&mutex, NULL))
    {
        return -1;
    }
    if (pthread_cond_init(&commentors[index].p_cond, NULL))
    {
        return -1;
    }

    struct timeval tp;
    // When to expire is an absolute time, so get the current time and add
    // it to our delay time
    gettimeofday(&tp, NULL);
    long new_nsec = tp.tv_usec * 1000 + (seconds - (long)seconds) * 1e9;
    timetoexpire.tv_sec = tp.tv_sec + (long)seconds + (new_nsec / (long)1e9);
    timetoexpire.tv_nsec = new_nsec % (long)1e9;

    pthread_mutex_lock(&mutex);
    int res = pthread_cond_timedwait(&commentors[index].p_cond, &mutex, &timetoexpire);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&commentors[index].p_cond);

    //Upon successful completion, a value of zero shall be returned
    return res;
}

void initValues(const char* argv[], int i) {
    if (strcmp(argv[i], "-n") == 0) {
        if (argv[i + 1] != NULL) {
            numOfCommentors = atoi(argv[i + 1]);
        }
    }
    if (strcmp(argv[i], "-q") == 0) {
        if (argv[i + 1] != NULL) {
            q = atoi(argv[i + 1]);
        }
    }
    if (strcmp(argv[i], "-p") == 0) {
        if (argv[i + 1] != NULL) {
            p = atof(argv[i + 1]);
        }
    }
    if (strcmp(argv[i], "-t") == 0) {
        if (argv[i + 1] != NULL) {
            t = atoi(argv[i + 1]);
        }
    }
    if (strcmp(argv[i], "-b") == 0) {
        if (argv[i + 1] != NULL) {
            b = atof(argv[i + 1]);
        }
    }
}


int main(int argc, char const* argv[]) {
    gettimeofday(&te, NULL); // get current time
    start_milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // calculate milliseconds

    for (int i = 0; i < argc; i++) {
        if (i > 0) {
            initValues(argv, i);
        }
    }
    srand(time(NULL));

    tvQueue = createQueue(numOfCommentors * q * 2);

    for (int i = 0; i < numOfCommentors; i++) {
        pthread_create(&commentors[thread_count++].id, NULL, commentor, NULL);
    }

    pthread_create(&event_observer_id, NULL, observer, NULL);
    pthread_create(&mod_id, NULL, moderator, NULL);

    while (finish != 1) {
        pthread_sleep(1);
        if (event == 0) {
            int r = rand() % 100;
            if (b * 100 >= r) {
                event = 1;
            }
        }
    }

    for (int i = 0; i < thread_count; ++i) {
        pthread_join(commentors[i].id, NULL);
    }

    pthread_join(mod_id, NULL);
    pthread_join(event_observer_id, NULL);
    return 0;
}