
project(sapcc)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ./)

add_executable(${PROJECT_NAME}
    errors.c
    scanner.c
    parser.c
    emitters.c
    paths.c
    main.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/../util
)

target_link_libraries(${PROJECT_NAME}
    pthread
    util
    gc
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -DUSE_GC
        $<$<CONFIG:DEBUG>:-g >
        $<$<CONFIG:DEBUG>:-DENABLE_LOGGER >
        $<$<CONFIG:DEBUG>:-DENABLE_DUMP >
        $<$<CONFIG:RELEASE>:-Ofast >
        $<$<CONFIG:PROFILE>:-pg -O0 >
)
