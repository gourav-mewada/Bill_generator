#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// function for generate the bill

struct items
{
    char item[20];
    float price;
    int qty;
};
struct orders
{
    char customer[50];
    char date[50];
    int numofitems;
    struct items itm[50];
};
void generate_bill_header(char name[50], char date[50])
{
    printf("\n\n");
    printf("\t CHANCHAL SWEETS  AND  RESTAURENT\n");
    printf("*************************************************\n");
    printf("date:%s", date);
    printf("\nInvoice To :%s", name);
    printf("\n----------------------------------------------\n");
    printf("Items\t\t");
    printf("Quantity\t\t");
    printf("Total\t\t\n");
    printf("-----------------------------------------------\n\n");
}
void generate_bill_body(char item[50], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t\n", qty * price);
}
void generate_bill_footer(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float nettotal = total - dis;
    float cgst = 0.09 * nettotal;
    float grandtotal = nettotal + 2 * cgst;
    printf("-----------------------------------------------\n");
    printf("\nSub total\t\t\t%.2f", total);
    printf("\nDiscount @10 %s\t\t\t%.2f", "%", dis);
    printf("\n \n\t\t\t-------\n");
    printf("\nNet Total\t\t\t%.2f", nettotal);
    printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\nSGST @9%s\t\t\t%.2f\n", "%", cgst);
    printf("-----------------------------------------------\n");
    printf("\nGrandTotal\t\t\t%.2f", grandtotal);
    printf("\n------------------------------------------------\n");
}

int main()
{
    int opt, n;
    
    struct orders ord;
    struct orders order;
    char savebill = 'y'; 
    char contflag = 'y';
    FILE *ptr;
    char name[50];
    print("Hellow world");
    while (contflag == 'y')
    {
float total=0; 
int  invoicefound = 0;
        printf("\t===============CHANCHAL SWEETS AND RESTAURENT================\n");
        printf("\n 1.Generate Invoices ");
        printf("\n 2.Show  all Invoices ");
        printf("\n 3.Search  Invoices ");
        printf("\n 4.Exist\n\n");
        printf("Please select your prefered operation \t");
        scanf("%d", &opt);
        fgetc(stdin);
        switch (opt)
        {
        case 1:
               
                printf("\nPlease Enter the name of the customer :\t");
                fgets(ord.customer, 50, stdin);
                ord.customer[strlen(ord.customer) - 1] = 0;
                strcpy(ord.date, __DATE__);
                printf("\nPlease Enter the number of items:\t");
                scanf("%d", &n);
                ord.numofitems = n;
            for (int i = 0; i < n; i++)
            {
                fgetc(stdin);
                printf("\n\n");
                printf("Please enter the item: %d \t", i + 1);
                fgets(ord.itm[i].item, 20, stdin);
                ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
                printf("Please Enter the quantity:\t");
                scanf("%d", &ord.itm[i].qty);
                printf("Please Enter the unit price:\t");
                scanf("%f", &ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;
            }
            generate_bill_header(ord.customer, ord.date);
            for (int i = 0; i < ord.numofitems; i++)
            {
                generate_bill_body(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }
            generate_bill_footer(total);
            printf("\n Do you want to save invoice[y/n]:\t");
            scanf("%s", &savebill);
            if (savebill == 'y')
            {
                ptr = fopen("Restaurentbill.dat", "a+");
                fwrite(&ord, sizeof(struct orders), 1, ptr);
                if (fwrite != 0)
                {
                    printf("\nsuccessfully saved");
                }
                else
                {
                    printf("\nError saving");
                }
                fclose(ptr);
            }
            break;
        case 2:
            ptr = fopen("Restaurentbill.dat", "r");
            printf("\n*****Your Previous Invoices ********\n");
            while (fread(&order, sizeof(struct orders), 1, ptr))
            {
                float tot = 0;
                generate_bill_header(order.customer, order.date);
                for (int i = 0; i < order.numofitems; i++)
                {
                    generate_bill_body(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    tot += order.itm[i].qty * order.itm[i].price;
                }
                generate_bill_footer(tot);
            }
            fclose(ptr);
            
            break;
        case 3:
            printf("\n Enter the name of the computer\t");
            
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = 0;
            ptr = fopen("Restaurentbill.dat", "r");
            printf("\n*****Invoice of %s********\n", name);
            while (fread(&order, sizeof(struct orders), 1, ptr))
            {
                float tot = 0;
                if (!strcmp(order.customer, name))
                {
                    generate_bill_header(order.customer, order.date);
                    for (int i = 0; i < order.numofitems; i++)
                    {
                        generate_bill_body(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                        generate_bill_footer(tot);
                        invoicefound = 1;
                    }
                }
            }
            if (!invoicefound)
            {
                printf("sorry the Invoices for %s doesnot exists", name);
            }
            fclose(ptr);
            break;
        case 4:
            printf("\n\t\t Bye Bye:\n\n");
            exit(0);
            break;
        default:
            printf("Sorry invalid option");
            break;
        }printf("\nDo you want to perform another operation ?[y/n]:\t");
        scanf("%s", &contflag);
        printf("\n\n");
    }
    return 0;
}
