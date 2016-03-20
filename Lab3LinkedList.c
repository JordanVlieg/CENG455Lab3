
#include <stdio.h>
#include <stdlib.h>

typedef struct TaskStruct* TaskReference;

typedef struct TaskStruct {
	int tid;
	int deadline;
	int task_type;
	int creation_time;
	int priority;
	TaskReference next;
	TaskReference prev;
} Task;

typedef struct QueueStruct{
	TaskReference head;
	TaskReference  tail;
	int size;
} Queue;
typedef Queue* QueueReference;

QueueReference initializeQueue()
{
	QueueReference newQueue = (QueueReference)malloc(sizeof(Queue));
	newQueue->head = NULL;
	newQueue->tail = NULL;
	newQueue->size = 0;
	return newQueue;
}

TaskReference initializeTaskNode(int tid, int deadline, int task_type, int creation_time)
{
	TaskReference newTask = (TaskReference)malloc(sizeof(Task));
	if (newTask == NULL)
	{
		printf("List Node malloc() failed\n");
		return NULL;
	}
	else
	{
		newTask->tid = tid;
		newTask->deadline = deadline;
		newTask->task_type = task_type;
		newTask->creation_time = creation_time;
		newTask->priority = deadline + creation_time;
		newTask->next = NULL;
		newTask->prev = NULL;
		return newTask;
	}
}

//TaskReference findNode(QueueReference theQueue, TaskReference theTask);

void insertTask(QueueReference theQueue, TaskReference newNode)
{
	/* List is Empty */
	if(theQueue->head == NULL)
	{
		theQueue->head = newNode;
		newNode->prev = NULL;
	}
	/* List is not empty */
	else
	{
		TaskReference tempNode = theQueue->head;
		while(tempNode->priority < newNode->priority)
		{
			if(tempNode->next == NULL)
			{
				break;
			}
			tempNode = tempNode->next;
		}
		/* Insert at tail */
		if(tempNode->priority < newNode->priority)
		{
			tempNode->next = newNode;
			newNode->prev = tempNode;
			theQueue->tail = newNode;
		}
		else
		{
			newNode->next = tempNode;
			newNode->prev = tempNode->prev;
			/* Insert at head */
			if(tempNode == theQueue->head)
			{
				theQueue->head = newNode;
			}
			/* Regular insert */
			else
			{
				tempNode->prev->next = newNode;
			}
			tempNode->prev = newNode;
		}
	}
	theQueue->size++;
}

TaskReference viewHead(QueueReference theQueue)
{
	TaskReference returnNode = theQueue->head;
	return returnNode;
}

TaskReference removeTaskFromHead(QueueReference theQueue)
{
	TaskReference returnNode = theQueue->head;
	theQueue->head = returnNode->next;
	theQueue->size--;
	return returnNode;
}

TaskReference removeTaskById(QueueReference theQueue, int theTaskID)
{
	TaskReference tempNode = theQueue->head;
	if(tempNode == NULL)
	{
		return NULL;
	}
	while(tempNode->tid != theTaskID)
	{
		if(tempNode->next == NULL)
		{
			return NULL;
		}
		tempNode = tempNode->next;
	}

	if(tempNode->prev == NULL)
	{
		return removeTaskFromHead(theQueue);
	}
	else if(tempNode->next == NULL)
	{
		theQueue->tail = tempNode->prev;
		tempNode->prev->next = NULL;
	}
	else
	{
		tempNode->prev->next = tempNode->next;
		tempNode->next->prev = tempNode->prev;
	}
	return tempNode;
}

int main(void)
{
	QueueReference aQueue = initializeQueue();
	TaskReference x = initializeTaskNode(1, 10, 1, 5);
	printf("Reached This\n");
	insertTask(aQueue, x);
	printf("Reached This Too\n");
	x = initializeTaskNode(2, 3, 1, 3);
	insertTask(aQueue, x);
	x = initializeTaskNode(3, 17, 1, 20);
	insertTask(aQueue, x);
	x = initializeTaskNode(4, 5, 1, 3);
	insertTask(aQueue, x);

	TaskReference tempNode = aQueue->head;
	while(tempNode != NULL)
	{
		printf("Node: %d\n", tempNode->tid);
		tempNode = tempNode->next;
		fflush(stdout);
	}
	printf("Done\n");

	return 1;
}