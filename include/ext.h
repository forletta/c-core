#ifndef EXT_H
#define EXT_H

typedef void (*FreeFunction)(void *);

typedef struct {
    FreeFunction free;
} ExtInterface;

static const ExtInterface EXT_NULL = {};

#endif // !EXT_H
