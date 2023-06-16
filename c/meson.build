project('c', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'optimization=3', 'c_std=c11', 'cpp_std=c++17'])

main = executable('main', 'main.c')
test('basic', main)

copy = executable('copy', 'copy.c')
test('basic', copy)

radixsort = executable('radix-sort', 'radix-sort.c')
test('basic', radixsort)

sorter = executable('sorter', 'sorter.c')
test('basic', sorter)
