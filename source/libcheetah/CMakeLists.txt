
find_package(HDF5 REQUIRED)
# We don't want to scare people with this
mark_as_advanced(HDF5_DIR)
mark_as_advanced(CLEAR HDF5_C_INCLUDE_DIR)
mark_as_advanced(CLEAR HDF5_hdf5_LIBRARY_RELEASE)
mark_as_advanced(CLEAR HDF5_hdf5_LIBRARY_DEBUG)


# Add source files here
LIST(APPEND sources "src/assemble2DImage.cpp" "src/backgroundCorrection.cpp")
LIST(APPEND sources "src/data2d.cpp" "src/detectorCorrection.cpp")
LIST(APPEND sources "src/detectorObject.cpp" "src/hitfinders.cpp")
LIST(APPEND sources "src/libcheetah.cpp" "src/median.cpp")
LIST(APPEND sources "src/powder.cpp" "src/peakfinders.cpp")
LIST(APPEND sources "src/radialAverage.cpp" "src/saveCXI.cpp")
LIST(APPEND sources "src/saveFrame.cpp" "src/setup.cpp")
LIST(APPEND sources "src/spectrum.cpp" "src/worker.cpp")

include_directories("include")
include_directories(${HDF5_INCLUDE_DIR})

add_library(cheetah SHARED ${sources})

target_link_libraries(cheetah ${HDF5_LIBRARIES})

set_target_properties(
 cheetah
 PROPERTIES SOVERSION 1
 VERSION 1
)

install(TARGETS cheetah
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})