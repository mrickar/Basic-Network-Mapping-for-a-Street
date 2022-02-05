#include <stdio.h>
#include <stdlib.h>
#include "the3.h"
#define NEXT(x) (x)->next
#define PREV(x) (x)->prev
/*APARTMENT*/
#define NAME(x) (x)->name
#define MBAND(x) (x)->max_bandwidth
#define FLIST(x) (x)->flat_list
/*FLAT*/
#define ID(x) (x)->id
#define IBAND(x) (x)->initial_bandwidth
#define EMPTY(x) (x)->is_empty

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)
int compare_name(char *name1, char *name2)
{
    int i = 0;
    while (1)
    {
        if (name1[i] == '\0' && name2[i] == '\0')
        {
            return 1;
        }

        if (name1[i] != name2[i])
        {
            return 0;
        }

        i++;
    }
}
Apartment *add_apartment(Apartment *head, int index, char *apartment_name, int max_bandwidth)
{
    Apartment *new_ap = malloc(sizeof(Apartment));
    Apartment *tmp_head = head;
    int i;
    NAME(new_ap) = apartment_name;
    MBAND(new_ap) = max_bandwidth;
    FLIST(new_ap) = NULL;
    NEXT(new_ap) = NULL;
    if (head == NULL)
    {
        NEXT(new_ap) = new_ap;
        return new_ap;
    }
    if (index == 0)
    {
        NEXT(new_ap) = head;
        while (NEXT(tmp_head) != NEXT(new_ap))
        {
            tmp_head = NEXT(tmp_head);
        }
        NEXT(tmp_head) = new_ap;
        return new_ap;
    }
    for (i = 0; i < index - 1; i++)
    {
        tmp_head = NEXT(tmp_head);
    }
    NEXT(new_ap) = NEXT(tmp_head);
    NEXT(tmp_head) = new_ap;

    return head;
}
void add_flat(Apartment *head, char *apartment_name, int index, int flat_id, int initial_bandwidth)
{
    Apartment *tmp_head = head;
    Flat *firstF;
    int mx_band, i;
    Flat *new_fl = malloc(sizeof(Flat));
    while (!compare_name(NAME(tmp_head), apartment_name))
    {
        tmp_head = NEXT(tmp_head);
    }
    mx_band = MBAND(tmp_head);
    firstF = FLIST(tmp_head);
    while (firstF != NULL)
    {
        mx_band -= IBAND(firstF);
        firstF = NEXT(firstF);
    }

    firstF = FLIST(tmp_head);
    mx_band = MAX(0, mx_band);
    IBAND(new_fl) = MIN(initial_bandwidth, mx_band);
    ID(new_fl) = flat_id;
    NEXT(new_fl) = NULL;
    PREV(new_fl) = NULL;
    EMPTY(new_fl) = 0;

    if (firstF == NULL)
    {
        FLIST(tmp_head) = new_fl;
        return;
    }
    if (index == 0)
    {

        NEXT(new_fl) = FLIST(tmp_head);
        FLIST(tmp_head) = new_fl;
        PREV(NEXT(new_fl)) = new_fl;
        return;
    }

    for (i = 0; i < index - 1; i++)
    {
        firstF = NEXT(firstF);
    }
    NEXT(new_fl) = NEXT(firstF);
    NEXT(firstF) = new_fl;
    PREV(new_fl) = firstF;
    if (NEXT(new_fl))
    {
        PREV(NEXT(new_fl)) = new_fl;
    }

    return;
}
void clrFl(Flat *tmpF)
{
    if (tmpF == NULL)
    {
        return;
    }
    clrFl(NEXT(tmpF));
    free(tmpF);
}
Apartment *remove_apartment(Apartment *head, char *apartment_name)
{
    Apartment *tmp_head = head, *tmpA;
    Flat *tmpF;
    int nl = 0;
    if (tmp_head == NEXT(tmp_head))
    {
        nl = 1;
    }
    if (compare_name(NAME(head), apartment_name))
    {
        head = NEXT(head);
    }
    if (!nl)
    {
        while (!compare_name(NAME(NEXT(tmp_head)), apartment_name))
        {
            tmp_head = NEXT(tmp_head);
        }
    }
    tmpF = FLIST(NEXT(tmp_head));
    clrFl(tmpF);
    tmpA = NEXT(tmp_head);
    NEXT(tmp_head) = NEXT(tmpA);
    free(tmpA);
    if (nl)
    {
        return NULL;
    }
    return head;
}
void make_flat_empty(Apartment *head, char *apartment_name, int flat_id)
{
    Apartment *tmp_head = head;
    Flat *tmpF;
    while (!compare_name(NAME(tmp_head), apartment_name))
    {
        tmp_head = NEXT(tmp_head);
    }
    tmpF = FLIST(tmp_head);
    while (ID(tmpF) != flat_id)
    {
        tmpF = NEXT(tmpF);
    }
    EMPTY(tmpF) = 1;
    IBAND(tmpF) = 0;
    return;
}
int find_sum_of_max_bandwidths(Apartment *head)
{
    Apartment *tmp_head = head;
    int sum = 0;
    if (tmp_head == NULL)
    {
        return 0;
    }
    sum += MBAND(tmp_head);
    tmp_head = NEXT(tmp_head);
    while (tmp_head != head)
    {
        sum += MBAND(tmp_head);
        tmp_head = NEXT(tmp_head);
    }
    return sum;
}
Apartment *merge_two_apartments(Apartment *head, char *apartment_name_1, char *apartment_name_2)
{
    Apartment *tmp_head = head, *ap1, *ap2;
    Flat *fl1, *fl2;
    int found = 0;
    if (compare_name(NAME(head), apartment_name_2))
    {
        head = NEXT(head);
    }
    while (found != 3)
    {
        if (found != 1 && compare_name(NAME(tmp_head), apartment_name_1))
        {
            ap1 = tmp_head;
            found += 1;
        }
        if (found != 2 && compare_name(NAME(NEXT(tmp_head)), apartment_name_2))
        {
            ap2 = tmp_head;
            found += 2;
        }
        tmp_head = NEXT(tmp_head);
    }

    MBAND(ap1) += MBAND(NEXT(ap2));
    fl1 = FLIST(ap1);
    fl2 = FLIST(NEXT(ap2));

    while (fl1 && NEXT(fl1))
    {
        fl1 = NEXT(fl1);
    }
    if (fl1)
    {
        NEXT(fl1) = fl2;
        if (fl2)
        {
            PREV(fl2) = fl1;
        }
    }
    else
    {
        FLIST(ap1) = fl2;
    }
    tmp_head = NEXT(ap2);
    FLIST(tmp_head) = NULL;
    NEXT(ap2) = NEXT(tmp_head);
    free(tmp_head);
    return head;
}
Flat *find_flat_id(Flat *tmpFl, Apartment **tmpAp, int id)
{
    if (!tmpFl)
    {
        *tmpAp = NEXT(*tmpAp);
        return find_flat_id(FLIST(*tmpAp), tmpAp, id);
    }
    else
    {
        if (ID(tmpFl) == id)
        {
            return tmpFl;
        }
        else
        {
            return find_flat_id(NEXT(tmpFl), tmpAp, id);
        }
    }
}
void relocate_flats_to_same_apartment(Apartment *head, char *new_apartment_name, int flat_id_to_shift, int *flat_id_list)
{
    Apartment *tmpAP = head, *newAP;
    Flat *tmpFL, *shiftFL;
    int i;
    while (!compare_name(NAME(tmpAP), new_apartment_name))
    {
        tmpAP = NEXT(tmpAP);
    }
    newAP = tmpAP;
    shiftFL = find_flat_id(FLIST(newAP), &newAP, flat_id_to_shift);
    tmpAP = head;
    for (i = 0; flat_id_list[i] != '\0'; i++)
    {

        tmpFL = find_flat_id(FLIST(tmpAP), &tmpAP, flat_id_list[i]);
        if (!PREV(tmpFL))
        {
            FLIST(tmpAP) = NEXT(tmpFL);
            if (NEXT(tmpFL))
            {
                PREV(NEXT(tmpFL)) = NULL;
            }
        }
        else
        {
            NEXT(PREV(tmpFL)) = NEXT(tmpFL);
            if (NEXT(tmpFL))
            {
                PREV(NEXT(tmpFL)) = PREV(tmpFL);
            }
        }
        MBAND(tmpAP) -= IBAND(tmpFL);
        MBAND(newAP) += IBAND(tmpFL);
        if (!PREV(shiftFL))
        {
            NEXT(tmpFL) = FLIST(newAP);
            FLIST(newAP) = tmpFL;
            PREV(tmpFL) = NULL;
            if (NEXT(tmpFL))
            {
                PREV(NEXT(tmpFL)) = tmpFL;
            }
        }
        else
        {
            NEXT(tmpFL) = shiftFL;
            PREV(tmpFL) = PREV(shiftFL);
            PREV(shiftFL) = tmpFL;
            NEXT(PREV(tmpFL)) = tmpFL;
        }
    }
}