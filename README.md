# VirtualToyShop_InventoryManagement

Program works at two ends\
a) Shopkeeper End
(shopkeeper needs to login)\
b) Customer End\
• We have 3 primary classes\
a) Shopkeeper Class\
b) Customer Class\
c) Order Class
(Order Class written in order to prohibit the Customer from accessing the inventory)

• We define DAILY_LIMIT to limit the arrival of new customers to our shop in one day. (for eg:-
10 new customers a day excluding customers in waiting queue).

• DATA STRUCTURES USED:
1. Array
-Used to store the toy inventory
2. Queue(using Linked List)
-To implement the waiting queue of customers.
3. Linked List
-To store Customer’ suggestions for adding the new toy.
• The list is sorted using the Selection Sort Algorithm, (in decreasing order: highest to lower) then
the most demanded toy item is added to our original toy menu and it is then removed from the
linked list.

• Order Processing
1. First, we take the order of the customer and check if enough stock is available in our toy
inventory.
2. If enough stock is available, we complete their order, generate their bill and ask them to
suggest a toy that is not included in our original toy menu.
3. If enough stock is not available, we give them 3 options:
a) Change their order
b) Cancel their order
c) Go into the waiting queue

• Waiting Queue\
-For customers who place an order while the item’s stack is not enough.\
-Their orders are acknowledged first when the shop is opened the next day.

• Replenishing Stock
-So originally, we have 30 pieces of each toy. When they reduce to 5 or below that after orders,
we replenish the stock of the item.

• Adding a new toy to our menu based on customer suggestion\
-After the completion of their orders, we ask the customers to suggest a toy to add in our toy
menu.\
-And the most demanded item of the day is then added to our menu.

• Total Earnings for the day\
-We tell the shopkeeper how much he’s earned in a day.
