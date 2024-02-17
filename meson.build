project('muista', 'cpp',
  default_options: [
    'warning_level=2',
    'optimization=2',
    'buildtype=release',
    'debug=true',
    'cpp_std=c++20',
  ]
)

qt6 = import('qt6')
qt6_dep = dependency('qt6', modules: ['Core', 'Gui', 'Widgets', 'Sql'])

muista_inc = include_directories('include')

subdir('common')
subdir('widgets')
subdir('dialogs')
subdir('screens')
subdir('muista')
