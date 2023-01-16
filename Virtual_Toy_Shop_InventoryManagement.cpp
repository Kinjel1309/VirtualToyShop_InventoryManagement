
/*PROJECT NAME:- VIRTUAL TOY SHOP
In this project of ours the flow of program is based on real life functioning of Toy Shop.
It implements all operations of Toy shop like:
-processes orders           -customers in waiting Queue
-replenishes stock/inventory when exhausted
-Also at end of day the shopkeeper has to enter a valid password to access records of things done during daytime
and to find his total earnings during the day.
*/
#include <iostream>
using namespace std;
#define DAILY_LIMIT 3
#define MAX_INVENTORY_SIZE 50
#define MAX 10

class Toy
{
    //Toy class
    int toy_ID;
    string toy_name;
    int price;
    int quantity;
    friend class Shopkeeper;
    friend class Customer;
    friend class Order;
public:
    Toy()
    {
        toy_ID=0;
        toy_name="\0";	//default constructor
        price=0;
        quantity=0;
    }
    Toy(int id, string toy, int price1, int qnty)
    {
        toy_ID=id;
        toy_name=toy;	//parameterized constructor
        price=price1;
        quantity=qnty;
    }
};

class Shopkeeper;      ///Shopkeeper class declaration to make it accessible to Order class

class Order
{
    string name;                                 //fields of Order class
    int no_of_items;
    Toy orderedToys[MAX];
    string status;
    friend class Shopkeeper;
    friend class Customer;
public:
    void link_order(Shopkeeper S1);  ///Order class is given access to Shopkeeper's inventory
    Order()
    {
        name="\0";
        no_of_items=0;
        status="\0";
    }
    string get_status()
    {
        return status;
    }
    string get_name()
    {
        return name;
    }
    void set_status(string stat)
    {
        status = stat;
    }
};

class Shopkeeper
{
    Toy Inventory[MAX_INVENTORY_SIZE];
    int Inventory_Size;      //indicates no. of available items in inventory
    friend class Order;
    int total_daily_earnings;
    string password;
public:

    void Initial_Inventory()  //defines initial toy inventory
    {
        Inventory_Size=15;
        //Original Toy Inventory
        total_daily_earnings=0;

        Inventory[0]=Toy(3001,"Rubik's Cube",15,30);
        Inventory[1]=Toy(3002,"Barbie Doll",100,30);
        Inventory[2]=Toy(3003,"Frisbee Toy ",50,30);
        Inventory[3]=Toy(3004,"Star Wars Toys",450,30);
        Inventory[4]=Toy(3005,"Lego Blocks",300,30);
        Inventory[5]=Toy(3006,"Toy Train",500,30);
        Inventory[6]=Toy(3007,"Toy Airplane",400,30);
        Inventory[7]=Toy(3008,"Toy Ship   ",300,30);
        Inventory[8]=Toy(3009,"Toy Car   ",250,30);
        Inventory[9]=Toy(3010,"Monopoly",300,30);
        Inventory[10]=Toy(3011,"Dominos Game",220,30);
        Inventory[11]=Toy(3012,"Snakes Ladders",135,30);
        Inventory[12]=Toy(3013,"Toy Guitar",670,30);
        Inventory[13]=Toy(3014,"Toy Piano",800,30);
        Inventory[14]=Toy(3015,"Toy Drum",590,30);
    }
    Order process_order(Order);
    void display_inventory();
    void replenishInventory();
    void generate_bill(Order);
    void add_new_item(string);
    Toy feedback_generator();
    void daily_earnings(int);
    int get_money()
    {
        return total_daily_earnings;
    }
    bool login(string);
};

bool Shopkeeper::login(string authorization_key) 	//shopkeeper login facility
{
    password = "admin@123";
    return password==authorization_key;
}

void Order::link_order(Shopkeeper S1) 	//function of Order class
{
    ///Links toy_IDs provided in order to other fields of the toy-name and price
    for(int i=0; i<no_of_items; i++)
    {
        for(int k=0; k<S1.Inventory_Size; k++)
        {
            if(orderedToys[i].toy_ID==S1.Inventory[k].toy_ID)
            {
                orderedToys[i].toy_name=S1.Inventory[k].toy_name;
                orderedToys[i].price=S1.Inventory[k].price;
                break;
            }
        }
    }
}

