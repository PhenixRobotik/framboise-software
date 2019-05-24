

test_can = executable('test-can',
  'can.c',
  'can/remote_call.c',
  'can/robotronik_protocol.c',
  # 'logger.c',
  'main.c',
  'server.c',
  # 'uart.c',
  include_directories: rootInclude,
  link_with: [
    uart,
    logger,
  ],
)
