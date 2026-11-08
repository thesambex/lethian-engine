include(FetchContent)

FetchContent_Declare(
	spdlog
	GIT_REPOSITORY https://github.com/gabime/spdlog.git
	GIT_TAG v1.17.0
)

set(SRC_CONTAINERS
	containers/string.hpp
	containers/string.cpp
)

FetchContent_MakeAvailable(spdlog)

source_group("Containers" FILES ${SRC_CONTAINERS})

set(SRC_CORE
	core_api.hpp
	core.hpp
	defines.hpp
	engine_context.hpp
	engine_context.cpp
	logger.hpp
	logger.cpp
)

if (ENABLE_DLL)
    add_library(leth-core SHARED ${SRC_CORE} ${SRC_CONTAINERS})
else ()
    add_library(leth-core STATIC ${SRC_CORE} ${SRC_CONTAINERS})
endif ()

if (ENABLE_DLL)
    target_compile_definitions(leth-core
		PUBLIC ENABLE_DLL
        PRIVATE LETH_CORE_EXPORTS
    )
endif ()

target_link_libraries(leth-core PRIVATE spdlog::spdlog)

target_include_directories(leth-core PUBLIC ${spdlog_SOURCE_DIR}/include)
