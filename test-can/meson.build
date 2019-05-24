

test_can = executable('test-can',
  'can/remote_call.c',
  'can/robotronik_protocol.c',
  'main.c',
  include_directories: rootInclude,
  link_with: [
    uart,
    logger,
    can,
  ],
)
