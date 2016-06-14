#include "addressbook_list.h"

TelephoneBookList * createTelephoneBookList()
{
    
    TelephoneBookList * newList = malloc(sizeof(struct telephoneBookList));
    return newList;
}

void freeTelephoneBookList(TelephoneBookList* list)
{
    TelephoneBookNode * current = list->head;
    TelephoneBookNode * temp;
    while(current != NULL)
    {
        temp = current->nextNode;
        freeTelephoneBookNode(current);
        current = temp;
        list->size--;
    }
    list->head = NULL;
}

TelephoneBookNode * createTelephoneBookNode()
{
    TelephoneBookNode * newNode = malloc(sizeof(TelephoneBookNode));
    newNode->previousNode = NULL;
    newNode->nextNode = NULL;
    return newNode;
}

void freeTelephoneBookNode(TelephoneBookNode * node)
{
    free(node);


}

Boolean insert(TelephoneBookList * list, TelephoneBookNode * node)
{

    if(list->head == NULL)
    {
        list->head = node;
        list->current = node;
        list->tail = node;
        node->previousNode = NULL;
        node->nextNode = NULL;
    }
    else if(list->current == list->tail)
    {
        node->previousNode = list->tail;
        list->tail->nextNode = node;
        node->nextNode = NULL;
        list->tail = node;
        list->current = list->tail;
    }
    else if (list->current == list->head)
    {
        node->previousNode = NULL;
        node->nextNode = list->head;
        list->head->previousNode = node;
        list->head = node;
        list->current = list->head;
    }
    else{
        node->previousNode = list->current->previousNode;
        list->current->previousNode->nextNode = node;
        node->nextNode = list->current;
        list->current->previousNode = node;
        list->current = node;
    }
    list->size++;
    return TRUE;

}

Boolean forward(TelephoneBookList * list, int forward)
{
    int count;
    if (list->tail->id > list->head->id)
    {
        if (forward > list->tail->id - list->current->id)
        {
            printf("> Unable to move %d nodes forward.\n",forward);
            return FALSE;
        }
        else{
            for (count = 0; count < forward; ++count)
            {
                if (list->current->nextNode == NULL)
                {
                    return FALSE;
                }
                else
                {
                    list->current = list->current->nextNode;
                }
            }
        }
    }
    else if (list->tail->id < list->head->id)
    {
        if (forward > list->current->id - list->tail->id)
        {
            printf("> Unable to move %d nodes forward.\n",forward);
            return FALSE;
        }
        else{
            for (count = 0; count < forward; ++count)
            {
                if (list->current->nextNode == NULL)
                {
                    return FALSE;
                }
                else
                {
                    list->current = list->current->nextNode;
                }
            }
        }
    }
    return TRUE;
}

Boolean backward(TelephoneBookList * list, int backward)
{
    int count;
    if (list->tail->id > list->head->id)
    {
        if (backward > list->current->id - list->head->id)
        {
            printf("> Unable to move %d nodes backward.\n",backward);
            return FALSE;
        }
        else
        {
            for (count = 0; count < backward; ++count)
            {
                if (list->current->previousNode == NULL)
                {
                    return FALSE;
                }
                else
                {
                    list->current = list->current->previousNode;
                }
            }
        }
    }
    else if (list->tail->id < list->head->id)
    {
        if (backward > list->head->id - list->current->id)
        {
            printf("> Unable to move %d nodes backward.\n",backward);
            return FALSE;
        }
        else
        {
            for (count = 0; count < backward; ++count)
            {
                if (list->current->previousNode == NULL)
                {
                    return FALSE;
                }
                else
                {
                    list->current = list->current->previousNode;
                }
            }
        }
    }
    return TRUE;
}

Boolean delete(TelephoneBookList * list)
{
    TelephoneBookNode * temp;

    if(list->current == list->tail){
        temp = list->current->previousNode;
        temp->nextNode = NULL;
        temp->previousNode = list->current->previousNode->previousNode;
       freeTelephoneBookNode(list->tail);
        list->tail = temp;
        list->current = list->tail;
    }else if(list->current == list->head){
        temp = list->head->nextNode;
        temp->previousNode = NULL;
        temp->nextNode = list->head->nextNode->nextNode;
        freeTelephoneBookNode(list->head);
        list->current = temp;
        list->head = temp;
    }else if(list->current->previousNode != NULL){
        temp = list->current->previousNode; 
        temp->nextNode = list->current->nextNode;
        freeTelephoneBookNode(list->current);
        list->current = temp;
    }
    list->size--;
    return TRUE;
}

TelephoneBookNode * findByID(TelephoneBookList * list, int id)
{

    TelephoneBookNode * current = list->head;
    while( current != NULL)
    {
        if (current->id == id)
        {
               return current;
        }

        current = current->nextNode;
    }
    return current;
}

TelephoneBookNode * findByName(TelephoneBookList * list, char * name)
{
    TelephoneBookNode * current = list->head;
    while( current != NULL)
    {
        if (strcmp(current->name,name) == 0)
        {
            printf("Found: %s with ID - %d\n",current->name,current->id);
            return current;
        }

        current = current->nextNode;
    }
    return current;
}