Order Shopkeeper::process_order(Order O) //processing order, update inventory stock if possible and return order with updated status-completed or waiting
{
    int flag=0;

    for(int i=0; i<O.no_of_items; i++) //process ordered items one by one
    {
        for(int k=0; k<Inventory_Size; k++) //looking in inventory
        {
            if(O.orderedToys[i].toy_ID==Inventory[k].toy_ID)
            {
                if(O.orderedToys[i].quantity>Inventory[k].quantity)
                {
                    O.status="waiting";
                    flag=1;
                }
            }
        }
    }
    if(flag==0)
    {
        //if flag is not 0,stock in inventory is not changed
        for(int i=0; i<O.no_of_items; i++)
        {
            for(int k=0; k<Inventory_Size; k++)
            {
                if(O.orderedToys[i].toy_ID==Inventory[k].toy_ID)
                {
                    Inventory[k].quantity=Inventory[k].quantity-O.orderedToys[i].quantity;
                    //inventory stock reduced
                }
            }
        }
        O.status="completed"; //order status changed
    }
    return O;
}

void Shopkeeper::display_inventory()              //displays Toy Inventory
{
    cout<<"ID\t Name\t\tprice\tQuantity"<<endl;
    for(int i=0; i<Inventory_Size; i++)
    {
        cout<<Inventory[i].toy_ID<<"\t";
        cout<<Inventory[i].toy_name<<"\t";
        cout<<Inventory[i].price<<"\t";
        cout<<Inventory[i].quantity<<"\n";
    }
}

void Shopkeeper::replenishInventory()          //Replenishing exhausted items Stock
{
    for(int i=0; i<Inventory_Size; i++)
    {
        if(Inventory[i].quantity<=7) //if stock of an item is less than 5 then replenish that stock
        {
            Inventory[i].quantity=Inventory[i].quantity+30;
        }
    }
}

void Shopkeeper::daily_earnings(int customer_paid)  //counts total money earned in a day
{
    total_daily_earnings+=customer_paid;
}

void Shopkeeper::generate_bill(Order custorder)            //billing function
{
    int bill=0;
    for(int i=0; i<custorder.no_of_items; i++)
    {
        bill+=custorder.orderedToys[i].quantity*custorder.orderedToys[i].price;
    }
    cout<<"Your Total Bill is :"<<bill<<" Rs. "<<endl;
    daily_earnings(bill);
}

void Shopkeeper::add_new_item(string new_toy)             //adding new item to the inventory
{
    cout<<"The most demanded item is: "<<new_toy<<endl;
    if (Inventory_Size<MAX_INVENTORY_SIZE)
    {
        Inventory_Size=Inventory_Size+1;
        Inventory[Inventory_Size-1].toy_name=new_toy;
        cout<<"Enter new Toy ID :";
        cin>>Inventory[Inventory_Size-1].toy_ID;
        cout<<"Set its Price :";
        cin>>Inventory[Inventory_Size-1].price;
        Inventory[Inventory_Size-1].quantity=30;
    }
    else
    {
        cout<<"Inventory is full. Cannot add new toy!"<<endl;
    }
}

class Customer
{
    string Myname;                 //fields of Customer
    int no_of_items=0;
    Toy order[10];
    friend class Queue;
public:
    void accept()  //accept personal details of customer
    {
        string first_name,last_name;
        cout<<"\n\n            Welcome Dear Customer !                     "<<endl;
        cout<<""<<endl;
        cout<<"Enter your Full name(Firstname Lastname): ";
        cin>>first_name;
        cin>>last_name;
        Myname=first_name +" "+last_name;
    }
    Order give_order();
    Order change_order();
    Order waiting_order();
    void display_order(Order);
};

Order Customer::give_order()                    //accepting customer's order
{
    int flag=0;
    Order my_order;
    my_order.name=Myname;
    cout<<"Enter the number of types of toys you want to order: ";
    cin>>no_of_items;
    my_order.no_of_items=no_of_items;
    for(int i=0; i<no_of_items; i++)
    {
        do
        {
            if(flag==1)
            {
                cout<<"INVALID ID."<<endl;
                cout<<"Please enter valid ID:"<<endl;
            }
            else
            {
                cout<<"Enter the Toy"<<i+1<<" ID: ";
            }
            cin>>order[i].toy_ID;
            if(order[i].toy_ID<3001)
            {
                flag=1;
            }
            else
            {
                flag=0;
            }
        }
        while(flag==1);
        cout<<"Enter the Quantity you wish to buy: ";
        cin>>order[i].quantity;
        my_order.orderedToys[i]=order[i];
    }
    my_order.status="processing";
    return my_order;
}

