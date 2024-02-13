dialog_src = files(
  'create_course_dialog.cpp',
)

dialog_ui = qt6.compile_ui(
  sources: ['ui/create_course_dialog.ui'],
)

dialog_moc = qt6.compile_moc( 
  headers: ['../include/dialogs/create_course_dialog.hpp'],
  dependencies: qt6_dep)

lib_dialogs = static_library(
  'muista-dialogs',
  dialog_src, dialog_moc, dialog_ui,
  include_directories: [muista_inc],
  dependencies: [qt6_dep],
)
