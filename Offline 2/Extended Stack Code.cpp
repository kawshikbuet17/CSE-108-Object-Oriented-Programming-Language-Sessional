/*
KAWSHIK KUMAR PAUL
STUDENT ID: 1705043
BUET CSE'17
*/

# include <iostream>
#include<cstdlib>
using namespace std;
#define sizeOfStackArray 3

class Stack{
    int *stck;
    int tos;
    int maxSize;
public:
    Stack();
    Stack(int size);
    void push(int num);
    void push(int a[], int n);
    void push(Stack);
    int pop();
    bool isEmpty();
    int Top();
    int getSize();
    double similarity(Stack sts);
    ~Stack();
};


Stack::Stack(){
    stck = new int[10];
    tos = 0;
    maxSize = 10;
}

Stack::Stack(int size){
    stck = new int[size];
    tos = 0;
    maxSize = size;
}

bool Stack::isEmpty(){
    return (!tos);
}

int Stack::getSize()
{
    return tos;
}

int Stack::Top(){
    int val = -1;

    if (tos == 0){
        cout << "Stack is empty" << endl;
    }
    else{

        val = stck[tos-1];
    }
    return val;
}

void Stack::push(int num){
    if (tos == maxSize)
    {
        cout << "Stack is increased" << endl;
        stck = (int*)realloc(stck, (maxSize+1)*sizeof(int));
    }
    stck[tos++] = num;
}

void Stack::push(int a[], int n)
{
    if (tos+n >= maxSize)
            {
                cout << "Stack is increased" << endl;
                stck = (int*) realloc(stck, (tos+n)*sizeof(int));
                maxSize = tos + n;
            }
    for(int i=0; i<n; i++)
    {
        push(a[i]);
    }
}

void Stack::push(Stack sts)
{
    if (tos+sts.tos >= maxSize)
            {
                cout << "Stack is increased" << endl;
                stck = (int*) realloc(stck, (tos+sts.tos)*sizeof(int));
                maxSize = tos+sts.tos;
            }
        while(!sts.isEmpty())
            push(sts.pop());
}

int Stack::pop(){
    int value = -1;
    if (tos == 0){
        cout << "Stack is empty" << endl;
    }
    else{
        value = stck[--tos];
        stck = (int*) realloc(stck, (maxSize-1)*sizeof(int));
    }
    return value;
}



Stack::~Stack(){
    delete[] stck;
}


double Stack::similarity(Stack sts)
{
    double matched=0, avg=(tos+sts.tos)/2.0;
    Stack temp = sts;
    int t1=tos;
    int t11=tos;
    int t2 = sts.tos;
    int t22 =sts.tos;

    if(tos<=sts.tos)
    {
        while(t1--)
        {
            if(stck[--t11]==temp.pop())
            {
                matched++;
            }
        }
    }
    else
    {
        while(!temp.isEmpty())
        {
            if(stck[--t1]==temp.pop())
            {
                matched++;
            }
        }
    }
    cout<<" Matched = "<<matched<<endl;
    cout<<" Avg Size = "<<avg<<endl;
    return matched/avg;
}

int main(){
    Stack mainStack;
    int c;
    while(1)
    {
        cout<<"1:	Push an element"<<endl;
        cout<<"2:	Push an array"<<endl;
        cout<<"3:	Push a stack"<<endl;
        cout<<"4:	Pop"<<endl;
        cout<<"5:	Top"<<endl;
        cout<<"6:	Size"<<endl;
        cout<<"7:	Similarity"<<endl;
        cout<<"8:	Exit"<<endl;
        cin>>c;
        if(c==1)
        {
            int a;
            cout<<"Input a number: ";
            cin>>a;
            mainStack.push(a);
            cout<<endl;
        }

        if(c==2)
        {
            int size;
            cout<<"input size of array ";
            cin>>size;
            int A[size];
            cout<<endl;
            cout<<"input the array: ";
            for(int i=0; i<size; i++)
            {
                cin>>A[i];
            }
            mainStack.push(A, size);
            cout<<endl;
        }

        if(c==3)
        {
            int size;
            cout<<"input size of stack: ";
            cin>>size;
            Stack tempStack(size);
            cout<<endl;
            cout<<"input the elements: ";
            for(int i=0; i<size; i++)
            {
                int a;
                cin>>a;
                tempStack.push(a);
            }
            mainStack.push(tempStack);
            cout<<endl;
        }
        if(c==4)
        {
            cout<<"Popped: "<<mainStack.pop()<<endl;
        }
        if(c==5)
        {
            cout<<"Top of mainStack is: "<<mainStack.Top()<<endl;
        }
        if(c==6)
        {
            cout<<"Size of mainStack is: "<<mainStack.getSize()<<endl;
        }
        if(c==7)
        {
            int size;
            cout<<"input size of stack: ";
            cin>>size;
            Stack tempStack(size);
            cout<<endl;
            cout<<"input the elements: ";
            for(int i=0; i<size; i++)
            {
                int a;
                cin>>a;
                tempStack.push(a);
            }
            cout<<"Similarity: "<<mainStack.similarity(tempStack)<<endl;
        }
        if(c==8)
        {
            cout<<"Overall popping mainStack: "<<endl;
            while(!mainStack.isEmpty())
                cout<<mainStack.pop()<<" ";
            cout<<endl;
            cout<<"Program ended..."<<endl;
            break;
        }
    }
    return 0;
}
