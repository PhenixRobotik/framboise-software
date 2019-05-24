

test_can = executable('test-can',
  'main.c',
  include_directories: rootInclude,
  link_with: [
    uart,
    logger,
    can,
    can_protocol,
  ],
)
