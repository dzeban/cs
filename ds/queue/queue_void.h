struct queue {
	struct item *head;
	struct item *tail;
};

struct item {
	void *p;
	struct item *next;
};

struct queue *queue_init();
void queue_free(struct queue *q);
// void queue_print(struct queue *q);
int enq(struct queue *q, void *p);
int deq(struct queue *q, void **pp);
