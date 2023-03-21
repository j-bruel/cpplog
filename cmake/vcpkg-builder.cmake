# Those functions are helpful for creating a CMake package suitable for VCPKG
# https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html

include(CMakePackageConfigHelpers) ## Helpers functions for creating config files that can be included by other projects to find and use a package. Will allow us to use configure_package_config_file.
include(GNUInstallDirs) ## Define GNU standard installation directories like CMAKE_INSTALL_LIBDIR or CMAKE_INSTALL_BINDIR.

set(PKG_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake)
set(PKG_VERSION_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake)
# add subfolder of project name for include folder
Set (CMAKE_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")

# Create a config file for the target project.
function(centor_configure_package_config_file)
	if (${ARGC} GREATER 0)
		set(config_file_input "${ARGV0}")
	else()
		set(config_file_input "${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in")

		if (NOT EXISTS ${config_file_input})
			set (config_file_input "${TMP_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}-config.cmake.in")
			message("Creation of package temporary configuration file input at ${config_file_input}")
			FILE(WRITE ${config_file_input}
				"@PACKAGE_INIT@\n"
				"include($\{CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@-targets.cmake)\n"
				"check_required_components(@PROJECT_NAME@)")
		endif()
	endif()

	configure_package_config_file(${config_file_input}
		${PKG_CONFIG_FILE}
		INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
		NO_SET_AND_CHECK_MACRO)
endfunction()

# Create a version file for a project.
function(centor_write_basic_package_version_file)
	if (${ARGC} GREATER 0)
		set(version_compatibility ${ARGV0})
	else()
		set(version_compatibility SameMajorVersion)
	endif()

	message("write_basic_package_version_file : ${PKG_VERSION_FILE}")
	write_basic_package_version_file(
		${PKG_VERSION_FILE}
		COMPATIBILITY ${version_compatibility})
endfunction()

# Install the files needed to have a package compatible with findpackage()
function(centor_install_package_files)
	install(
		FILES
			${PKG_CONFIG_FILE}
			${PKG_VERSION_FILE}
		DESTINATION
			${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME})

	install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets)

	if (${ARGC} GREATER 0)
		set(public_headers_dir "${ARGV0}")
	else()
		set(public_headers_dir "${CMAKE_CURRENT_SOURCE_DIR}/public/")
	endif()
	install(DIRECTORY ${public_headers_dir} TYPE INCLUDE)

	install(EXPORT ${PROJECT_NAME}-targets
		NAMESPACE centor::
		DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME})
endfunction()