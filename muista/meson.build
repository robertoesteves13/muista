muista_ui = qt6.compile_ui(
  sources: ['ui/main_window.ui'],
)

muista_moc = qt6.compile_moc(headers: [
    '../include/main_window.hpp',
  ], dependencies: qt6_dep)


executable(
  'muista',
  files(
    'main.cpp',
    'main_window.cpp',
  ), muista_ui, muista_moc,
  include_directories: muista_inc,
  link_with: [lib_widgets, lib_dialogs, lib_screens],
  dependencies: [qt6_dep],
)
