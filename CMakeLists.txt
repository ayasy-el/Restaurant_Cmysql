cmake_minimum_required(VERSION 3.29.3)
project(MyProject)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# Restoran sources
set(RESTORAN_SOURCES
    src/restoran/main.c
    src/restoran/kelola_menu.c
    src/restoran/tambah_pesanan.c
    src/restoran/lihat_riwayat.c
    src/database.c
    src/login.c
)

# Karyawan sources
set(KARYAWAN_SOURCES
    src/karyawan/main.c
    src/karyawan/kelola_karyawan.c
    src/database.c
    src/login.c
)

option(BUILD_RESTORAN "Build the restoran executable" ON)
option(BUILD_KARYAWAN "Build the karyawan executable" ON)

if(WIN32)
    include_directories(${PROJECT_SOURCE_DIR}/include)
    link_directories(${PROJECT_SOURCE_DIR}/lib)
    set(LIB libmariadb)
else()
    include_directories(/usr/include/mysql)
    set(LIB mysqlclient)
endif()

set(BUILD_DIR "${CMAKE_SOURCE_DIR}/build")
set(DIST_DIR "${BUILD_DIR}/dist")

if(BUILD_RESTORAN)
    add_executable(restoran ${RESTORAN_SOURCES})
    target_link_libraries(restoran PRIVATE ${LIB})

    set_target_properties(restoran PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${DIST_DIR}")
    if(WIN32)
        add_custom_command(TARGET restoran POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/lib/libmariadb.dll ${DIST_DIR}/libmariadb.dll)
    endif()
endif()

if(BUILD_KARYAWAN)
    add_executable(karyawan ${KARYAWAN_SOURCES})
    target_link_libraries(karyawan PRIVATE ${LIB})

    set_target_properties(karyawan PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${DIST_DIR}")
    if(WIN32)
        add_custom_command(TARGET karyawan POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/lib/libmariadb.dll ${DIST_DIR}/libmariadb.dll)
    endif()
endif()
