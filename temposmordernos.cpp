#include <cstdio>
#include <iostream>

using namespace std;

struct Link{
    int identifier;
    int time;
    Link *next;

    Link(int elem,int times,Link *nextval=NULL){
        identifier = elem;
        time = times;
        next = nextval;
    }

    Link(Link *nextval=NULL){
        next = nextval;
    }
};

struct Queue{
    Link *head;
    Link *tail;
    Link *proc;
    Link *cur;

    int cnt;

    Queue(){
        tail = head = new Link;
        cnt=0;
    }

    void enqueue(int ident,int times){
        tail = tail->next = new Link(ident,times,NULL);
        cnt++;
    }

    void cenqueue(Link *link){
        tail = tail->next = link;
        cnt++;
    }

    Link* dequeue(){
        if(cnt!=0){
            Link *it = head->next;
            head->next = head->next->next;
            if(head->next==NULL) tail = head;
            cnt--;
            return it;
        }
        else return NULL;
    }

    void spin(){
        Link *it = dequeue();
        enqueue(it->identifier,it->time);
    }

    Link* cdequeue(){
        
        if(cnt!=0){
            cur = head->next;
            Link *it = tail;
            if(cnt > 1){
                while(cur->next->next !=NULL){
                    cur=cur->next;
                }
                tail=cur;
                tail->next=NULL;
            }
            else{
                tail = head;
            }

            cnt--;
            return it;
        }
        else return NULL;
    }
};

struct Stack{
    Link *top;
    int cnt;

    Stack(){
        top = NULL;
        cnt=0;
    }

    //void push(int ident,int times){
    //    top = new Link(ident,times,top);
    //    cnt++;
    //}

    void push(Link *link){
        link->next = top;
        top = link;
        cnt++;
    }

    int pop(){
        if(cnt!=0){
            int it = top->identifier;
            Link *temp = top;
            top = top->next;
            temp->next =NULL;
            delete temp;
            cnt--;
            return it;
        }
        else return 0;
    }
};

int main(){
    int timecycle,identifier,time;
    string command = "start";
    Queue queue = Queue();
    Stack stack = Stack();
    Queue cqueue = Queue();
    
    cin >> timecycle;
    
    while(command != "END"){
        cin >> command;

        if(command == "LOAD"){
            cin >> identifier >> time;
            queue.enqueue(identifier,time);
        }

        else if(command == "PROC"){
            if(cqueue.cnt>0){
                if(cqueue.tail->time == 0){
                    stack.push(cqueue.cdequeue());
                }
            }
            if(queue.cnt>0){
                cqueue.cenqueue(queue.dequeue());
            }

            if(cqueue.cnt>0){
                cqueue.head->next->time = cqueue.head->next->time - timecycle;
                if(cqueue.head->next->time < 0){
                    cqueue.head->next->time = 0;
                }

                cout << "PROC "<< cqueue.head->next->identifier << ' ' << cqueue.head->next->time << endl;

                if(cqueue.cnt>1){
                    cqueue.spin();
                }
                
            }
            else{
                cout << "PROC -1 -1\n";
            }
        }

        else if(command == "UNLD"){
            cout << "UNLD" << ' '<< stack.pop() << endl;
        }

    }
    
    return 0;
}