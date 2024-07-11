project('muista', 'cpp',
  default_options: [
    'warning_level=2',
    'optimization=2',
    'debug=true',
    'b_lto=true',
    'cpp_std=c++20',
  ]
)

qt6 = import('qt6')
qt6_dep = dependency('qt6', modules: ['Core', 'Gui', 'Quick', 'Qml', 'Sql', 'Test'])

subdir('domain')

muista_inc = domain_inc

subdir('resources')
subdir('tests')
subdir('application')
