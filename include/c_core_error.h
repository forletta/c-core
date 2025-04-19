#ifndef C_CORE_ERROR_H
#define C_CORE_ERROR_H

#pragma weak out_of_bounds
#pragma weak malloc_error

_Noreturn void out_of_bounds();
_Noreturn void malloc_error();

#endif // !C_CORE_ERROR_H
