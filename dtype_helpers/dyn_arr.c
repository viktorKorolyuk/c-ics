#include <stdlib.h>
#include "dtype_helpers.h"
#include <stdio.h>

// Initialises a dynamic array struct for use with the `dyn_arr_*` functions.
void dyn_arr_init(struct dyn_arr *dyn_arr, void ***ref, long long size, long long data_size)
{
  dyn_arr->ref = ref;
  dyn_arr->size = size;
  dyn_arr->index = 0;
  dyn_arr->data_size = data_size;
}

void dyn_arr_set_size(struct dyn_arr *dyn_arr, long long size)
{
  dyn_arr->size = size;
  *(dyn_arr->ref) = realloc(*(dyn_arr->ref), size * dyn_arr->data_size);
}

/**
 * @brief Push a value to the dynamic array.
 *        The array size is automatically doubled when the limit is reached.
 *        The index after insertion (n+1) is always set to `NULL`.
 * 
 * @param dyn_arr 
 * @param data The data to push. The data must be cast to `long long` however it is intended for any datatype.
 * @return char The status of the push. 1 if the size of the array was increased. Otherwise 0.
 */
char dyn_arr_push(struct dyn_arr *dyn_arr, long long data)
{
  char flag_increase = dyn_arr->index + 2 >= dyn_arr->size;
  if (flag_increase) // Increase the size to allow insertion of two new elements (data + NULL)
    dyn_arr_set_size(dyn_arr, dyn_arr->size * 2);

  (*dyn_arr->ref)[dyn_arr->index] = (void *)data; // Save the data
  (*dyn_arr->ref)[dyn_arr->index + 1] = NULL;     // Clear the next entry
  dyn_arr->index++;
  return flag_increase;
}