#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>
#define ISEMPTY printf("\nEMPTY LIST:");

struct node
{
    int id;
    char name[20];
    int price;
    int qty;
    struct node *next;
};

struct node2
{
    int id;
    int qty;
    struct node2 *next2;
};

typedef struct node snode;
typedef struct node2 snode2;
snode *newnode, *ptr, *prev,*temp;
snode *first = NULL, *last = NULL;
snode2 *newnode2, *ptr2, *prev2,*temp2;
snode2 *first2 = NULL, *last2 = NULL;


snode* create_node(int id, char *name, int price, int qty);
snode2* create_node2(int id, int qty);
void manageProduct();
void purchaseProduct();
void generateBill();
void addProduct();
void addToCart();
void viewCart();
void modifyCart();
void checkout();
void checkStock(int id, int qty);
void updateStock();
void updateCart(int id, int qty);
void removeProduct();
void deleteCart(int id);
void clearCart();
int posProduct(int id);
int posCart(int id);
void displayAllProduct();

int main()
{
    int ch;

    while (1)
    {
        system ("cls");
        printf("=========================================================\n\n");
        printf("\t\t WELCOME TO SHOPPING CART!!\n\n");
        printf("=========================================================\n\n");
        printf("1. Manage Product\n\n");
        printf("2. Purchase Product\n\n");
        printf("3. Generate Bill\n\n");
        printf("0. Exit\n\n");
        printf("=========================================================\n\n");
        printf("\nPlease enter your Choice: ");
        scanf("%d",&ch);

        switch (ch)
        {
            case 1: {
                manageProduct();
                break;
            }
            case 2:{
                purchaseProduct();
                break;
            }
            case 3: {
                generateBill();
                break;
            }
            case 0: exit(0);
            default: printf("Valid choice not entered!");
        }

    }

}