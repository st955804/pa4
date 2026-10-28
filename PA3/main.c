/* COP3502C PA3 
This program is written by: Stuart Palmer */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Monster {
    char name[51];
    char element[31];
    int level;
    int hp;
} Monster;

typedef struct Node {
    Monster* monster;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* back;
    int size;
} Queue;

typedef struct WillsPC {
    Queue* storageBox; // FIFO Queue for Will's PC Storage Box
    Node* activeRosterHead; //Singly Linked List for sorted active roster
} WillsPC;


Queue * createQueue(void){
    Queue * empty_queue = malloc(sizeof(Queue));
    empty_queue->front = NULL;
    empty_queue->back = NULL;
    empty_queue->size = 0;
    return empty_queue;
}

void enqueue(Queue * q, Monster * m){
    
    Node * new_monster_node = malloc(sizeof(Node));
    if(new_monster_node == NULL){
        return;
    }
    
    new_monster_node->next = NULL;

    new_monster_node->monster = m;
    // If queue is empty
    if (q->front == NULL){
        q->front = new_monster_node;
        q->back = new_monster_node;
    }
    else{
        // Otherwise put it at back of queue
        q->back->next = new_monster_node;
        // And update back to be the new last node
        q->back = new_monster_node;
    }
    // Increment q->size as we have added a new node
    q->size++;
}

Monster * dequeue(Queue * q){
    // Queue is FIFO -  remove first node

    // Only dequeues if there is something to pull out
    if(q->front == NULL){
        return NULL;
    }
    Node * temp = q->front;
    Monster * monsterPtr = temp->monster;
    // Removes the front node from q 
    q->front = q->front->next;
    q->size--;
        // Frees the unlinked Node container
    free(temp);

       // Updates q back to null if q becomes empty
   if(q ->size == 0){
        q->front = NULL;
        q->back = NULL;
    }
    return monsterPtr;
}

Node * insertRosterSorted(Node * head, Monster * m){

    Node * newNode = malloc(sizeof(Node));
    newNode->monster = m;
    newNode->next = NULL;

    Node * temp = head;

    // If list is empty
    if (temp == NULL){
        head = newNode;
        return head;
    } 
    while(temp != NULL){
        
        // Prevents out of bounds access
        if(m->level > head->monster->level){
            newNode->next = head;
            head = newNode;
            return head;
        }
        if(m->level == head->monster->level){
            if(head->monster->hp < m->hp){
                newNode->next = head;
                head = newNode;
                
                return head;
            }
        }
        if(temp->next == NULL){
            temp->next = newNode;
            return head;
        }
        if(temp->next->monster->level < m->level){
            newNode->next = temp->next;
            temp->next = newNode;
            return head;
        }
        // If the next monster has the same level as m
        else if(temp->next->monster->level == m->level){
            // and temp ->next->monster's hp is less
            if(temp->next->monster->hp < m->hp){
                // This used to save the temp->next node
                Node * node = temp->next;
                temp->next = newNode;
                temp->next->next = node;
                return head;
            }
        }
        temp = temp->next;
    }
    return head;
}

Node * depositBackToPC(Node * head, Queue * q, const char* monsterName){
    Node * temp = head;
    Monster * monsterPtr;
    Node * removeNode;
    if (head == NULL){
        printf("[ERROR] %s is not in the Active Roster.\n", monsterName);        return head;
    }

    while(temp){
        // For if the matching monster is the head
        if(strcmp(head->monster->name, monsterName) == 0){
            removeNode = head;
            monsterPtr = removeNode->monster;
            head = head->next;
            enqueue(q, monsterPtr);
            free(removeNode);
            // same print as below for success
            printf("[EVENT] Returned %s from Active Roster back to Will's PC.\n", monsterName);
            return head;
        }

        if(temp->next == NULL){
            // prints the error line 
            printf("[ERROR] %s is not in the Active Roster.\n", monsterName);
            
            return head;
            
        }
        // Searches the active roster for the first node matching monsterName
        if(strcmp(temp->next->monster->name, monsterName) == 0){
            // Unlinks the node
            removeNode = temp->next;
            
            monsterPtr = removeNode->monster;
            temp->next = temp->next->next;
            enqueue(q, monsterPtr);
            //
            free(removeNode);
        
            //if successful prints event line 
            printf("[EVENT] Returned %s from Active Roster back to Will's PC.\n", monsterName);
            return head;
        }
        temp = temp->next;
    }
    return head;
}

// Similar to lab 6
Node *releaseFainted(Node *head, int minHp, int *releasedCount) {
    if (head == NULL) {
        return NULL;
    }
    // Recursively check the list and attach it to head
    head->next = releaseFainted(head->next, minHp, releasedCount);
    // If the current monster's hp is too low, move head to next and 
    if (head->monster->hp < minHp) {
        Node *temp = head;
        head = head->next;
        // free it
        free(temp->monster);
        free(temp);
        // Increment counter
        (*releasedCount)++;
    }
    return head;
}

