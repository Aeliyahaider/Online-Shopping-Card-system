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
void addProduct() {
    system("cls");
    int id, price, qty, pos, cnt = 0, i;
    char name[20], ch;
    
    printf("=========================================================\n\n");
    printf("\t\t ADD PRODUCTS!!\n\n");
    printf("=========================================================\n\n");
    
    // Input validation loop for ID
    while (1) {
        printf("\nEnter the ID of the product (1-9999): ");
        id = validateInput(1, 9999);
        
        // Check if ID already exists
        int idExists = 0;
        for (ptr = first; ptr != NULL; ptr = ptr->next) {
            if (ptr->id == id) {
                idExists = 1;
                break;
            }
        }
        
        if (!idExists) break;
        printf("Product ID already in use. Please enter a different ID.\n");
    }
    
    // Input validation loop for name
    while (1) {
        printf("\nEnter the name of the product (letters only, max 19 chars): ");
        scanf("%19s", name);
        if (isProductNameValid(name)) break;
        printf("Invalid product name! Only letters are allowed (max 19 chars).\n");
    }
    
    printf("\nEnter the price of the product (1-10000): ");
    price = validateInput(1, 10000);
    
    printf("\nEnter the quantity of the product (1-1000): ");
    qty = validateInput(1, 1000);
    
    newnode = create_node(id, name, price, qty);
    if (newnode == NULL) {
        printf("\nFailed to create product.");
        getch();
        return;
    }
    // Add to beginning if list is empty
    if (first == NULL) {
        first = last = newnode;
    } 
    else {
        // Add to end of list
        last->next = newnode;
        last = newnode;
    }
    
    saveProductsToFile(); // Save after adding
    printf("\nProduct Added Successfully!!");
    
    printf("\nDo you want to add another product[Y/N]? ");
    scanf(" %c", &ch);
    if (toupper(ch) == 'Y') {
        addProduct();
    }
} 
void displayAllProduct() {
    system("cls");
    if (first == NULL) {
        ISEMPTY;
        printf("No Products Available. \n");
        return;
    }
    
    printf("=========================================================\n\n");
    printf("\t\t Product Details\n\n");
    printf("=========================================================\n\n");
    printf("ID\tName\tQty\tPrice(Rs.)\n\n");
    
    for (ptr = first; ptr != NULL; ptr = ptr->next) {
        printf("%d\t%s\t%d\t%d\n", ptr->id, ptr->name, ptr->qty, ptr->price);
    }
    
    printf("=========================================================\n\n");
}

