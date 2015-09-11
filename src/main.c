#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include "array.h"

typedef int bool;
#define true 1
#define false 0

struct {
    json_t *root;
    const char *json_path;
    array_s instructions;
    bool updated;
    bool verbose;
} settings;

void init_settings() {
    array_init(&settings.instructions, 8);
    settings.updated = false;
    settings.verbose = true; // debug
}

typedef struct {
    const char *name;
    const char *operation;
    void *params;
} command_s;

typedef struct {
    const char *command;
    void *args;
} instruction_s;

typedef struct {
    const char *value;
    int amount;
} increment_args_s;

typedef struct {
    const char *full;
    int full_length;
    char value[64];
    int start;
    int end;
} json_path;

const char *json_path_next(json_path *self) {
    int i;
    self->start = self->end + 1;

    if (self->start >= self->full_length)
        return 0;

    bool found = false;
    for (i = self->start; i < self->full_length; i++) {
        if (self->full[i] == '/') {
            self->end = i;
            found = true;
            break;
        }
    }

    if (found == false) {
        self->end = self->full_length;
    }

    printf("Path start: %i end: %i found: %i\n", self->start, self->end, found);

    int length = self->end - self->start;
    memcpy(self->value, self->full + self->start, self->end - self->start);
    self->value[length] = 0;
    if (settings.verbose) {
        printf("Path iterated: %s", self->value);
    }

    return self->value;
}

const char *json_path_begin(json_path *self, const char *value) {
    memset(self, 0, sizeof(json_path));
    self->full = value;
    self->full_length = strlen(value);
    self->start = 0;
    self->end = -1;
    return json_path_next(self);
}


json_t *json_get_by_path(json_t *root, const char *path) {
    json_path iterator;
    const char *key = json_path_begin(&iterator, path);
    json_t *obj = root;
    while (key && obj) {
        obj = json_object_get(obj, key);
        key = json_path_next(&iterator);
    }

    return obj;
}

void json_path_test() {
    json_path p;

    const char *key = json_path_begin(&p, "targets/versionbump/build");
    while (key) {
        printf("Path: %s\n", key);
        key = json_path_next(&p);
    }
}

int exec_command_increment(json_t *root, increment_args_s *args) {
    // targets/versionbump/build
}

int main(int argc, char **argv) {
    json_path_test();

    return 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <config.json> [--increment target/value amount]\n", argv[0]);
        return 1;
    }

    int i;

    init_settings();
    settings.json_path = argv[1];

    for (i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--increment") == 0) {
            instruction_s *is = malloc(sizeof(command_s));
            increment_args_s *ni = malloc(sizeof(increment_args_s));
            is->command = "increment";
            is->args = ni;
            ni->value = argv[i + 1];
            ni->amount = atoi(argv[i + 2]);
            array_add(&settings.instructions, is);
            if (settings.verbose == true) {
                printf("Increment %s by %i\n", ni->value, ni->amount);
            }
            i++;
            continue;
        }
    }

    printf("Loading: %s\n", argv[1]);

    //char *json_text = load_file(argv[1]);
    json_error_t error;
    json_t *root = json_load_file(argv[1], 0, &error); //json_loads(json_text, 0, &error);
    settings.root = root;

    if (!root) {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return 1;
    }

    if (!json_is_object(root)) {
        fprintf(stderr, "error: root is not an object\n");
        json_decref(root);
        return 1;
    }

    json_t *targets = json_object_get(root, "targets");
    if (!targets) {
        fprintf(stderr, "error: 'target' not found\n");
        json_decref(root);
        return 1;
    }

    const char *key;
    json_t *value;

    void *iter = json_object_iter(targets);
    while (iter) {
        key = json_object_iter_key(iter);
        value = json_object_iter_value(iter);

        printf("%s\n", key);


        iter = json_object_iter_next(targets, iter);
    }

    return 0;
}