macro(hatchet_add_test test_class)
    include_directories(${QT_INCLUDES} "${PROJECT_SOURCE_DIR}/src" ${CMAKE_CURRENT_BINARY_DIR})

    set(HATCHET_TEST_CLASS ${test_class})
    set(HATCHET_TEST_TARGET ${HATCHET_TEST_CLASS}Test)
    configure_file(main.cpp.in Test${HATCHET_TEST_CLASS}.cpp)
    configure_file(Test${HATCHET_TEST_CLASS}.h Test${HATCHET_TEST_CLASS}.h)

    add_executable(${HATCHET_TEST_CLASS}Test Test${HATCHET_TEST_CLASS}.cpp)

    set_target_properties(${HATCHET_TEST_TARGET} PROPERTIES AUTOMOC ON)

    target_link_libraries(${HATCHET_TEST_TARGET}
        ${HATCHET_LIBRARIES}
        ${QT_QTTEST_LIBRARY}
        ${QT_QTCORE_LIBRARY}
    )

    target_link_libraries(${HATCHET_TEST_TARGET}
        Qt5::Core Qt5::Network Qt5::Widgets Qt5::Sql Qt5::Xml Qt5::Test
    )

    add_test(NAME ${HATCHET_TEST_TARGET} COMMAND ${HATCHET_TEST_TARGET})

endmacro()
