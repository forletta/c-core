#ifndef EXT_H
#define EXT_H

typedef void (*FreeFunction)(void *);

typedef struct {
    FreeFunction free;
} ExtInterface;

static const ExtInterface NULL_EXT = {};

#endif // !EXT_H
