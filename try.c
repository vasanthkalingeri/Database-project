#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
Product(catalogno 10,description 40, price 10, count 10)
start = 0, 10, 50, 60 total length = 70
Customer(id 10, name 30, emailid 40, postaladd 60)
start = 0, 10, 40, 80 total length = 140
Orders(custid 10, catalogno 10, quantity 10, amount 10)
start = 0, 10, 20, 30 total length = 40

condition codes:
0 - no condition
1 - equal
2 - not equal
3 - less than
4 - greater than
5 - less than equal
6 - greater than equal
the below mean the same except that it works on offset instead
11
12
13
14
15
16

relation codes:
0 - and
1 - or
2 - not

query of the form
select colnname from tabelename where constraints

constraints are to be of the form
colname=k
where k is constant
if of the form col1=col2 then express it into the form
col1=k1 or col1=k2 etc where k1,k2 are the values of col2

querys of the form where two tables have to be used simulateously is yet to be implemented

Guildlines for input file


offset till -1

no of conditions

condition type
condition on offset
value to be compared to / column index to be compared to NOT OFFSET
*/

int size(int *a)
{
    int n = 0;
    while(a[n++] != -1);
    n--;
    return n;
}

void sort(int a[])
{
    int i, j, n, temp;
    n = size(a);
    for(i=0;i < n-1;i++)
    {
        for(j=0;j < (n - i -1);j++)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }    
}

void printarray(int *arr, int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int check(char *value, int cond, char *var)
{
    int val1, val2;
    if(cond > 2)
    {
        val1 = atoi(value);
        val2 = atoi(var);
        switch(cond)
        {
            case 3: return val1 < val2;
            case 4: return val1 > val2;
            case 5: return val1 <= val2;
            case 6: return val1 >= val2;
        }
    }
    else
    {
        switch(cond)
        {
            case 1: return strcmp(value, var) == 0;
            case 2: return strcmp(value, var) > 0 || strcmp(value, var) < 0;
        }
    }
}

int satisfies(int res[], int relation[], int n)
{
    int result, j;
    result = res[0];
    for(j=1;j<n;j++)
    {
        if(!relation[j - 1])
            result = result & res[j];
        else
            result = result | res[j];    
    }
    return result;
}

int gettuple(FILE *fp, int *offset, int *condition, int *relation, char **var, int *condoffset, int numcond, char **value, int linelength)
{
    int i, j, k, *res, print;
    char c;
    for(j=0 ; offset[j] != -1;j++)
    {
        value[j] = (char *)calloc(sizeof(char *), offset[j]);
        fseek(fp, offset[j], SEEK_SET);
        k = 0;
        while((c=getc(fp)) != '$')
            value[j][k++] = c;
        value[j][k] = '\0';
        offset[j] += (linelength + 1);
    }
    res = (int *)calloc(sizeof(int *), numcond + 1);
    print = 1;
    for(j=0 ; j < numcond;j++)
    {
        if((condition[j] < 10) && condition[j])
        {
            printf("I am here \n");
            if(check(value[j], condition[j], var[j]))
                res[j] = 1;
            else
                res[j] = 0;
        }
        else if((condition[j] > 10) && condition[j]%10)
        {
            var[j] = value[atoi(var[j])];
            printf("var=%s\n", var[j]);
            if(check(value[j], condition[j]%10, var[j]))
                res[j] = 1;
            else
                res[j] = 0;
        }   
        else
            res[j] = 0;
    }
    return print;
}

void show(FILE *fp, int *offset, int linelength, int no_lines, int *condition, int *relation, char **var, int *condoffset, int numcond)
{
    int i,j, n, print;
    char c, **line;
    sort(offset);
    i = 1;
    n = size(offset);
    line = (char **)calloc(sizeof(char **), n);
    while(i <= no_lines)
    {
        print = 0;//checks if the line has to be printed or not
        print = gettuple(fp, offset, condition, relation, var, condoffset, numcond, line, linelength);
        if(print)
        {
            for(j=0;j<n;j++)
            {
                if(strlen(line[j]) > 0)
                {
                    printf("%s",line[j]);
                }
                printf("\t");
            }
            printf("\n");
        }
        i++;
    }
}

int getlineno(FILE *fp)
{
    char c;
    int count = 0;
    while((c=getc(fp)) != EOF)
        if(c == '\n')
            count++;
    return count;
}

int main()
{
    FILE *prodf, *custf, *ordf;
    char c, n;
    int numcond, check;
    int i, offset[50], j;
    int *condition, *relation, *condoffset;
    char **var;
    prodf = fopen("product.data", "r");
    custf = fopen("customer.data", "r");
    ordf = fopen("orders.data", "r");
    //You have a choice with product.data customer.data and orders.data
    
    //Performing the input operation
    i = 0;
    while(1)
    {
        scanf("%d", &offset[i]);
        if(offset[i++] == -1)
            break;
    }
    scanf("%d", &numcond);
    condition = (int *)calloc(sizeof(int *), numcond);
    relation = (int *)calloc(sizeof(int *), numcond - 1);
    condoffset = (int *)calloc(sizeof(int *), numcond);
    var = (char **)calloc(sizeof(char **), numcond);
    for(i=0;i<numcond;i++)
    {
        var[i] = (char *)calloc(sizeof(char *), 30);
        scanf("%d", &condition[i]);
        if(condition[i] == 0)
            continue;
        scanf("%d", &condoffset[i]);
        scanf("%s", var[i]);
        printf("var entered = %s\n", var[i]);
        if(i > 0)
        {
            scanf("%d", &relation[i - 1]);
        }
    }
    //End of taking input
    n = getlineno(ordf);
    show(ordf, offset, 40, n, condition, relation, var, condoffset, numcond);
    return 0;
}
