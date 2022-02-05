#include "the3.c"


void print()
{
    printf("**\n");
}
void show_ap(Apartment *head);
void show_all(Apartment *head, int len);
void show_fl(Flat *fl);
int printApts(Apartment *apt);
int main()
{
    /*Apartment *head = malloc(sizeof(Apartment));
    Apartment *tail = malloc(sizeof(Apartment));
    Apartment *head2 = head;
    NAME(tail) = "Z";
    NAME(head) = "X";
    NEXT(head) = tail;
    NEXT(tail) = head;*/
    Apartment *x = malloc(sizeof(Apartment));
    Apartment *z = malloc(sizeof(Apartment));
    Apartment *head2 = x;
    Flat *flat1 = malloc(sizeof(Flat));
    Flat *flat4 = malloc(sizeof(Flat));
    Flat *flat9 = malloc(sizeof(Flat));
    Flat *flat7 = malloc(sizeof(Flat));
    Flat *flat11 = malloc(sizeof(Flat));
    char *x_apartman = "Apartment X";
    char *z_apartman = "Apartment Z";
    char *zn = "Apartment Z";
    char *xn = "Apartment X";
    char *yn = "Apartment Y";
    int idlist[4] = {4,6,7};

    flat1 -> next = flat4;
    PREV(flat1)=NULL;
    flat1 -> id = 1;
    flat1 -> initial_bandwidth = 25;

    flat4 -> prev = flat1;
    NEXT(flat4)=NULL;
    flat4 -> id = 4;
    flat4 -> initial_bandwidth = 20;

    flat9 -> next = flat7;
    PREV(flat9)=NULL;
    flat9 -> id = 9;
    flat9 -> initial_bandwidth = 20;

    flat7 -> next = flat11;
    flat7 -> prev = flat9;
    flat7 -> id = 7;
    flat7 -> initial_bandwidth = 10;
    
    flat11 -> prev = flat7;
    NEXT(flat11)=NULL;
    flat11 -> id = 11;
    flat11 -> initial_bandwidth = 15;

    x->name = x_apartman;
    x->max_bandwidth = 80;
    x->next = z;
    x->flat_list = flat1;

    z->name = z_apartman;
    z->max_bandwidth = 60;
    z->next = x;
    z->flat_list = flat9;
    head2 = add_apartment(head2, 1, yn, 50);

    /*add_flat(head2, xn, 0, 2, 25);
    add_flat(head2, xn, 1, 6, 0);
    add_flat(head2, xn, 2, 8, 25);

    add_flat(head2, yn, 0, 9, 25);
    add_flat(head2, yn, 1, 3, 0);
    

    add_flat(head2, zn, 0, 1, 10);
    add_flat(head2, zn, 1, 7, 15);
    add_flat(head2, zn, 2, 4, 20);*/
    

    /*head2=merge_two_apartments(head2,yn,xn);*/
    /*relocate_flats_to_same_apartment(head2, yn, 9, idlist);*/
    show_all(head2, 3);
    head2=remove_apartment(head2,zn);
    show_all(head2, 3);
    show_fl(flat9);
    show_fl(flat7);
    show_fl(flat11);

    return 0;
}
void show_ap(Apartment *head)
{

    printf("name=%s max_band=%d \n", NAME(head), MBAND(head));
}
void show_fl(Flat *fl)
{
    printf("id:%d band:%d emp:%d\n", ID(fl), IBAND(fl), EMPTY(fl));
}
void show_all(Apartment *head, int len)
{
    Apartment *head2 = head;
    Flat *tmpF;
    int i;
    for (i = 0; i < len; i++)
    {
        tmpF = FLIST(head2);
        printf("APARTMENT name=%s \n\tmax_band=%d \n", NAME(head2), MBAND(head2));
        while (tmpF != NULL)
        {
            printf("\t\tid=%d \n\t\t\tband=%d \n\t\t\tis_empty=%d\n", ID(tmpF), IBAND(tmpF), EMPTY(tmpF));
            if (NEXT(tmpF) == NULL)
            {
                break;
            }
            tmpF = NEXT(tmpF);
        }
        printf("\t\t\t\treverse ");
        while (tmpF != NULL)
        {
            printf("id=%d ", ID(tmpF));
            tmpF = PREV(tmpF);
        }
        printf("\n");
        head2 = NEXT(head2);
    }
}
int printApts(Apartment *apt){
    Apartment *aCurr;
    aCurr = apt;

    if (apt == NULL)
    {
        printf("NULL\n");
        return 0;
    }
    do{
        printf("%s, %d\n", aCurr->name, aCurr->max_bandwidth);
        if (aCurr->flat_list){
            Flat *fCurr;
            fCurr = aCurr->flat_list;
            while(fCurr){
                printf("     %d, %d, %d\n", fCurr->id, fCurr->initial_bandwidth, fCurr->is_empty);
                if (fCurr->next){
                    if(fCurr->next->prev == fCurr){
                        printf("\t|  |\n"); /* if flats are doubly linked (as intended)*/
                    }
                    else{
                        printf("\t.  .\n"); /* not doubly linked */
                    }
                }
                else
                    printf("\n");
                fCurr = fCurr->next;
            }
        }
        aCurr = aCurr->next;
    }while(aCurr != apt);

    return 0;
}