
project(sapcc)


add_executable(${PROJECT_NAME}
    errors.c
    scanner.c
    parser.c
    emitters.c
    paths.c
    main.c
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
        -I${PROJECT_SOURCE_DIR}/../util
        -I${PROJECT_SOURCE_DIR}/../bdwgc/include
        $<$<CONFIG:DEBUG>:-g >
        $<$<CONFIG:DEBUG>:-DENABLE_LOGGER >
        $<$<CONFIG:DEBUG>:-DENABLE_DUMP >
        $<$<CONFIG:RELEASE>:-Ofast >
        $<$<CONFIG:PROFILE>:-pg -O0 >
)
