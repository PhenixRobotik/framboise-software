systemd_config = configuration_data()
systemd_config.set('DaemonExecStart',
  get_option('prefix') / get_option('bindir') / 'framboise-brain'
)

configure_file(
  input : 'framboise-brain.service.in',
  output: 'framboise-brain.service',
  configuration: systemd_config,
  install: true,
  install_dir: get_option('sysconfdir') / 'systemd' / 'user',
)