Order Customer::change_order()                 //change customer order
{
    Order my_order;
    my_order.name=Myname;
    my_order.no_of_items=no_of_items;
    for(int i=0; i<no_of_items; i++)
    {
        cout<<"Toy ID "<<order[i].toy_ID<<":"<<endl;
        cout<<"Enter the new quantity:";
        cin>>order[i].quantity;
        my_order.orderedToys[i]=order[i];
    }
    my_order.status="processing";
    return my_order;
}

void Customer::display_order(Order P)                  //displaying customer order
{
    cout<<"Customer ordered: "<<endl;
    cout<<"Toy\t\tQuantity"<<endl;
    for(int i=0; i<P.no_of_items; i++)
    {
        cout<<P.orderedToys[i].toy_name<<"\t"<<P.orderedToys[i].quantity<<endl;
    }
}

Order Customer::waiting_order() 	//treating orders of customers in waiting queue
{
    Order my_order;
    my_order.name=Myname;
    my_order.no_of_items=no_of_items;
    for(int i=0; i<no_of_items; i++)
    {
        my_order.orderedToys[i]=order[i];
    }
    my_order.status="processing";
    return my_order;
}

class qnode    //node of waiting queue
{
    //Data fields;
    Customer P;
    qnode *next;
    friend class Queue;
    qnode(Customer N)
    {
        P=N;
        next=NULL;
    }
};

class Queue      //implementing waiting queue
{
    qnode *front,*rear;
public:
//functions
    void enq(Customer P);
    Customer deq();
    void display();
    Queue()
    {
        front=rear=NULL;
    }
    bool isempty()
    {
        return front==NULL;
    }
};

void Queue::enq(Customer P)	//enqueue operation
{
    qnode *newnode= new qnode(P);
    if(front==0 && rear==0)
    {
        front=newnode;
        rear=newnode;
    }
    else
    {
        rear->next=newnode;
        rear=newnode;
    }
}

Customer Queue::deq()	//dequeue operation
{
    Customer current;
    current=front->P;
    qnode *ptr=front;
    if(front==0 && rear==0)
    {
        cout<<"No Customers in the Queue."<<endl;
    }
    else
    {
        front=front->next;
        delete ptr;
    }
    return current;
}

void Queue::display()
{
    qnode *ptr=front;
    if(front==0)
    {
        cout<<"No Customers in Waiting Queue."<<endl;
    }
    else
    {
        cout<<"\nCustomers in waiting queue"<<endl;
        while(ptr!=NULL)
        {
            cout<<ptr->P.Myname<<" "<<endl;
            ptr=ptr->next;
        }
    }
}

class fbnode  //node of list to store suggestions for new toy
{
    string suggest_Toy;    //name of suggested toy
    int count;             //no of times a suggestion is made
    fbnode *link;
    friend class fb_list;
public:

    fbnode(string s1)
    {
        count=1;
        link=NULL;
        suggest_Toy=s1;
    }
};

class fb_list      //list to store suggestions for new toy
{
    fbnode *head;
public:
    fb_list()
    {
        head=NULL;
    }
    void add_node();
    void display();
    void remove_node();
    string most_demanded();
    void sort_list();

};
void fb_list::add_node()
{
    string s1;
    int search_flag=0;

    cout<<"Please suggest toy you would recommend us having: ";
    cout<<"(Capitalize first letter of each new word. Enter input without spaces): ";
    cin>>s1;

    fbnode *a=new fbnode(s1);
    fbnode *ptr=head;
    if(head==NULL)
    {
        head=a;
    }
    else
    {
        while(ptr!=NULL)
        {
            if (a->suggest_Toy==ptr->suggest_Toy)  ///if suggested item already exists in the list just increment count
            {
                ptr->count=ptr->count+1;
                search_flag=1;
                break;
            }
            ptr=ptr->link;
        }
        ptr=head;
        if(search_flag!=1)
        {
            while(ptr->link!=NULL)
            {
                ptr=ptr->link;
            }
            ptr->link=a;    ///else add suggestion to the list
        }
    }
}

