# libtomahawk.accounts build file
#============================================================================

libtomahawk_inc += include_directories('.')
libtomahawk_accounts_dir = meson.current_source_dir()


libtomahawk_src += files(
    join_paths(libtomahawk_accounts_dir, 'Account.cpp'),
    join_paths(libtomahawk_accounts_dir, 'AccountConfigWidget.cpp'),
    join_paths(libtomahawk_accounts_dir, 'AccountDelegate.cpp'),
    join_paths(libtomahawk_accounts_dir, 'AccountFactoryWrapper.cpp'),
    join_paths(libtomahawk_accounts_dir, 'AccountFactoryWrapperDelegate.cpp'),
    join_paths(libtomahawk_accounts_dir, 'AccountManager.cpp'),
    join_paths(libtomahawk_accounts_dir, 'AccountModel.cpp'),
    join_paths(libtomahawk_accounts_dir, 'AccountModelFilterProxy.cpp'),
    join_paths(libtomahawk_accounts_dir, 'CredentialsManager.cpp'),
    join_paths(libtomahawk_accounts_dir, 'ConfigStorage.cpp'),
    join_paths(libtomahawk_accounts_dir, 'DelegateConfigWrapper.cpp'),
    join_paths(libtomahawk_accounts_dir, 'LocalConfigStorage.cpp'),
    join_paths(libtomahawk_accounts_dir, 'ResolverAccount.cpp'))

libtomahawk_moc_src += files()

libtomahawk_moc_h += files(
    join_paths(libtomahawk_accounts_dir, 'Account.h'),
    join_paths(libtomahawk_accounts_dir, 'AccountConfigWidget.h'),
    join_paths(libtomahawk_accounts_dir, 'AccountDelegate.h'),
    join_paths(libtomahawk_accounts_dir, 'AccountFactoryWrapper.h'),
    join_paths(libtomahawk_accounts_dir, 'AccountFactoryWrapperDelegate.h'),
    join_paths(libtomahawk_accounts_dir, 'AccountManager.h'),
    join_paths(libtomahawk_accounts_dir, 'AccountModel.h'),
    join_paths(libtomahawk_accounts_dir, 'AccountModelFilterProxy.h'),
    join_paths(libtomahawk_accounts_dir, 'CredentialsManager.h'),
    join_paths(libtomahawk_accounts_dir, 'ConfigStorage.h'),
    join_paths(libtomahawk_accounts_dir, 'DelegateConfigWrapper.h'),
    join_paths(libtomahawk_accounts_dir, 'LocalConfigStorage.h'),
    join_paths(libtomahawk_accounts_dir, 'ResolverAccount.h'))


libtomahawk_moc_ui += files(
    join_paths(libtomahawk_accounts_dir, 'AccountFactoryWrapper.ui'))



libtomahawk_accounts_dirs = [
  'configstorage',
  'spotify']

if (get_option('with_liblastfm'))
    libtomahawk_accounts_dirs += 'lastfm'
endif

foreach dir : libtomahawk_accounts_dirs
    subdir(dir)
endforeach
