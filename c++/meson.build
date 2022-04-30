project('c++', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

tmpl = executable('template', 'template.c++', install : true)

test('basic', tmpl)

uniq = executable('unique', 'unique.c++', install : true)

test('basic', uniq)
