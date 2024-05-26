tests_moc = qt6.compile_moc( 
  headers: ['../include/tests/dictionary_test.hpp' ],
  dependencies: qt6_dep)

executable(
  'muista-tests',
  files(
    'main.cpp',
    'dictionary_test.cpp',
  ), resources, tests_moc,
  include_directories: [muista_inc],
  link_with: [lib_commons],
  dependencies: [qt6_dep],
)
