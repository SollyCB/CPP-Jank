struct component {
  const char *name;
  const char *value;
};

struct component_table {
  union {
    struct {
      // I would like to use std::string over char*, but then initializing this
      // structure becomes awkward, because the compiler complains about use of
      // a deleted function. Plus, since I am only going to be printing these,
      // not manipulating them, I do not really get a benefit from using
      // std::string.
      struct component scheme = {.name = "scheme"};
      struct component path   = {.name = "path"};
      struct component auth   = {.name = "authority"};
      struct component query  = {.name = "query"};
      struct component frag   = {.name = "fragment"};
    };
    struct component array[5];
  };
};

// Why does the '::' notation not work for std::size, but it does for sizeof?
// constexpr int COMPONENT_COUNT size(component_table::array)
//
// This is not allowed because it is apparently not constant, but it is constant if you use sizeof
// constexpr int COMPONENT_COUNT = size(((component_table*)0)->array);
// and this -
// int arr[5] = {};
// int brr[size(arr)] = {};
// is constant
//
// This is basically just the C way.
// constexpr int COMPONENT_COUNT = (sizeof(component_table::array)/sizeof(component_table::array[0]));
//
// I do not know which of the above is preferable, or if there is actually a nice way.
