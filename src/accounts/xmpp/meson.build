# accounts.xmpp build file
#============================================================================

xmpp_inc = include_directories('.')
xmpp_dir = meson.current_source_dir()


xmpp_src = files(
    join_paths(xmpp_dir, 'XmppAccount.cpp'),
    join_paths(xmpp_dir, 'XmppConfigWidget.cpp'),
    join_paths(xmpp_dir, 'XmppInfoPlugin.cpp'),

    join_paths(xmpp_dir, 'sip/XmppSip.cpp'),
    join_paths(xmpp_dir, 'sip/HatchetXmppMessage.cpp'),
    join_paths(xmpp_dir, 'sip/HatchetXmppMessageFactory.cpp'),
    join_paths(xmpp_dir, 'sip/AvatarManager.cpp'),
    join_paths(xmpp_dir, 'sip/XmlConsole.cpp'))


xmpp_moc_ui = files(
    join_paths(xmpp_dir, 'XmppConfigWidget.ui'),
    join_paths(xmpp_dir, 'sip/XmlConsole.ui'))

xmp_moc_h = files (
    join_paths(xmpp_dir, 'XmppAccount.h'),
    join_paths(xmpp_dir, 'XmppConfigWidget.h'),
    join_paths(xmpp_dir, 'XmppInfoPlugin.h'),

    join_paths(xmpp_dir, 'sip/XmppSip.h'),
    join_paths(xmpp_dir, 'sip/HatchetXmppMessage.h'),
    join_paths(xmpp_dir, 'sip/HatchetXmppMessageFactory.h'),
    join_paths(xmpp_dir, 'sip/AvatarManager.h'),
    join_paths(xmpp_dir, 'sip/XmlConsole.h'))




