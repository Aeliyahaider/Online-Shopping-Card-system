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


snode* create_node(int id, char *name, int price, int qty)
{
    newnode=(snode*)malloc(sizeof(snode));
    if(newnode==NULL)
    {
        printf("\nSorry, no Products Available.");
        return 0;
    }
    else
    {
        newnode->id=id;
        strcpy(newnode->name,name);
        newnode->price=price;
        newnode->qty=qty;
        newnode->next=NULL;
        return newnode;
    }
}
snode2* create_node2(int id, int qty)
{
    newnode2=(snode2*)malloc(sizeof(snode2));
    if(newnode2==NULL)
    {
        printf("\nSorry, no Products Available.");
        return 0;
    }
     else
    {
        newnode2->id=id;
        newnode2->qty=qty;
        newnode2->next2=NULL;
        return newnode2;
    }
}
 
 void addProduct()
{
    system("cls");
    int id, price, qty,pos,cnt=0,i;
    printf("=========================================================\n\n");
    printf("\t\t ADD PRODUCTS!!\n\n");
    printf("=========================================================\n\n");
    char name[20],ch;
    printf("\nEnter the ID of the product: ");
    scanf("%d", &id);
    for (ptr = first;ptr != NULL;ptr = ptr->next)
    {
        if (ptr->id==id)
        {
            printf("Product ID already in use.");
            getch();
            return manageProduct();
        }

    }
    printf("\nEnter the name of the product: ");
    scanf("%s", name);
    printf("\nEnter the price of the product: ");
    scanf("%d", &price);
    printf("\nEnter the quantity of the product: ");
    scanf("%d", &qty);

    newnode = create_node(id, name, price, qty);
    pos = posProduct(id);
    if (pos == 0) {
        if (first == last && first == NULL) {
            first = last = newnode;
            first->next = NULL;
            last->next = NULL;
        } else {
            temp = first;
            first = newnode;
            first->next = temp;
        }
    } else {
        ptr = first;
        while (ptr != NULL) {
            ptr = ptr->next;
            cnt++;
        }
        if (pos == 1) {
            if (first == last && first == NULL) {
                first = last = newnode;
                first->next = NULL;
                last->next = NULL;
            } else {
                temp = first;
                first = newnode;
                first->next = temp;
            }
        } else if (pos > 1 && pos <= cnt) {
            ptr = first;
            for (i = 1; i < pos; i++) {
                prev = ptr;
                ptr = ptr->next;
            }
            prev->next = newnode;
            newnode->next = ptr;
        } else {
            printf("Product Not Found!!");
        }
    }
    fprintf(fp, "=========================================================\n");
    fprintf(fp, "\t\t RECEIPT\n");
    fprintf(fp, "=========================================================\n");
    fprintf(fp, "ID\tName\tQty\tPrice\tSubtotal\n");
    
    for (ptr2 = first2; ptr2 != NULL; ptr2 = ptr2->next2) {
        for (ptr = first; ptr != NULL; ptr = ptr->next) {
            if (ptr->id == ptr2->id) {
                fprintf(fp, "%d\t%s\t%d\t%d\t%d\n", 
                       ptr->id, ptr->name, ptr2->qty, ptr->price, ptr2->qty * ptr->price);
                break;
            }
        }
    }
    fprintf(fp, "=========================================================\n");
    fprintf(fp, "TOTAL AMOUNT: Rs. %d\n", total);
    fprintf(fp, "=========================================================\n");
    fclose(fp);
    printf("\nReceipt saved to receipt.txt\n");
}
snode* create_node(int id, char *name, int price, int qty) {
    newnode = (snode*)malloc(sizeof(snode));
    if (newnode == NULL) {
        printf("\nMemory allocation failed.");
        return NULL;
    }
    
    newnode->id = id;
    strncpy(newnode->name, name, 19);
    newnode->name[19] = '\0';
    newnode->price = price;
    newnode->qty = qty;
    newnode->next = NULL;
    return newnode;
}
snode2* create_node2(int id, int qty) {
    newnode2 = (snode2*)malloc(sizeof(snode2));
    if (newnode2 == NULL) {
        printf("\nMemory allocation failed.");
        return NULL;
    }
    
    newnode2->id = id;
    newnode2->qty = qty;
    newnode2->next2 = NULL;
    return newnode2;
}
void manageProduct() {
    int ch;
    while (1) {
        system("cls");
        printf("=========================================================\n\n");
        printf("\t\t WELCOME MANAGER!!\n\n");
        printf("=========================================================\n\n");
        printf("1. Add New Product\n\n");
        printf("2. Display All Products\n\n");
        printf("3. Remove Product\n\n");
        printf("0. Back\n\n");
        printf("=========================================================\n\n");
        printf("\nPlease enter your Choice: ");
        ch = validateInput(0, 3);
        
        switch (ch) {
            case 1: addProduct(); break;
            case 2: {
                displayAllProduct();
                printf("\nPress any key to continue...");
                getch();
                break;
            }
            case 3: {
                displayAllProduct();
                removeProduct();
                break;
            }
            case 0: return;
            default: printf("Valid choice not entered!");
        }
    }
}
