#include <stdio.h>
#include "easy_conf.h"

int main() {
    // Carica la configurazione dal file
    node_list config = read_config("settings.conf");

    // Stampa l'intera lista di configurazione
    config.print_list(&config);

    // Recupera e stampa il valore associato a "username"
    const char* val = config.get_setting(&config, "username");
    if (val) {
        printf("username: %s\n", val);
    } else {
        printf("Setting 'username' not found.\n");
    }

    // Recupera e stampa il valore associato a "password"
    val = config.get_setting(&config, "password");
    if (val) {
        printf("password: %s\n", val);
    } else {
        printf("Setting 'password' not found.\n");
    }

    // Libera la memoria
    config.free_list(&config);
    return 0;
}

// compile with : gcc example.c -leasy_conf -o example