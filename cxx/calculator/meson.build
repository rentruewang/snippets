fmt_proj = subproject('fmt')
fmt_dep = fmt_proj.get_variable('fmt_dep')

calculator = executable('calculator', ['main.cxx', 'calculator.cxx'], dependencies: [fmt_dep])
test('basic', calculator)
