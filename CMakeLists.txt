cmake_minimum_required(VERSION 3.29.3)
project(MyProject)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(SOURCES
    main.c
    tambah_menu.c
    tambah_pesanan.c
    lihat_riwayat.c
    database.c
)

if(WIN32)
    include_directories(${PROJECT_SOURCE_DIR}/include)
    link_directories(${PROJECT_SOURCE_DIR}/lib)

    add_executable(main ${SOURCES})
    target_link_libraries(main PRIVATE libmariadb)
else()
    include_directories(/usr/include/mysql)

    add_executable(main ${SOURCES})
    target_link_libraries(main PRIVATE mysqlclient)
endif()

# Output directories
set(BUILD_DIR "${CMAKE_SOURCE_DIR}/build")
set(DIST_DIR "${BUILD_DIR}/dist")
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${DIST_DIR}")

# Copy .dll only on Windows
if(WIN32)
    add_custom_command(TARGET main POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/lib/libmariadb.dll ${DIST_DIR}/libmariadb.dll)
endif()