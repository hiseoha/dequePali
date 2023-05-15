#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_QUEUE_SIZE 100
typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} DequeType;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(DequeType* q)
{
	q->front = q->rear = 0;
}

int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}

int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void deque_print(DequeType* q)
{
	printf("DEQUE(front=%d rear=%d)= ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("Deque Full");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("Deque Empty");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element get_front(DequeType* q)
{
	if (is_empty(q))
		error("Deque Empty");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("Deque Full");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("Deque Empty");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}

element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("Deque Empty");
	return q->data[q->rear];
}

int palindrome_check(char str[]) {
	bool result = true;
	DequeType q;
	init_queue(&q);

	for (int i = 0; i < strlen(str); i++) {
		if (isalpha(str[i]) != 0) {
			char c = tolower(str[i]);
			add_rear(&q, str[i]);
		}
	}

	for (int i = 0; i < strlen(str); i++) {
		char c = tolower(str[i]);
		if (c!=delete_rear(&q)) {
			return result = false;
		}
		else return result = true;
	}
}

int main(void)
{
	DequeType q;
	init_queue(&q);
	char str[MAX_QUEUE_SIZE];
	
	while (1) {
		printf("Enter a string (or input 'exit'): ");
		gets(str);

		if (!strcmp(str, "exit")) {
			printf("Program exit\n");
			break;
		}
		else {
			if (palindrome_check(str)) printf("%s is a palindrome.\n", str);
			else printf("%s is not a palindrome.\n", str);
		}
	}

	return 0;
}