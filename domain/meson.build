domain_src = files(
  'course.cpp',
  'lesson.cpp',
  'dictionary.cpp',
  'word_tracker.cpp',
)

domain_moc = qt6.compile_moc( 
  headers: [
    './include/course.hpp',
    './include/dictionary.hpp',
    ],
  dependencies: qt6_dep)

domain_inc = include_directories('./include')

lib_domain = static_library(
  'muista-domains',
  domain_src, domain_moc,
  include_directories: [domain_inc],
  dependencies: [qt6_dep],
)
