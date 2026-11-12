include(FetchContent)

FetchContent_Declare(
	spdlog
	GIT_REPOSITORY https://github.com/gabime/spdlog.git
	GIT_TAG v1.17.0
)

set(CONTAINERS_SRC
	containers/string.hpp
	containers/string.cpp
)

FetchContent_MakeAvailable(spdlog)

source_group("Core/Containers" FILES ${CONTAINERS_SRC})

set(CORE_SRC
	core_api.hpp
	core.hpp
	defines.hpp
	engine_context.hpp
	engine_context.cpp
	logger.hpp
	logger.cpp
	uuid.hpp
	uuid.cpp
)

source_group("Core" FILES ${CORE_SRC})

if (ENABLE_DLL)
    add_library(leth-core SHARED ${CORE_SRC} ${CONTAINERS_SRC})
else ()
    add_library(leth-core STATIC ${CORE_SRC} ${CONTAINERS_SRC})
endif ()

if (ENABLE_DLL)
    target_compile_definitions(leth-core
		PUBLIC ENABLE_DLL
        PRIVATE LETH_CORE_EXPORTS
    )
endif ()

target_link_libraries(leth-core PRIVATE spdlog::spdlog)

target_include_directories(leth-core PUBLIC ${spdlog_SOURCE_DIR}/include)