void fb_list::display()
{
    fbnode *ptr = head;
    cout<<"Customers' suggested items are: "<<endl;
    while(ptr!=NULL)
    {
        cout<<ptr->suggest_Toy<<"\t";
        cout<<ptr->count<<endl;
        ptr=ptr->link;
    }
    cout<<endl;
}
void fb_list::sort_list()
{
    ///Sorts the list in descending order(most suggested item first) using selection sort algorithm
    fbnode *maxptr=head;
    string tempstr;
    int tempcnt;
    for(fbnode *ptr=head; ptr->link!=NULL; ptr=ptr->link)
    {
        maxptr=ptr;
        for(fbnode *ptr1=ptr->link; ptr1!=NULL; ptr1=ptr1->link)
        {
            if(ptr1->count>maxptr->count)
                maxptr=ptr1;
        }
        tempstr=maxptr->suggest_Toy;
        tempcnt=maxptr->count;			//swapping
        maxptr->suggest_Toy=ptr->suggest_Toy;
        maxptr->count=ptr->count;
        ptr->suggest_Toy=tempstr;
        ptr->count=tempcnt;
    }
}
void fb_list::remove_node()
{
    fbnode *ptr=head;               //at beginning
    head=ptr->link;
    delete ptr;

}
string fb_list::most_demanded()
{
    string st;
    sort_list(); //sort list
    display(); //display sorted list
    st=head->suggest_Toy; //fetch most demanded item
    return st;
}

