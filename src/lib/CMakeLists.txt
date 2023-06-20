
project(common)

add_library(${PROJECT_NAME} STATIC
    fileio.c
    hash.c
    dllist.c
    memory.c
    strs.c
    errors.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/../include
        ${PROJECT_SOURCE_DIR}/../common
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall
        -Wextra
        $<$<CONFIG:DEBUG>:-g3 >
        $<$<CONFIG:DEBUG>:-Og >
        $<$<CONFIG:DEBUG>:-DMEMORY_DEBUG >
        $<$<CONFIG:DEBUG>:-DENA_TRACE >
        $<$<CONFIG:RELEASE>:-Ofast >
        $<$<CONFIG:PROFILE>:-pg -O0 >
)
