sources = files(
    'main.cpp',
    'application.cpp',
)

muista_moc = qt6.compile_moc( 
  headers: ['../include/application.hpp' ],
  dependencies: qt6_dep)

executable(
  'muista',
  sources, resources, muista_moc,
  include_directories: muista_inc,
  link_with: [lib_commons],
  dependencies: [qt6_dep],
  install: true,
)
