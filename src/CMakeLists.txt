# Project root directory
set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")

# Get *.cpp and *.h source files
set(SOURCE_DIR "${ROOT_DIR}/src")
file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.h")

# Plugin.h
set(VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/src/Plugin.h")
configure_file(
	"${ROOT_DIR}/cmake/Plugin.h.in"
	"${VERSION_HEADER}"
	@ONLY
)
source_group("src" FILES "${VERSION_HEADER}")

# version.rc
configure_file(
	"${ROOT_DIR}/cmake/version.rc.in"
	"${CMAKE_CURRENT_BINARY_DIR}/version.rc"
	@ONLY
)

# Setup SKSE project library
add_library(
	"${PROJECT_NAME}"
	SHARED
	${SOURCE_FILES}
	"${VERSION_HEADER}"
	"${CMAKE_CURRENT_BINARY_DIR}/version.rc"
	"${ROOT_DIR}/.clang-format"
	"${ROOT_DIR}/.editorconfig"
)

# Compile with C++20 features
target_compile_features(
	"${PROJECT_NAME}"
	PRIVATE
		cxx_std_23
)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(
		"${PROJECT_NAME}"
		PRIVATE
			"/sdl"	# Enable Additional Security Checks
			"/utf-8"	# Set Source and Executable character sets to UTF-8
			"/Zi"	# Debug Information Format

			"/permissive-"	# Standards conformance
			"/Zc:preprocessor"	# Enable preprocessor conformance mode

			"/wd4200" # nonstandard extension used : zero-sized array in struct/union

			"$<$<CONFIG:DEBUG>:>"
			"$<$<CONFIG:RELEASE>:/Zc:inline;/JMC-;/Ob3>"
	)

	target_link_options(
		"${PROJECT_NAME}"
		PRIVATE
			"$<$<CONFIG:DEBUG>:/INCREMENTAL;/OPT:NOREF;/OPT:NOICF>"
			"$<$<CONFIG:RELEASE>:/INCREMENTAL:NO;/OPT:REF;/OPT:ICF;/DEBUG:FULL>"
	)
endif()

# Default output directory for compiled files
target_include_directories(
	"${PROJECT_NAME}"
	PRIVATE
		"${CMAKE_CURRENT_BINARY_DIR}/src"
		"${SOURCE_DIR}"
)

# CommonLib
if(${SKYRIM_AE})
	add_subdirectory("${ROOT_DIR}/CommonLib/AE" CommonLibSSE EXCLUDE_FROM_ALL)
elseif(${SKYRIM_SE})
	add_subdirectory("${ROOT_DIR}/CommonLib/SE" CommonLibSSE EXCLUDE_FROM_ALL)
elseif(${SKYRIM_VR})
	add_subdirectory("${ROOT_DIR}/CommonLib/VR" CommonLibSSE EXCLUDE_FROM_ALL)
endif()
target_link_libraries(
	"${PROJECT_NAME}"
	PRIVATE
		CommonLibSSE::CommonLibSSE
)

# Precompiled Headers (PCH)
target_precompile_headers(
	"${PROJECT_NAME}"
	PRIVATE
		"${SOURCE_DIR}/PCH.h"
)

# Get output directory based on configured version of Skyrim
if(${SKYRIM_AE})
	set(OUTPUT_FOLDER "$ENV{SKSE_SKYRIM_AE_DLLS}")
	if(NOT EXISTS "${OUTPUT_FOLDER}")
		set(OUTPUT_FOLDER "${ROOT_DIR}/output/AE")
	endif()
elseif(${SKYRIM_SE})
	set(OUTPUT_FOLDER "$ENV{SKSE_SKYRIM_SE_DLLS}")
	if(NOT EXISTS "${OUTPUT_FOLDER}")
		set(OUTPUT_FOLDER "${ROOT_DIR}/output/SE")
	endif()
elseif(${SKYRIM_VR})
	set(OUTPUT_FOLDER "$ENV{SKSE_SKYRIM_VR_DLLS}")
	if(NOT EXISTS "${OUTPUT_FOLDER}")
		set(OUTPUT_FOLDER "${ROOT_DIR}/output/VR")
	endif()
endif()

# Create output directory if it does not exist
if(NOT EXISTS "${OUTPUT_FOLDER}")
	add_custom_command(
		TARGET "${PROJECT_NAME}"
		POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${OUTPUT_FOLDER}"
		VERBATIM
	)
endif()

MESSAGE(INFO "Build will output .dll and .pdb to ${OUTPUT_FOLDER}")

# Copy the output .dll and debug .pdb to the configured output directory
add_custom_command(
	TARGET "${PROJECT_NAME}"
	POST_BUILD
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${OUTPUT_FOLDER}"
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_PDB_FILE:${PROJECT_NAME}>" "${OUTPUT_FOLDER}"
	VERBATIM
)
