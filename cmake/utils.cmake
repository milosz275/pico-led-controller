# see https://github.com/raspberrypi/pico-sdk/issues/1282
function(suppress_pico_sdk_warnings)
    set_source_files_properties(
        ${PICO_SDK_PATH}/src/rp2_common/pico_async_context/async_context_threadsafe_background.c
        PROPERTIES
        COMPILE_FLAGS "-Wno-unused-function"
    )
endfunction()
