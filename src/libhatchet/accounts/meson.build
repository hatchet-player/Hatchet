# libhatchet.accounts build file
#============================================================================

libhatchet_inc += include_directories('.')
libhatchet_accounts_dir = meson.current_source_dir()


libhatchet_src += files(
    join_paths(libhatchet_accounts_dir, 'Account.cpp'),
    join_paths(libhatchet_accounts_dir, 'AccountConfigWidget.cpp'),
    join_paths(libhatchet_accounts_dir, 'AccountDelegate.cpp'),
    join_paths(libhatchet_accounts_dir, 'AccountFactoryWrapper.cpp'),
    join_paths(libhatchet_accounts_dir, 'AccountFactoryWrapperDelegate.cpp'),
    join_paths(libhatchet_accounts_dir, 'AccountManager.cpp'),
    join_paths(libhatchet_accounts_dir, 'AccountModel.cpp'),
    join_paths(libhatchet_accounts_dir, 'AccountModelFilterProxy.cpp'),
    join_paths(libhatchet_accounts_dir, 'CredentialsManager.cpp'),
    join_paths(libhatchet_accounts_dir, 'ConfigStorage.cpp'),
    join_paths(libhatchet_accounts_dir, 'DelegateConfigWrapper.cpp'),
    join_paths(libhatchet_accounts_dir, 'LocalConfigStorage.cpp'),
    join_paths(libhatchet_accounts_dir, 'ResolverAccount.cpp'))

libhatchet_moc_src += files()

libhatchet_moc_h += files(
    join_paths(libhatchet_accounts_dir, 'Account.h'),
    join_paths(libhatchet_accounts_dir, 'AccountConfigWidget.h'),
    join_paths(libhatchet_accounts_dir, 'AccountDelegate.h'),
    join_paths(libhatchet_accounts_dir, 'AccountFactoryWrapper.h'),
    join_paths(libhatchet_accounts_dir, 'AccountFactoryWrapperDelegate.h'),
    join_paths(libhatchet_accounts_dir, 'AccountManager.h'),
    join_paths(libhatchet_accounts_dir, 'AccountModel.h'),
    join_paths(libhatchet_accounts_dir, 'AccountModelFilterProxy.h'),
    join_paths(libhatchet_accounts_dir, 'CredentialsManager.h'),
    join_paths(libhatchet_accounts_dir, 'ConfigStorage.h'),
    join_paths(libhatchet_accounts_dir, 'DelegateConfigWrapper.h'),
    join_paths(libhatchet_accounts_dir, 'LocalConfigStorage.h'),
    join_paths(libhatchet_accounts_dir, 'ResolverAccount.h'))


libhatchet_moc_ui += files(
    join_paths(libhatchet_accounts_dir, 'AccountFactoryWrapper.ui'))



libhatchet_accounts_dirs = [
  'configstorage',
  'spotify']

if (get_option('with_liblastfm'))
    libhatchet_accounts_dirs += 'lastfm'
endif

foreach dir : libhatchet_accounts_dirs
    subdir(dir)
endforeach
