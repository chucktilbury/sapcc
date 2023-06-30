
project(sapcc)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ./)

add_executable(${PROJECT_NAME}
    #utils.c
    scanner.c
    #parser.c
    main.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/../lib
)

target_link_libraries(${PROJECT_NAME}
    pthread
    gc
    common
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall
        -Wextra
        #-Wno-sign-compare
        #-Wno-unused-variable
        #-Wno-parentheses-equality
        -DUSE_GC
        $<$<CONFIG:DEBUG>:-g3 >
        $<$<CONFIG:DEBUG>:-Og >
        #$<$<CONFIG:DEBUG>:-DMEMORY_DEBUG >
        $<$<CONFIG:DEBUG>:-DENABLE_TRACE >
        $<$<CONFIG:DEBUG>:-DENABLE_DUMP >
        $<$<CONFIG:RELEASE>:-Ofast >
        $<$<CONFIG:PROFILE>:-pg -O0 >
)
