
get_filename_component(Hatchet_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set( HATCHET_USE_FILE "${Hatchet_CMAKE_DIR}/HatchetUse.cmake")
set( HATCHET_INCLUDE_DIRS "${Hatchet_CMAKE_DIR}/../../../include/libhatchet" )

# this is not how you do it but proper exporting of targets causes weird issues with cross-compiling for me
#TODO: we can easily write the install dir on configuration of this file
find_library(HATCHET_LIBRARY "hatchetlib"
                PATHS
                    "${Hatchet_CMAKE_DIR}/../../../lib/"
                    "${Hatchet_CMAKE_DIR}/../../../lib64/"
)
set( HATCHET_LIBRARIES "${HATCHET_LIBRARY}" )