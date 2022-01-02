#ifndef DTYPE_HELPERS
#define DTYPE_HELPERS
struct dyn_arr {
  void ***ref;
  long long size;
  long long index;
  long long data_size;
};
void dyn_arr_init(struct dyn_arr *dyn_arr, void ***ref, long long size, long long data_size);
char dyn_arr_push(struct dyn_arr *dyn_arr, long long data);
#endif