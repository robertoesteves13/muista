domain_src = files(
  'category.cpp',
  'course.cpp',
  'definition.cpp',
  'dictionary.cpp',
  'lesson.cpp',
  'word.cpp',
  'word_tracker.cpp',
)

domain_moc = qt6.compile_moc( 
  headers: [
    './include/category.hpp',
    './include/course.hpp',
    './include/course_reader.hpp',
    './include/definition.hpp',
    './include/dictionary.hpp',
    './include/word.hpp',
    './include/word_track.hpp',
    './include/word_tracker.hpp',
  ],
  dependencies: qt6_dep)

domain_inc = include_directories('./include')

lib_domain = static_library(
  'muista-domains',
  domain_src, domain_moc,
  include_directories: [domain_inc],
  dependencies: [qt6_dep],
)
