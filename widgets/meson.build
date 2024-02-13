widget_src = files(
  'course_list_button.cpp',
)

widget_ui = qt6.compile_ui(
  sources: ['ui/course_list_button.ui'],
)

widget_moc = qt6.compile_moc(headers: [
  '../include/widgets/course_list_button.hpp'
  ],include_directories: muista_inc, dependencies: qt6_dep)

lib_widgets = static_library(
  'muista-widgets',
  widget_src, widget_moc, widget_ui,
  include_directories: [muista_inc],
  dependencies: [qt6_dep],
)
