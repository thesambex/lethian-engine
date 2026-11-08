set(
    FRAMEWORK_SRC
    framework_api.hpp
    engine_framework.hpp
    engine_framework.cpp
)

if (ENABLE_DLL)
    add_library(leth-framework SHARED ${FRAMEWORK_SRC})
else ()
    add_library(leth-framework STATIC ${FRAMEWORK_SRC})
endif ()

if (ENABLE_DLL)
    target_compile_definitions(leth-framework
        PUBLIC ENABLE_DLL
        PRIVATE LETH_FRAMEWORK_EXPORTS
    )
endif ()

target_include_directories(leth-framework
    PRIVATE
    "${ENGINE_DIR}"
)

target_link_libraries(leth-framework
    PRIVATE
    leth-core
)

