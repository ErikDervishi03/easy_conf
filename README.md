# easy_conf

A simple, lightweight C library for parsing configuration files into a linked list structure.

## Features

- Easy integration
- Minimal dependencies (pure C)
- Function-pointer-based interface for flexibility
- Suitable for small to medium-sized projects

---

## How to Use

You can use `easy_conf` in **two ways**:

### 1. Manual Include (without installing)

Copy the following files into your project:

```
easy_conf.c
utility.c
easy_conf.h
```

Then in your code:

```c
#include "easy_conf.h"
```

Compile using:

```bash
gcc your_program.c easy_conf.c utility.c -o your_program
```

---

### 2. Install & Use System-Wide

Install with:

```bash
make
sudo make install
```

Then in your code:

```c
#include <easy_conf.h>
```

Compile using:

```bash
gcc your_program.c -leasy_conf -o your_program
```

This works because the header and static library are installed to:

- `/usr/local/include/easy_conf.h`
- `/usr/local/lib/libeasy_conf.a`

---

### 3. Example Usage

```c
#include <stdio.h>
#include "easy_conf.h"

int main() {
    node_list config = read_config("settings.conf");
    config.print_list(&config);

    const char* db_host = config.get_setting(&config, "host");
    if (db_host) {
        printf("DB host: %s\n", db_host);
    }

    config.free_list(&config);
    return 0;
}
```

---

## Example `settings.conf`

```
host=localhost
port=5432
debug=true
```

---

## Functions Overview

After calling `read_config("filename.cfg")`, you get a `node_list` structure with these functions:

- `add_rule(&list, "key", "value");`
- `delete_rule(&list, "key");`
- `get_setting(&list, "key");`
- `print_list(&list);`
- `change_setting(&list, "key", "new_value");`
- `free_list(&list);`

---

## License

MIT License
