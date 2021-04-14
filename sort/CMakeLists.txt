enable_testing()

function(build_cpu_code name srcs)
    add_executable(${name} ${srcs})
    target_include_directories(${name}  
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/cpu/common/
    )

    target_link_libraries(${name} 
        LINK_PRIVATE
        ${EXTRA_SHARED_LIBS}
    )
endfunction()

file(GLOB sources cpu/*.cpp)

foreach(src ${sources})
    file(RELATIVE_PATH src_rel_path ${CMAKE_CURRENT_SOURCE_DIR}/cpu/ ${src})
    string(REGEX REPLACE "[/_\\.]" "-" example_name ${src_rel_path})
    build_cpu_code(${example_name} ${src})
    add_test("${example_name}-cpu" "${example_name}")
endforeach()
