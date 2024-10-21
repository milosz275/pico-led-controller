# toolchain-arm-gcc.cmake

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Specify the cross compilers
set(CMAKE_C_COMPILER "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/arm-none-eabi-g++")

# Set compile flags for Cortex-M0+
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m0plus -mthumb -Wl,--no-dynamic -nostartfiles -nodefaultlibs")
set(CMAKE_CXX_FLAGS "-mcpu=cortex-m0plus -mthumb -Wl,--no-dynamic -nostartfiles -nodefaultlibs")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-dynamic -nostartfiles -nodefaultlibs -L/usr/arm-none-eabi/lib")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -lc -lnosys")
