cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(kmeans)


find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  CommonTransforms
  FiltersSources
  FiltersModeling
  InteractionStyle
  InteractionWidgets
  RenderingAnnotation
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
)

# Portable: copy binaries .a to googletest/include/lib folder
set(GTEST_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/googletest/include)
set(GMOCK_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/googletest/include)
set(GTEST_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/googletest/lib)
set(GMOCK_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/googletest/lib)
include_directories(${GTEST_INCLUDE_DIR})
include_directories(${GMOCK_INCLUDE_DIR})

# Fedora: sudo dnf install gtest
set(GTEST_LIBRARY "/usr/lib64/libgtest.so.1.13.0")
set(GTEST_MAIN_LIBRARY "/usr/lib64/libgtest_main.so.1.13.0")
# ------
include_directories(${INCLUDE_DIR})

set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")

# Agrega la siguiente línea para copiar el archivo CSV a la carpeta de compilación
configure_file(${CMAKE_SOURCE_DIR}/data2k.csv ${CMAKE_BINARY_DIR}/data2k.csv COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/data5k.csv ${CMAKE_BINARY_DIR}/data5k.csv COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/puntos.csv ${CMAKE_BINARY_DIR}/puntos.csv COPYONLY)

add_executable(kmeans 
              includes/Node.hpp 
              includes/KDTree.hpp 
              utils/Reader.hpp 
              # utils/Grapher.hpp
              # utils/Tester.hpp
              # test.cpp
              main.cpp
)

target_link_libraries(kmeans PRIVATE
    ${VTK_LIBRARIES}
    # ${GTEST_LIB_DIR}/libgtest.a
    # ${GTEST_LIB_DIR}/libgtest_main.a
    # ${GMOCK_LIB_DIR}/libgmock.a
    # ${GMOCK_LIB_DIR}/libgmock_main.a
)

# Fedora --------------------------------
# target_link_libraries(kmeans PRIVATE
#     ${VTK_LIBRARIES}
#     ${GTEST_LIBRARY} 
#     ${GTEST_MAIN_LIBRARY}
# )
# target_include_directories(kmeans PRIVATE "/usr/src/googletest/googletest/include") # ruta de los encabezados de Google Test
# --------------------------------------

vtk_module_autoinit(
  TARGETS kmeans
  MODULES ${VTK_LIBRARIES}
)
