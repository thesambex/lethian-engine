set(ENGINE_SRC
	engine_api.hpp
)

source_group("Engine" FILES ${ENGINE_SRC})

set(RESOURCES_SRC
	resources/asset.hpp
	resources/asset.cpp
)

source_group("Engine/Resources" FILES ${RESOURCES_SRC})

if (ENABLE_DLL)
    add_library(leth-engine
		SHARED
		${ENGINE_SRC}
		${RESOURCES_SRC}
	)
else ()
    add_library(leth-engine
	 	STATIC
		${ENGINE_SRC}
		${RESOURCES_SRC}
	)
endif ()

if (ENABLE_DLL)
    target_compile_definitions(leth-engine
        PUBLIC ENABLE_DLL
        PRIVATE LETH_ENGINE_EXPORTS
    )
endif ()

target_include_directories(leth-engine
    PRIVATE
    "${ENGINE_DIR}"
)

target_link_libraries(leth-engine
    PRIVATE
    leth-core
	leth-platform
)
