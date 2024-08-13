edatos_sources = [
  'main.c',
  'edatos-application.c',
  'edatos-window.c',
]

edatos_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
]

gnome = import('gnome')

edatos_sources += gnome.compile_resources('edatos-resources',
  'edatos.gresource.xml',
  c_name: 'edatos'
)

executable('edatos', edatos_sources,
  dependencies: edatos_deps,
  install: true,
)
