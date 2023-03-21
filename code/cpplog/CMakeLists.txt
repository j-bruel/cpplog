project(cpplog)

find_package(fmt REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

set(CPPLOG_CPP_SOURCES	"src/centor/log/default_logger.cpp"
						"src/centor/log/logger.cpp"
						"src/centor/log/current_process_folder.cpp")
set(CPPLOG_INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(CPPLOG_PUBLIC_DIRECTORY "${PROJECT_SOURCE_DIR}/public")
set(PROJECT_VERSION "1.0.0") # @todo: Use VERSION.txt file insteed.

add_library(${PROJECT_NAME} SHARED)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "") # Disable CMake auto add "lib" prefix on Linux
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE 1) # shared libraries need PIC force it to static too we don't care of the very small overhead on full static version
cpp_flags(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${CPPLOG_CPP_SOURCES})
target_include_directories(${PROJECT_NAME}	PRIVATE
												${CPPLOG_INCLUDE_DIRECTORY}
												${TMP_OUTPUT_DIRECTORY}
											PUBLIC
												$<BUILD_INTERFACE:${CPPLOG_PUBLIC_DIRECTORY}>
											INTERFACE
												$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_definitions(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_EXPORTS)
target_link_libraries(${PROJECT_NAME}	PRIVATE spdlog::spdlog magic_enum::magic_enum
										PUBLIC fmt::fmt)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${TMP_OUTPUT_DIRECTORY}/${PROJECT_NAME}_export.hpp)

include(installdeps)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES ${TMP_OUTPUT_DIRECTORY}/${PROJECT_NAME}_export.hpp TYPE INCLUDE)
if(WIN32)
	installdeps(${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}/bin ${CMAKE_INSTALL_PREFIX}/bin)
endif()

#
# Needed only to generate install package
#
include(vcpkg-builder)
centor_configure_package_config_file()
centor_write_basic_package_version_file()
centor_install_package_files()

if (ENABLE_TESTING)
	add_subdirectory("tests")
endif ()