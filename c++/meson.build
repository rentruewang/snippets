project('c++', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'optimization=3', 'c_std=c11', 'cpp_std=c++20'])

tmpl = executable('template', 'template.c++', install : true)
test('basic', tmpl)

uniq = executable('unique', 'unique.c++', install : true)
test('basic', uniq)

so = executable('signed-overflow', 'signed-overflow.c++')
test('basic', so)

init = executable('init-stmt', 'init-stmt.c++')
test('basic', init)

par = executable('parallel', 'parallel.c++')
test('basic', par)

vir = executable('virtual', 'virtual.c++')
test('basic', vir)

cls = executable('classes', 'classes.c++')
test('basic', cls)

subdir('namespace')
