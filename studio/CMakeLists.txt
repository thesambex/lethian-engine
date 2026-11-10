find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SRC_PROJECT
	project/studio_project.hpp
	project/studio_project.cpp
)

source_group("Project" FILES ${SRC_PROJECT})

set(SRC_PRESENTATION
	presentation/main_window.ui
	presentation/main_window.hpp
	presentation/main_window.cpp
	presentation/new_project_dialog.ui
	presentation/new_project_dialog.hpp
	presentation/new_project_dialog.cpp
)

source_group("Presentation" FILES ${SRC_PRESENTATION})

set(SRC_WIDGETS
	widgets/file_list_widget.hpp
	widgets/file_list_widget.cpp
)

source_group("Widgets" FILES ${SRC_WIDGETS})

qt_add_executable(lethian-studio WIN32
    main.cpp
	studio_application.hpp
	studio_application.cpp
	studio_engine.hpp
	studio_engine.cpp
	${SRC_PRESENTATION}
	${SRC_PROJECT}
	${SRC_WIDGETS}
)

target_link_libraries(lethian-studio
    PRIVATE
    Qt::Core
    Qt::Widgets
	leth-core
	leth-framework
)

target_include_directories(
	lethian-studio
	PRIVATE
	"${VENDOR_DIR}/toml"
	"${ENGINE_DIR}"
)

install(TARGETS lethian-studio
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET lethian-studio
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})

