macro(utils_target_generate_hex TARGET_NAME)
    add_custom_target(${TARGET_NAME}-hex
        ALL
        COMMAND
            ${CMAKE_OBJCOPY} -O ihex
                $<TARGET_FILE:${TARGET_NAME}>
                ${CMAKE_CURRENT_BINARY_DIR}/output/${OUTPUTFILENAME}.hex
    )
    add_dependencies(${TARGET_NAME}-hex
        ${TARGET_NAME}
    )
endmacro()

macro(utils_target_generate_bin TARGET_NAME)   
    add_custom_target(${TARGET_NAME}-bin
        ALL
        COMMAND
            ${CMAKE_OBJCOPY} -O binary
                $<TARGET_FILE:${TARGET_NAME}>
                ${CMAKE_CURRENT_BINARY_DIR}/output/${OUTPUTFILENAME}.bin
    )
    add_dependencies(${TARGET_NAME}-bin
        ${TARGET_NAME}
    )

    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_CURRENT_BINARY_DIR}/output/${OUTPUTFILENAME}.bin")
endmacro()

macro(utils_target_print_size TARGET_NAME)
    add_custom_command(TARGET ${TARGET_NAME}
        POST_BUILD
            COMMAND
                ${CMAKE_SIZE_UTIL} --radix=10 $<TARGET_FILE:${TARGET_NAME}>
    )
endmacro()

macro(utils_target_set_linker_script TARGET_NAME LINKER_SCRIPT)
    target_link_options(${TARGET_NAME}
        PRIVATE
            -T ${LINKER_SCRIPT}
    )
    set_target_properties(${TARGET_NAME}
        PROPERTIES
            LINK_DEPENDS
                ${LINKER_SCRIPT}
    )
endmacro()