int main()                               //main function
{
    Shopkeeper S;
    S.Initial_Inventory(); //Fetch Original Inventory
    Customer C1; //to refer to customers in waiting queue
    int num;
    char control='N';
    Queue waiting_queue;
    Order O; //refer to orders of new customers
    Order lastOrder; //last order of a day
    fb_list feedback;
    string authorization_key;
    do //Start of new day
    {
        cout<<"\n*Customer end*\n";
        while(true) 	//while loop to acknowledge orders in waiting queue
        {
            if(waiting_queue.isempty())
            {
                break;
            }
            C1=waiting_queue.deq();
            Order O1=C1.waiting_order();
            O1.link_order(S);
            C1.display_order(O1);
            O1=S.process_order(O1);
            while(O1.get_status()=="waiting")
            {
                cout<<"Your order cannot be completed right now."<<endl;
                cout<<"You can -"<<endl;
                cout<<"1. CHANGE your order"<<endl;
                cout<<"2. CANCEL your order"<<endl;
                cout<<"3. Continue waiting"<<endl;
                cout<<"Choose an option"<<endl;
                cin>>num;
                switch(num)
                {
                case 1:
                    O1=C1.change_order();
                    O1.link_order(S);
                    O1=S.process_order(O1);
                    break;
                case 2:
                    cout<<"Your order has been cancelled"<<endl;
                    O1.set_status("Cancelled");
                    break;
                case 3:
                    waiting_queue.enq(C1);
                    O1.set_status("In_queue");
                    break;
                }

            }
            if(O1.get_status()=="completed")
            {
                cout<<"Your order has been successfully completed"<<endl;
                S.generate_bill(O1);
                cout<<"Thank you for shopping with us!"<<endl;
                feedback.add_node();
            }
            waiting_queue.display();
            if(O1.get_name()==lastOrder.get_name())
                break;
        }

        for(int i=0; i<DAILY_LIMIT; i++)
        {
            //for loop for every new customer order
            cout<<" TOY MENU  "<<endl;
            S.display_inventory();
            Customer C;
            C.accept();
            O=C.give_order();
            O.link_order(S);
            O=S.process_order(O);
            C.display_order(O);
            while(O.get_status()=="waiting")
            {
                cout<<"Your order cannot be completed right now."<<endl;
                cout<<"You can -"<<endl;
                cout<<"1. CHANGE your order"<<endl;
                cout<<"2. CANCEL your order"<<endl;
                cout<<"3. Continue waiting"<<endl;
                cout<<"Choose an option"<<endl;
                cin>>num;
                switch(num)
                {
                case 1:
                    O=C.change_order();
                    O.link_order(S);
                    O=S.process_order(O);
                    break;
                case 2:
                    cout<<"Your order has been cancelled"<<endl;
                    O.set_status("Cancelled");
                    break;
                case 3:
                    waiting_queue.enq(C);
                    cout<<"You have been added to the waiting queue."<<endl;
                    O.set_status("In_queue");
                    break;

                }
            }
            if(O.get_status()=="completed")
            {
                cout<<"Your order has been successfully completed"<<endl;
                S.generate_bill(O);
                cout<<"Thank you for shopping with us!"<<endl;
                feedback.add_node();
            }
        }

        lastOrder=O;
        cout<<"The Shop is closed for the day"<<endl;

        cout<<"\n*Shopkeeper end*\n";
        for (int i= 0; i < 3; i++)
        {
            cout<<"Enter password: ";
            cin>>authorization_key;
            if(S.login(authorization_key))
            {

                cout<<"Today's total earning: "<<S.get_money()<<" Rs."<<endl;

                waiting_queue.display();

                cout<<"\nCurrent Toy Inventory:\n"<<endl;
                S.display_inventory();

                cout<<"\nFeedback results:"<<endl;
                string most_demanded_toy=feedback.most_demanded();
                cout<<"Press A to add the most demanded toy to the inventory: ";
                cin>>control;
                if (control=='A' || control=='a')
                {
                    cout<<"Adding new toy: "<<endl;
                    S.add_new_item(most_demanded_toy);
                    feedback.remove_node(); //remove suggestion from list after adding to inventory
                }
                cout<<"\nTHE REPLENISHED TOY INVENTORY"<<endl;
                S.replenishInventory();
                S.display_inventory();
                break;
            }
            else
                cout<<"Wrong password!"<<2-i<<" attempt/attempts left"<<endl;
        }
        cout<<"*Day End*"<<endl;
        cout<<"\n\n\n*New Day*\n";
        cout<<"\nPress Y to open shop: ";
        cin>>control;
    }
    while(control=='Y' || control=='y');
    return 0;
}
/*
OUTPUT -:
Customer end
 TOY MENU
ID       Name           price   Quantity
3001    Rubik's Cube    15      30
3002    Barbie Doll     100     30
3003    Frisbee Toy     50      30
3004    Star Wars Toys  450     30
3005    Lego Blocks     300     30
3006    Toy Train       500     30
3007    Toy Airplane    400     30
3008    Toy Ship        300     30
3009    Toy Car         250     30
3010    Monopoly        300     30
3011    Dominos Game    220     30
3012    Snakes Ladders  135     30
3013    Toy Guitar      670     30
3014    Toy Piano       800     30
3015    Toy Drum        590     30


            Welcome Dear Customer !

Enter your Full name(Firstname Lastname): Jim Halpert
Enter the number of types of toys you want to order: 2
Enter the Toy1 ID: 111
INVALID ID.
Please enter valid ID:
3012
Enter the Quantity you wish to buy: 15
Enter the Toy2 ID: 3001
Enter the Quantity you wish to buy: 21
Customer ordered:
Toy             Quantity
Snakes Ladders  15
Rubik's Cube    21
Your order has been successfully completed
Your Total Bill is :2340 Rs.
Thank you for shopping with us!
Please suggest toy you would recommend us having: (Capitalize first letter of each new word. Enter input without spaces): HotWheelsCars
 TOY MENU
ID       Name           price   Quantity
3001    Rubik's Cube    15      9
3002    Barbie Doll     100     30
3003    Frisbee Toy     50      30
3004    Star Wars Toys  450     30
3005    Lego Blocks     300     30
3006    Toy Train       500     30
3007    Toy Airplane    400     30
3008    Toy Ship        300     30
3009    Toy Car         250     30
3010    Monopoly        300     30
3011    Dominos Game    220     30
3012    Snakes Ladders  135     15
3013    Toy Guitar      670     30
3014    Toy Piano       800     30
3015    Toy Drum        590     30


            Welcome Dear Customer !

Enter your Full name(Firstname Lastname): Pam Beasly
Enter the number of types of toys you want to order: 2
Enter the Toy1 ID: 3001
Enter the Quantity you wish to buy: 11
Enter the Toy2 ID: 3012
Enter the Quantity you wish to buy: 10
Customer ordered:
Toy             Quantity
Rubik's Cube    11
Snakes Ladders  10
Your order cannot be completed right now.
You can -
1. CHANGE your order
2. CANCEL your order
3. Continue waiting
Choose an option
3
You have been added to the waiting queue.
 TOY MENU
ID       Name           price   Quantity
3001    Rubik's Cube    15      9
3002    Barbie Doll     100     30
3003    Frisbee Toy     50      30
3004    Star Wars Toys  450     30
3005    Lego Blocks     300     30
3006    Toy Train       500     30
3007    Toy Airplane    400     30
3008    Toy Ship        300     30
3009    Toy Car         250     30
3010    Monopoly        300     30
3011    Dominos Game    220     30
3012    Snakes Ladders  135     15
3013    Toy Guitar      670     30
3014    Toy Piano       800     30
3015    Toy Drum        590     30


            Welcome Dear Customer !

Enter your Full name(Firstname Lastname): Dwight Schrute
Enter the number of types of toys you want to order: 1
Enter the Toy1 ID: 3010
Enter the Quantity you wish to buy: 21
Customer ordered:
Toy             Quantity
Monopoly        21
Your order has been successfully completed
Your Total Bill is :6300 Rs.
Thank you for shopping with us!
Please suggest toy you would recommend us having: (Capitalize first letter of each new word. Enter input without spaces): HotWheelsCars
The Shop is closed for the day

Shopkeeper end
Enter password: kinjel@123
Wrong password!2 attempt/attempts left
Enter password: admin@111
Wrong password!1 attempt/attempts left
Enter password: admin@123
Today's total earning: 8640 Rs.

Customers in waiting queue
Pam Beasly

Current Toy Inventory:

ID       Name           price   Quantity
3001    Rubik's Cube    15      9
3002    Barbie Doll     100     30
3003    Frisbee Toy     50      30
3004    Star Wars Toys  450     30
3005    Lego Blocks     300     30
3006    Toy Train       500     30
3007    Toy Airplane    400     30
3008    Toy Ship        300     30
3009    Toy Car         250     30
3010    Monopoly        300     9
3011    Dominos Game    220     30
3012    Snakes Ladders  135     15
3013    Toy Guitar      670     30
3014    Toy Piano       800     30
3015    Toy Drum        590     30

Feedback results:
Customers' suggested items are:
HotWheelsCars   2

Press A to add the most demanded toy to the inventory: A
Adding new toy:
The most demanded item is: HotWheelsCars
Enter new Toy ID :3016
Set its Price :500

THE REPLENISHED TOY INVENTORY
ID       Name           price   Quantity
3001    Rubik's Cube    15      9
3002    Barbie Doll     100     30
3003    Frisbee Toy     50      30
3004    Star Wars Toys  450     30
3005    Lego Blocks     300     30
3006    Toy Train       500     30
3007    Toy Airplane    400     30
3008    Toy Ship        300     30
3009    Toy Car         250     30
3010    Monopoly        300     9
3011    Dominos Game    220     30
3012    Snakes Ladders  135     15
3013    Toy Guitar      670     30
3014    Toy Piano       800     30
3015    Toy Drum        590     30
3016    HotWheelsCars   500     30
Day End



New Day

Press Y to open shop: Y

Customer end
Customer ordered:
Toy             Quantity
Rubik's Cube    11
Snakes Ladders  10
Your order cannot be completed right now.
You can -
1. CHANGE your order
2. CANCEL your order
3. Continue waiting
Choose an option
1
Toy ID 3001:
Enter the new quantity:8
Toy ID 3012:
Enter the new quantity:10
Your order has been successfully completed
Your Total Bill is :1470 Rs.
Thank you for shopping with us!
Please suggest toy you would recommend us having: (Capitalize first letter of each new word. Enter input without spaces): Jenga
 TOY MENU
ID       Name           price   Quantity
3001    Rubik's Cube    15      1
3002    Barbie Doll     100     30
3003    Frisbee Toy     50      30
3004    Star Wars Toys  450     30
3005    Lego Blocks     300     30
3006    Toy Train       500     30
3007    Toy Airplane    400     30
3008    Toy Ship        300     30
3009    Toy Car         250     30
3010    Monopoly        300     9
3011    Dominos Game    220     30
3012    Snakes Ladders  135     5
3013    Toy Guitar      670     30
3014    Toy Piano       800     30
3015    Toy Drum        590     30
3016    HotWheelsCars   500     30


            Welcome Dear Customer !

Enter your Full name(Firstname Lastname): Angela Martin
Enter the number of types of toys you want to order: 1
Enter the Toy1 ID: 3002
Enter the Quantity you wish to buy: 21
Customer ordered:
Toy             Quantity
Barbie Doll     21
Your order has been successfully completed
Your Total Bill is :2100 Rs.
Thank you for shopping with us!
Please suggest toy you would recommend us having: (Capitalize first letter of each new word. Enter input without spaces): TeddyBear
 TOY MENU
ID       Name           price   Quantity
3001    Rubik's Cube    15      1
3002    Barbie Doll     100     9
3003    Frisbee Toy     50      30
3004    Star Wars Toys  450     30
3005    Lego Blocks     300     30
3006    Toy Train       500     30
3007    Toy Airplane    400     30
3008    Toy Ship        300     30
3009    Toy Car         250     30
3010    Monopoly        300     9
3011    Dominos Game    220     30
3012    Snakes Ladders  135     5
3013    Toy Guitar      670     30
3014    Toy Piano       800     30
3015    Toy Drum        590     30
3016    HotWheelsCars   500     30


            Welcome Dear Customer !

Enter your Full name(Firstname Lastname): Toby Flenderson
Enter the number of types of toys you want to order: 1
Enter the Toy1 ID: 3015
Enter the Quantity you wish to buy: 32
Customer ordered:
Toy             Quantity
Toy Drum        32
Your order cannot be completed right now.
You can -
1. CHANGE your order
2. CANCEL your order
3. Continue waiting
Choose an option
2
Your order has been cancelled
 TOY MENU
ID       Name           price   Quantity
3001    Rubik's Cube    15      1
3002    Barbie Doll     100     9
3003    Frisbee Toy     50      30
3004    Star Wars Toys  450     30
3005    Lego Blocks     300     30
3006    Toy Train       500     30
3007    Toy Airplane    400     30
3008    Toy Ship        300     30
3009    Toy Car         250     30
3010    Monopoly        300     9
3011    Dominos Game    220     30
3012    Snakes Ladders  135     5
3013    Toy Guitar      670     30
3014    Toy Piano       800     30
3015    Toy Drum        590     30
3016    HotWheelsCars   500     30


            Welcome Dear Customer !

Enter your Full name(Firstname Lastname): Erin Hannon
Enter the number of types of toys you want to order: 1
Enter the Toy1 ID: 3001
Enter the Quantity you wish to buy: 5
Customer ordered:
Toy             Quantity
Rubik's Cube    5
Your order cannot be completed right now.
You can -
1. CHANGE your order
2. CANCEL your order
3. Continue waiting
Choose an option
1
Toy ID 3001:
Enter the new quantity:1
Your order has been successfully completed
Your Total Bill is :15 Rs.
Thank you for shopping with us!
Please suggest toy you would recommend us having: (Capitalize first letter of each new word. Enter input without spaces): TeddyBear
The Shop is closed for the day

Shopkeeper end
Enter password: admin@123
Today's total earning: 12225 Rs.

No Customers in Waiting Queue.

Current Toy Inventory:

ID       Name           price   Quantity
3001    Rubik's Cube    15      0
3002    Barbie Doll     100     9
3003    Frisbee Toy     50      30
3004    Star Wars Toys  450     30
3005    Lego Blocks     300     30
3006    Toy Train       500     30
3007    Toy Airplane    400     30
3008    Toy Ship        300     30
3009    Toy Car         250     30
3010    Monopoly        300     9
3011    Dominos Game    220     30
3012    Snakes Ladders  135     5
3013    Toy Guitar      670     30
3014    Toy Piano       800     30
3015    Toy Drum        590     30
3016    HotWheelsCars   500     30

Feedback results:
Customers' suggested items are:
TeddyBear       2
Jenga   1

Press A to add the most demanded toy to the inventory: A
Adding new toy:
The most demanded item is: TeddyBear
Enter new Toy ID :3017
Set its Price :350

THE REPLENISHED TOY INVENTORY
ID       Name           price   Quantity
3001    Rubik's Cube    15      30
3002    Barbie Doll     100     9
3003    Frisbee Toy     50      30
3004    Star Wars Toys  450     30
3005    Lego Blocks     300     30
3006    Toy Train       500     30
3007    Toy Airplane    400     30
3008    Toy Ship        300     30
3009    Toy Car         250     30
3010    Monopoly        300     9
3011    Dominos Game    220     30
3012    Snakes Ladders  135     35
3013    Toy Guitar      670     30
3014    Toy Piano       800     30
3015    Toy Drum        590     30
3016    HotWheelsCars   500     30
3017    TeddyBear       350     30
Day End



New Day

Press Y to open shop: N 
*/
