set(
	PLATFORM_SRC
	platform_api.hpp
)

source_group("Platform" FILES ${PLATFORM_SRC})

set(FS_SRC
	filesystem/file.hpp
	filesystem/filesystem.hpp
	filesystem/physical_filesystem.hpp
	filesystem/physical_filesystem.cpp
	filesystem/vsf.hpp
	filesystem/vsf.cpp
)

source_group("Platform/Filesystem" FILES ${FS_SRC})

set(FS_WINDOWS_SRC
	filesystem/windows/windows_file.hpp
	filesystem/windows/windows_file.cpp
)

source_group("Platform/Filesystem/Windows" FILES ${FS_WINDOWS_SRC})

set(DISPLAY_SRC
	display/display.hpp
	display/display.cpp
)

source_group("Platform/Display" FILES ${DISPLAY_SRC})

set(DISPLAY_WINDOWS_SRC
	display/windows/windows_display.hpp
	display/windows/windows_display.cpp
	display/windows/windows_callback.hpp
	display/windows/windows_callback.cpp
)

source_group("Platform/Display/Windows" FILES ${DISPLAY_WINDOWS_SRC})

if (ENABLE_DLL)
    add_library(leth-platform
		SHARED
		${PLATFORM_SRC}
		${FS_SRC}
		${DISPLAY_SRC}
	)
else ()
    add_library(leth-platform
		STATIC
		${PLATFORM_SRC}
		${FS_SRC}
		${DISPLAY_SRC}
	)
endif ()

if (WIN32)
	target_sources(leth-platform
		PRIVATE
		${FS_WINDOWS_SRC}
		${DISPLAY_WINDOWS_SRC}
	)
endif ()

if (ENABLE_DLL)
    target_compile_definitions(leth-platform
        PUBLIC ENABLE_DLL
        PRIVATE LETH_PLATFORM_EXPORTS
    )
endif ()

target_include_directories(leth-platform
    PRIVATE
    "${ENGINE_DIR}"
)

target_link_libraries(leth-platform
    PRIVATE
    leth-core
)
