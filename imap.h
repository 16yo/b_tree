#ifndef M_IMAP_H

#define M_IMAP_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct imap_item {
    int64_t id;
    int64_t value;
    struct imap_item* prev;
    struct imap_item* next;
} imap_item;

typedef struct imap {
    imap_item* begin;
    imap_item* back;
    uint64_t size;
} imap;

imap_item* new_imap_item(int64_t id, int64_t value, \
                         const imap_item* prev, const imap_item* next);

imap_item* copy_imap_item(const imap_item* i);

imap create_empty_imap();

int64_t imap_at(const imap* m, int64_t id);

void imap_add(imap* m, int64_t id, int64_t value);

void imap_remove_by_id(imap* m, int64_t id);

void imap_remove_by_value(imap* m, int64_t value);

int8_t is_empty_imap(const imap* m);

int8_t is_valid_edges(const imap* m);

int8_t is_valid(const imap* m);

void make_valid(imap* m);

void clear_imap(imap* m);

void imap_copy(imap* m, const imap* m_);

#define mat(m, id) imap_at((m), (id))

#define log_exception(M, ...)                                             \
{                                                                         \
    fprintf(stderr, "(%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
}

#define exception_exit(M, ...)           \
{                                        \
    log_exception(M, ##__VA_ARGS__);     \
    exit(-1);                            \
}


#endif