// Made this to print the roster using a node * 
void printRoster(Node * head){
    if(head == NULL){
        return;
    }
    if (head->next == NULL){
        printf("%s [Lv: %d]", head->monster->name, head->monster->level);
    }
    else{
    printf("%s [Lv: %d] -> ", head->monster->name, head->monster->level);
    }
    printRoster(head->next);
}

// Made this to print the queue, as it queue does not have a head
void printQueue(Node * curr){
    if (curr == NULL){
        return;
    }
    if(curr->next == NULL){
        printf("%s [Lv: %d]", curr->monster->name, curr->monster->level);
    }
    else{
        printf("%s [Lv: %d] -> ", curr->monster->name, curr->monster->level);
    }
    printQueue(curr->next);
}



void displayStorage(WillsPC * pc){
    int count = 0;
    Node * curr = pc->activeRosterHead;

    while(curr != NULL){
        count++;
        curr=curr->next;
    }
    printf("--- WILL'S PC STATUS ---\n");
    // If storageVox is empty
    if(pc->storageBox->size == 0){
        printf("Storage Box Queue (%d): EMPTY", pc->storageBox->size);
    }
    // Use printQueue function to print 
    else{
        printf("Storage Box Queue (%d): ", pc->storageBox->size);
         printQueue(pc->storageBox->front);
    }
    // If roster is empty
    printf("\n");
    if(pc->activeRosterHead == NULL){
        printf("Active Roster (%d): EMPTY", count);
        printf("\n------------------------");
    }
    // Use printRoster and pass the pc's activeRosterHead
    else{
        printf("Active Roster (%d): ", count);
        printRoster(pc->activeRosterHead);
        printf("\n------------------------");
    }
    printf("\n");
}    

WillsPC * createWillsPC(void){
    WillsPC * pc = malloc(sizeof(WillsPC));
    pc->storageBox = createQueue();
    pc->activeRosterHead = NULL;
    return pc;
}

void releaseWillsPC(WillsPC * pc){
    // Since dequeue removes node, frees node, and returns monster *
    // I have to free each monster *
    // While the queue has things in it 
    while(pc->storageBox->size != 0){
    Monster * temp  = dequeue(pc->storageBox);
    free(temp);
    }
    free(pc->storageBox);

    Node * curr = pc->activeRosterHead;
    // Freeing the linked list
    while(curr != NULL){
        Node * next = curr->next;
        free(curr->monster);
        free(curr);
        curr = next;
    }
    free(pc);
}

int main (void){
    WillsPC * pc = createWillsPC();
    // Declared 50 because assignment had no specific
    char command[50];
    scanf("%49s", command);

    while(1){
        // if the input is DEPOSIT_PC
        if(strcmp(command, "DEPOSIT_PC") == 0){
            Monster * monsterPtr = malloc(sizeof(Monster));
            scanf("%50s %30s %d %d", monsterPtr->name, monsterPtr->element,
                 &monsterPtr->level, &monsterPtr->hp);
            enqueue(pc->storageBox, monsterPtr);
            printf("[EVENT] Deposited to Will's PC: %s (%s, Lv: %d, HP: %d)\n", 
                monsterPtr->name,
                 monsterPtr->element, monsterPtr->level, monsterPtr->hp);
        }

        if(strcmp(command, "WITHDRAW_PARTY") == 0){
            int count;
            int withdrawn = 0;
            scanf("%d", &count);
            while(withdrawn < count && pc->storageBox->size > 0){
                // Takes the monster out of queue
                Monster * monsterPtr =  dequeue(pc->storageBox);
                // Put it in party
                pc->activeRosterHead = insertRosterSorted(pc->activeRosterHead, monsterPtr);
                withdrawn++;
            }
            printf("[EVENT] Withdrew %d monster(s) from Will's PC to Active Roster.\n", withdrawn);
        }
            
        if(strcmp(command, "DEPOSIT_BACK") == 0){
            char monsterName[51];
            scanf("%50s", monsterName);
            // Saving potentially updated activeRosterHead
            pc->activeRosterHead = depositBackToPC(pc->activeRosterHead, pc->storageBox, monsterName);
        }

        if(strcmp(command, "RELEASE_FAINTED") == 0){
            int minHP;
            int releasedCount = 0;
            scanf("%d", &minHP);
            // Releases monsters and updates the roster head, and prints the number of monsters released.
            pc->activeRosterHead = releaseFainted(pc->activeRosterHead, minHP, &releasedCount);
            printf("[EVENT] Released %d fainted monster(s) with HP below %d.\n", releasedCount, minHP);
        }
        // Display storage using function with pc as arg
        if(strcmp(command, "DISPLAY_STORAGE") == 0){
            displayStorage(pc);
        }
        // Simple print
        if(strcmp(command, "LOGOFF_PC") == 0){
            printf("[EVENT] Logged off Will's PC.");
            // To exit loop
            break;
        }
        // Reads new command and compares that in the while
        scanf("%49s", command);
    }
    // Frees the memory
    releaseWillsPC(pc);
    return 0;
}