
project('framboise-brain',
  'c', 'cpp',
  version: '0.3',

  default_options: [
    'cpp_std=gnu++14',
    'warning_level=3',
    'prefix=/usr',
  ],
)

###############################################################################
# Project setup
config = configuration_data()

config.set('PROJECT', '"@0@"'.format(meson.project_name()))

config.set('VERSION', '"@0@"'.format(meson.project_version()))

data_directory = get_option('datadir') / 'framboise-brain'
config.set('DATA_DIR', '"@0@"'.format(get_option('prefix') / data_directory))


###############################################################################
# Dependencies

gtkmm = dependency('gtkmm-3.0', version: '>=3.10')

###############################################################################
# Targets

subdir('data')
subdir('src')