void removeProduct() {
    if (first == NULL) {
        ISEMPTY;
        printf("\nNo Products to delete\n");
        getch();
        return;
    }
    
    printf("\nEnter the ID of the product to be deleted: ");
    int id = validateInput(1, 9999);
    int found = 0;
    
    // Check if product exists in cart
    for (ptr2 = first2; ptr2 != NULL; ptr2 = ptr2->next2) {
        if (ptr2->id == id) {
            printf("\nCannot delete product. It exists in the cart!");
            getch();
            return;
        }
    }
    // Find and delete product
    prev = NULL;
    ptr = first;
    
    while (ptr != NULL) {
        if (ptr->id == id) {
            found = 1;
            if (prev == NULL) {
                // Deleting first node
                first = ptr->next;
                if (first == NULL) last = NULL;
            } else {
                prev->next = ptr->next;
                if (ptr == last) last = prev;
            }
            free(ptr);
            saveProductsToFile(); // Save after removal
            printf("\nProduct deleted successfully!");
            break;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    
    if (!found) {
        printf("\nProduct Not Found!!");
    }
    getch();
}

int posProduct(int id) {
    int pos = 0;
    for (ptr = first; ptr != NULL; ptr = ptr->next) {
        pos++;
        if (ptr->id == id) {
            return pos;
        }
    }
    return 0;
}

int posCart(int id) {
    int pos = 0;
    for (ptr2 = first2; ptr2 != NULL; ptr2 = ptr2->next2) {
        pos++;
        if (ptr2->id == id) {
            return pos;
        }
    }
    return 0;
}

void purchaseProduct() {
    int ch;
    while (1) {
        system("cls");
        displayAllProduct();
        printf("\n\t\t WELCOME CUSTOMER!!\n\n");
        printf("1. Add to Cart\n");
        printf("2. View Cart\n");
        printf("0. Back\n");
        printf("\nPlease enter your Choice: ");
        ch = validateInput(0, 2);
        
        switch (ch) {
            case 1: addToCart(); break;
            case 2: viewCart(); break;
            case 0: return;
            default: printf("Valid choice not entered!");
        }
    }
}

void addToCart() {
    system("cls");
    displayAllProduct();
    
    if (first == NULL) {
        printf("\nNo products available to add to cart!");
        getch();
        return;
    }
    
    int id, qty;
    printf("\nEnter the ID of the product you wish to add to cart: ");
    id = validateInput(1, 9999);
    
    // Check if product exists
    int productExists = 0;
    for (ptr = first; ptr != NULL; ptr = ptr->next) {
        if (ptr->id == id) {
            productExists = 1;
            break;
        }
    }
    
    printf("\nEnter the quantity[1-10]: ");
    qty = validateInput(1, 10);
    
    checkStock(id, qty);
    
    // Check if product already in cart
    for (ptr2 = first2; ptr2 != NULL; ptr2 = ptr2->next2) {
        if (ptr2->id == id) {
            ptr2->qty += qty;
            if (ptr2->qty > 10) {
                ptr2->qty = 10;
                printf("\nQuantity limited to 10 as per policy.");
            }
            saveCartToFile();
            printf("\nProduct quantity updated in cart!");
            getch();
            return;
        }
    }
    
    // Add new item to cart
    newnode2 = create_node2(id, qty);
    if (newnode2 == NULL) {
        printf("\nFailed to add to cart.");
        getch();
        return;
    }
    
    void checkStock(int id, int qty)
{
    if (first == NULL)
    {
        ISEMPTY;
    }
    else
    {
        for (ptr = first;ptr != NULL;ptr = ptr->next)
        {
            if (ptr->id == id)
            {
                if (ptr->qty<qty)
                {
                    printf("Not enough products available.");
                    getch();
                    return purchaseProduct();
                }
            }
        }

    }
}
void viewCart()
{
    system("cls");
    if (first == NULL)
    {
        ISEMPTY;
        printf("No Products Available in Cart. \n");
        getch();
        return main();
    }
    else
    {
        printf("=========================================================\n\n");
        printf("\t\t PRODUCTS IN CART\n\n");
        printf("=========================================================\n\n");
        printf("ID\t Name\t Qty.\t Price(Rs.)\n\n");
        for (ptr2 = first2;ptr2 != NULL;ptr2 = ptr2->next2)
        for (ptr2 = first2;ptr2 != NULL;ptr2 = ptr2->next2)
        {
            printf("%d\t", ptr2->id);
            for (ptr = first;ptr != NULL;ptr = ptr->next)
            {
                if (ptr->id==ptr2->id)
                {
                    printf("%s\t", ptr->name);
                    printf("%d\t", ptr2->qty);
                    printf("%d\t", ptr->price);
                }

            }
            printf("\n");
        }
        printf("=========================================================\n\n");
    }
    getch();
}

void generateBill()
{
    int ch;
    system("cls");
    viewCart();
    printf("\n1. Modify your cart.");
    printf("\n2. Proceed to Checkout.");
    printf("\n0. Back");
    printf("\nPlease enter your Choice: ");
    scanf("%d", &ch);
     switch (ch)
    {
        case 1: {
            modifyCart();
            break;
        }
        case 2: {
            checkout();
            break;
        }
        case 0:
        {
            return main();
        }
        default: {
            printf("Valid choice not entered!");
            getch();
            return generateBill();
        }
    }
}

void modifyCart()
{
    int id,qty,ch;
    system("cls");
    viewCart();
    printf("\nEnter the ID of the Product you wish to Modify: ");
    scanf("%d",&id);
    for (ptr2 = first2;ptr2 != NULL;ptr2 = ptr2->next2) {
        if (ptr2->id == id)
        {
            printf("\n1. Delete Product.");
            printf("\n2. Modify the quantity.");
            printf("\n0. Back.");
            printf("\nPlease enter your Choice: ");
            scanf("%d", &ch);
            switch (ch) {
                case 1: {
                    deleteCart(id);
                    getch();
                    return generateBill();
                }
                case 2: {
                    printf("\nEnter the new quantity[1-10]: ");
                    scanf("%d", &qty);
                    if (qty <= 10) {
                        updateCart(id, qty);
                        getch();
                        return generateBill();
                    } else {
                        printf("Quantity can't exceed 10.");
                        getch();
                        return modifyCart();
                    }
                }
                case 0: {
                    return generateBill();
                }
                default: {
                    printf("Valid choice not entered!");
                    getch();
                    return generateBill();
                }
            }

        }

    }
    printf("\n Product Not Found!!");
    getch();
    return generateBill();

}
