macro(add_hatchet_translations language)
    list( APPEND HATCHET_LANGUAGES ${ARGV} )

    set( hatchet_i18n_qrc_content "<!DOCTYPE RCC><RCC version=\"1.0\">\n" )

    # hatchet and qt language files
    set( hatchet_i18n_qrc_content "${hatchet_i18n_qrc_content}<qresource prefix=\"/lang\">\n" )
    foreach( lang ${HATCHET_LANGUAGES} )
        set( hatchet_i18n_qrc_content "${hatchet_i18n_qrc_content}<file>hatchet_${lang}.qm</file>\n" )
        if( NOT lang STREQUAL "en" AND EXISTS ${QT_TRANSLATIONS_DIR}/qt_${lang}.qm )
            file( COPY ${QT_TRANSLATIONS_DIR}/qt_${lang}.qm DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
            set( hatchet_i18n_qrc_content "${hatchet_i18n_qrc_content}<file>qt_${lang}.qm</file>\n" )
        endif()

        # build explicitly enabled languages
        list( APPEND TS_FILES "${CMAKE_SOURCE_DIR}/lang/hatchet_${lang}.ts" )
    endforeach()

    set( hatchet_i18n_qrc_content "${hatchet_i18n_qrc_content}</qresource>\n" )
    set( hatchet_i18n_qrc_content "${hatchet_i18n_qrc_content}</RCC>\n" )

    # Write file and configure it aferwards to make it a BYPRODUCT: https://gitlab.kitware.com/cmake/cmake/issues/16367
    file( WRITE ${CMAKE_BINARY_DIR}/lang/hatchet_i18n.qrc.in "${hatchet_i18n_qrc_content}" )
    configure_file(${CMAKE_BINARY_DIR}/lang/hatchet_i18n.qrc.in ${CMAKE_BINARY_DIR}/lang/hatchet_i18n.qrc COPYONLY)

    qt5_add_translation(QM_FILES ${TS_FILES})

    ## HACK HACK HACK - around rcc limitations to allow out of source-tree building
    set( trans_file hatchet_i18n )
    set( trans_srcfile ${CMAKE_BINARY_DIR}/lang/${trans_file}.qrc )
    set( trans_infile ${CMAKE_CURRENT_BINARY_DIR}/${trans_file}.qrc )
    set( trans_outfile ${CMAKE_CURRENT_BINARY_DIR}/qrc_${trans_file}.cxx )

    # Copy the QRC file to the output directory
    add_custom_command(
        OUTPUT ${trans_infile}
        COMMAND ${CMAKE_COMMAND} -E copy ${trans_srcfile} ${trans_infile}
        MAIN_DEPENDENCY ${trans_srcfile}
    )

    # Run the resource compiler (rcc_options should already be set)
    add_custom_command(
        OUTPUT ${trans_outfile}
        COMMAND ${QT_RCC_EXECUTABLE}
        ARGS ${rcc_options} -name ${trans_file} -o ${trans_outfile} ${trans_infile}
        MAIN_DEPENDENCY ${trans_infile}
        DEPENDS ${QM_FILES}
    )
endmacro()

