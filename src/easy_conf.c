// rule_list.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../easy_conf.h"
#include "utility.c"

// Node structure for the linked list
typedef struct Node {
    rule data;
    struct Node* next;
} Node;

// Utility: Create a new node
static Node* create_node(const char* setting, const char* value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strncpy(new_node->data.setting, setting, sizeof(new_node->data.setting) - 1);
    new_node->data.setting[sizeof(new_node->data.setting) - 1] = '\0';

    strncpy(new_node->data.value, value, sizeof(new_node->data.value) - 1);
    new_node->data.value[sizeof(new_node->data.value) - 1] = '\0';

    new_node->next = NULL;
    return new_node;
}

// Add a rule at the end of the list
static void add_rule(node_list* list, const char* setting, const char* value) {
    Node* new_node = create_node(setting, value);
    if (list->head == NULL) {
        list->head = new_node;
        return;
    }
    Node* temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

// Delete a node by setting
static void delete_rule(node_list* list, const char* setting) {
    Node* temp = list->head;
    Node* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->data.setting, setting) == 0) {
            if (prev == NULL) {
                list->head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Setting \"%s\" not found\n", setting);
}

// Get the value associated with a setting
static const char* get_setting(node_list* list, const char* setting) {
    Node* temp = list->head;
    while (temp != NULL) {
        if (strcmp(temp->data.setting, setting) == 0) {
            return temp->data.value;
        }
        temp = temp->next;
    }
    return NULL;
}

// Change the value of an existing setting
static void change_setting(node_list* list, const char* setting, const char* new_value) {
    Node* temp = list->head;
    while (temp != NULL) {
        if (strcmp(temp->data.setting, setting) == 0) {
            strncpy(temp->data.value, new_value, sizeof(temp->data.value) - 1);
            temp->data.value[sizeof(temp->data.value) - 1] = '\0';
            return;
        }
        temp = temp->next;
    }
    printf("Setting \"%s\" not found\n", setting);
}

// Print the entire list
static void print_list(node_list* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("[%s: %s] -> ", temp->data.setting, temp->data.value);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Free the entire list
static void free_list(node_list* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

// Initialize the list and assign function pointers
void init_list(node_list* list) {
    list->head = NULL;
    list->add_rule = add_rule;
    list->delete_rule = delete_rule;
    list->get_setting = get_setting;
    list->print_list = print_list;
    list->change_setting = change_setting;
    list->free_list = free_list;
}

node_list read_config(char * file_name){
    node_list list;

    FILE* file = fopen(file_name, "r");

    // Buffer to store each line of the file.
    char line[100];

    // Check if the file was opened successfully.
    if (file != NULL) {
        
        init_list(&list);
        char rule[50];
        char setting[50];
        int line_count = 1;
        // Read each line from the file and store it in the
        // 'line' buffer.
        while (fgets(line, sizeof(line), file)) {
            int error = parse_string(line, rule, setting);

            if(error){
              fprintf(stderr, "config file error at line : %d\n", line_count);
              break;
            }

            strcpy(setting, trimwhitespace(setting));
            strcpy(rule, trimwhitespace(rule));

            list.add_rule(&list, rule, setting);

            memset(rule,0,sizeof(rule));
            memset(setting,0,sizeof(setting));
        }

        // Close the file stream once all lines have been
        // read.
        fclose(file);
    }
    else {
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        fprintf(stderr, "Unable to open file!\n");
    }
    return list;
}


