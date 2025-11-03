#include <iostream>
using namespace std;

class Node
{
public :
	int requestId;
	char name[50];
	char serviceType[50];
	char contactinfo[50];
	Node *next;
	Node()
	{
		next = NULL;
	}
};

class Queue
{
	Node *front, *rear;

public:
	Queue()
	{
		front = NULL;
		rear = NULL;
	}

	void enqueue()
	{
		Node *newData = new Node();

		cout<<"\n Enter requestId: ";
		cin>>newData->requestId;
		cout<<"\n Enter name: ";
		cin>>newData->name;
		cout<<"\n Enter serviceType: ";
		cin>>newData->serviceType;
		cout<<"\n Enter contact";
		cin>>newData->contactinfo;
		if(front == NULL && rear == NULL)
		{
			front = newData;
			rear = newData;
		}
		else
		{
			rear->next = newData;
			rear = rear->next;
		}
	}

	void dequeue()
	{
		Node *temp;
		temp = front;
		front = front -> next;

		delete(temp);
	}

	void printQueue()
	{
		Node *curr;
		curr=front;

		cout<<"Queue";
		while(curr != NULL) {
			cout<<curr->requestId <<"->"<<curr-> name <<"->"<<curr->serviceType <<"->"<<curr->contactinfo<<"->";
			curr=curr->next;
		}
		cout<<"NULL";
	}
};

int main(int argc, char** argv) {
	Queue *q1 = new Queue();
	int ch;
	do {
		cout<<"Enter Details\n";
		cout<<"\t1 Enter Details";
		cout<<"\n\t2 Delete Details";
		cout<<"\n\t3 Print Details";
		cout<<"\n\t Choose: ";
		cin>>ch;
		switch(ch)
		{
		case 1 :
			cout<<"\nEnter Details";
			q1->enqueue();
			break;
		case 2 :
			cout<<"\nDelete Details";
			q1->dequeue();
			break;
		case 3 :
			cout<<"\nPrint Details";
			q1->printQueue();
			break;
		}
	} while(ch != 4);
	{
		cout << "Invalid choice. Try again.\n";
	}


	return 0;
}
