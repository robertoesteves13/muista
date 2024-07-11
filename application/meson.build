sources = files(
    'main.cpp',
    'application.cpp',
    'models/course_list.cpp',
)

muista_moc = qt6.compile_moc( 
  headers: ['./include/application.hpp', './include/models/course_list.hpp' ],
  dependencies: qt6_dep)

executable(
  'muista',
  sources, resources, muista_moc,
  include_directories: [muista_inc, './include'],
  link_with: [lib_domain],
  dependencies: [qt6_dep],
  install: true,
)
