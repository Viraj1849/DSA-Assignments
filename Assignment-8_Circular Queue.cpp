#include<iostream>
using namespace std;

# define size 5
class S_Mart
{
	int order_id;
	static int cust_count;
	string name;
	string order_items;
public:
	void readOrderDetails()
	{
		order_id = ++cust_count;
		cout<<"Enter the name :";
		cin>>name;
		cout<<"Enter your order :";
		cin>>order_items;
	}
	void printOrderDetails()
	{
		cout<<"Name :"<<name<<" Order: "<<order_items<<"\n";
	}
};
int S_Mart::cust_count = 0;
class Customer
{
	int rear,front;
	int count;
	S_Mart q[10];
public:
	Customer()
	{
		rear=front=-1;
		count=0;
	}
	void enqueue(S_Mart x)
	{
		if(count==size)
		{
			cout<<"Oueue is full\n";
		}
		else
		{
			rear=(rear+1)%size;
			q[rear]=x;
			count++;
		}
	}
	S_Mart dequeue()
	{
		S_Mart x;
		if(count>0) {
			front=(front+1)%size;
			x=q[front];
			count--;
			return x;
		}
		else {
			cout<<"Queue is Empty\n";
		}
	}
	void printqueue() {
		int i;
		if(count>0) {
			cout<<"********** S-Mart **********\n";
			for(i=(front+1%size); i!=rear; i=(i+1)%size)
			{
				q[i].printOrderDetails();
				cout<<"\n";
			}
			q[i].printOrderDetails();
			cout<<"\n";
		}
	}
};
int main() {
	S_Mart c1;
	Customer c2;
	int ch;
	do {
		cout<<"********** Welcome to S-Mart **********\n\n";
		cout<<"1)Place Order\n";
		cout<<"2)Process Order\n";
		cout<<"3)Print Queue\n";
		cout<<"4)Exit\n";
		cout<<"Enter your Choice:";
		cin>>ch;
		switch(ch) {
		case 1:
			c1.readOrderDetails();
			c2.enqueue(c1);
			break;
		case 2:
			c1=c2.dequeue();
			cout<<"Processed Order Detail: \n";
			c1.printOrderDetails();
			break;
		case 3:
			c2.printqueue();
			break;
		case 4:
			exit(0);
		}

	} while(ch!=5);
	return 0;
}
