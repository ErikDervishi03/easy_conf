// rule_list.h
#ifndef RULE_LIST_H
#define RULE_LIST_H

// Rule structure
typedef struct {
    char setting[50];
    char value[50];
} rule;

// Forward declaration of node_list for function pointers
typedef struct node_list node_list;

// Function pointer typedefs
typedef void (*add_rule_func)(node_list*, const char*, const char*);
typedef void (*delete_rule_func)(node_list*, const char*);
typedef const char* (*get_setting_func)(node_list*, const char*);
typedef void (*print_list_func)(node_list*);
typedef void (*change_setting_func)(node_list*, const char*, const char*);
typedef void (*free_list_func)(node_list*);

// List structure with function pointers
struct node_list {
    void* head;

    add_rule_func add_rule;
    delete_rule_func delete_rule;
    get_setting_func get_setting;
    print_list_func print_list;
    change_setting_func change_setting;
    free_list_func free_list;
};

// Initialization function
void init_list(node_list* list);

node_list read_config(char * file_name);

#endif // RULE_LIST_H
