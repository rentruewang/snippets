project('c++', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'optimization=3', 'c_std=c11', 'cpp_std=c++20'])

tmpl = executable('template', 'template.cxx', install : true)
test('basic', tmpl)

uniq = executable('unique', 'unique.cxx', install : true)
test('basic', uniq)

so = executable('signed-overflow', 'signed-overflow.cxx')
test('basic', so)

init = executable('init-stmt', 'init-stmt.cxx')
test('basic', init)

par = executable('parallel', 'parallel.cxx')
test('basic', par)

vir = executable('virtual', 'virtual.cxx')
test('basic', vir)

cls = executable('classes', 'classes.cxx')
test('basic', cls)

ctor = executable('ctor', 'ctor.cxx')
test('basic', ctor)

subdir('namespace')
