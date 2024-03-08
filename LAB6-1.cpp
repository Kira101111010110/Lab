#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct studentNode {
    char name[20];
    int age;
    char sex;
    float gpa;
    struct studentNode *next;
    struct studentNode *back;
};

struct studentNode *AddNode(struct studentNode **start, const char *name, int age, char sex, float gpa) {
    struct studentNode *newNode = (struct studentNode *)malloc(sizeof(struct studentNode));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0'; // Ensure null-terminated string
    newNode->age = age;
    newNode->sex = sex;
    newNode->gpa = gpa;
    newNode->next = NULL;
    newNode->back = NULL;

    if (*start == NULL) {
        *start = newNode;
    } else {
        struct studentNode *current = *start;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->back = current;
    }

    return newNode;
}

void InsNode(struct studentNode *now, const char *name, int age, char sex, float gpa) {
    if (now == NULL) {
        return; // Handle the case when 'now' is NULL
    }

    struct studentNode *newNode = (struct studentNode *)malloc(sizeof(struct studentNode));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0'; // Ensure null-terminated string
    newNode->age = age;
    newNode->sex = sex;
    newNode->gpa = gpa;
    newNode->next = now;
    newNode->back = now->back;

    if (now->back != NULL) {
        now->back->next = newNode;
    }

    now->back = newNode;
}

void DelNode(struct studentNode **now) {
    if (*now == NULL) {
        return; // Handle the case when 'now' is NULL
    }

    struct studentNode *temp = *now;

    if ((*now)->next != NULL) {
        (*now)->next->back = (*now)->back;
    }

    if ((*now)->back != NULL) {
        (*now)->back->next = (*now)->next;
        *now = (*now)->next;
    } else {
        *now = (*now)->next;
    }

    free(temp);
}

void GoBack(struct studentNode **now) {
    if (*now != NULL && (*now)->back != NULL) {
        *now = (*now)->back;
    }
}

void ShowAll(struct studentNode *walk) {
    while (walk != NULL) {
        printf("%s ", walk->name);
        walk = walk->next;
    }
    printf("\n");
}

int main() {
    struct studentNode *start, *now;
    start = NULL;
    now = AddNode(&start, "one", 6, 'M', 3.11);
    ShowAll(start);
    now = AddNode(&start, "two", 8, 'F', 3.22);
    ShowAll(start);
    InsNode(now, "three", 10, 'M', 3.33);
    ShowAll(start);
    InsNode(now, "four", 12, 'F', 3.44);
    ShowAll(start);
    GoBack(&now);
    DelNode(&now);
    ShowAll(start);
    DelNode(&now);
    ShowAll(start);
    DelNode(&now);
    ShowAll(start);

    return 0;
}