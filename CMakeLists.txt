cmake_minimum_required(VERSION 3.10)
project(lanetrotro)

add_subdirectory(external/cjson)

add_executable(
    lanetrotro

    src/lib/module.h
    src/lib/validate.h

    src/lanetrotro.c
    src/lanetrotro.h

    src/modules/modules.h

    src/modules/ipinfo.c
    src/modules/ctlogs.c
)

target_link_libraries(lanetrotro cjson)
