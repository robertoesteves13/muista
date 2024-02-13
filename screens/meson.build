screen_src = files(
  'course_screen.cpp',
  'start_screen.cpp',
)

screen_ui = qt6.compile_ui(
  sources: [
    'ui/start_screen.ui',
    'ui/course_screen.ui'
  ]
)

screen_moc = qt6.compile_moc(headers: [
    '../include/screens/start_screen.hpp',
    '../include/screens/course_screen.hpp',
  ], dependencies: qt6_dep)

lib_screens = static_library(
  'muista-screens',
  screen_src, screen_moc, screen_ui,
  include_directories: muista_inc,
  dependencies: [qt6_dep],
)
