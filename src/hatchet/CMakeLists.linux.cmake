FILE( GLOB _icons "${CMAKE_SOURCE_DIR}/data/icons/*-hatchet-icon.png" )
FOREACH( _file ${_icons} )
 STRING( REPLACE "${CMAKE_SOURCE_DIR}/data/icons/" "" _res ${_file} )
 STRING( REPLACE "-hatchet-icon.png" "" _res ${_res} )
 INSTALL( FILES ${_file} RENAME ${HATCHET_TARGET_NAME}.png DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/${_res}/apps )
ENDFOREACH( _file )

IF( WITH_UPOWER )
    qt5_add_dbus_interface(hatchetSources "${CMAKE_CURRENT_SOURCE_DIR}/linux/org.freedesktop.UPower.xml" "UPowerProxy")
    SET( hatchetSources ${hatchetSources} linux/UPowerHandler.cpp  )
ENDIF( WITH_UPOWER )

IF( WITH_GNOMESHORTCUTHANDLER )
    qt5_add_dbus_interface(hatchetSources "${CMAKE_CURRENT_SOURCE_DIR}/linux/GnomeSettingsDaemonMediaKeys.xml" "GnomeSettingsDaemonMediaKeysProxy")
    SET( hatchetSources ${hatchetSources} linux/GnomeShortcutHandler.cpp )
ENDIF( WITH_GNOMESHORTCUTHANDLER )

INSTALL( FILES ${CMAKE_SOURCE_DIR}/data/icons/hatchet-icon.svg RENAME ${HATCHET_TARGET_NAME}.svg  DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps )

INSTALL( FILES ${CMAKE_SOURCE_DIR}/admin/unix/hatchet.desktop  RENAME ${HATCHET_TARGET_NAME}.desktop DESTINATION ${CMAKE_INSTALL_DATADIR}/applications )

