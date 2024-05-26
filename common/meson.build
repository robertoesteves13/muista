common_src = files(
  'course.cpp',
  'module.cpp',
  'dictionary.cpp',
)

common_moc = qt6.compile_moc( 
  headers: ['../include/common/course.hpp', '../include/common/dictionary.hpp'],
  dependencies: qt6_dep)

lib_commons = static_library(
  'muista-commons',
  common_src, common_moc,
  include_directories: [muista_inc],
  dependencies: [qt6_dep],
)
