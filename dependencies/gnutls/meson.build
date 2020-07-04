# Gnutls dependency file
#============================================================================


# Look for gnutls, a required dependency.
#---------------------------------------------------
gnutls_dep = declare_dependency(
    dependencies : [dependency(
        'gnutls',
        version : '>= 3.6.0')])


# Set HAVE_GNUTLS in config.h
#---------------------------------------------------
config_h.set(
    'HAVE_GNUTLS',
    gnutls_dep.found(),
    description : 
        'GnuTLS is a secure communications library implementing the ' +
        ' SSL, TLS, and DTLS protocols and technologies around them.')
