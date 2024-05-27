tests_moc = qt6.compile_moc( 
  headers: [ 'tests.hpp' ],
  dependencies: qt6_dep,
)

dictionary_test = executable(
  'dictionary',
  'dictionary.cpp', tests_moc,
  include_directories: [muista_inc],
  link_with: [lib_commons],
  dependencies: [qt6_dep],
  install: true,
)

word_test = executable(
  'word',
  'word.cpp', tests_moc,
  include_directories: [muista_inc],
  link_with: [lib_commons],
  dependencies: [qt6_dep],
  install: true,
)

test('dictionary-test', dictionary_test)
test('word-test', word_test)
