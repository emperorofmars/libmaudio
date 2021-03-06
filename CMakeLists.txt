cmake_minimum_required(VERSION 3.0)
project(libmaudio)

if(NOT DEFINED MAUDIO_PARENT_PROJECT)
	set(MAUDIO_PARENT_PROJECT 0)
endif()

set(PORTABLE 1 CACHE BOOL "set portable install")
set(DEBIAN 0 CACHE BOOL "create Debian package")

if(PORTABLE EQUAL 1)
	message(STATUS "libmaudio: using portable install")
	
	set(CMAKE_INSTALL_PREFIX "install")
	add_definitions("-DMAUDIO_PORTABLE=1")
else()
	message(STATUS "libmaudio: using system install")
	
	add_definitions("-DMAUDIO_PORTABLE=0")
endif()

set(MAUDIO_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(MAUDIO_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(MAUDIO_TEST_DIR "${PROJECT_SOURCE_DIR}/test")

include_directories(${MAUDIO_INCLUDE_DIR})
include_directories(${MAUDIO_SOURCE_DIR})
include_directories(${MAUDIO_TEST_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wl,--no-as-needed")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "./res/lib:.")

#set preprocessor variables for version and commit hash
if(EXISTS "${PROJECT_SOURCE_DIR}/.git/HEAD")
	execute_process(
		COMMAND git rev-parse --abbrev-ref HEAD
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_BRANCH
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	execute_process(
		COMMAND git log -1 --format=%H
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_COMMIT_HASH
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	execute_process(
		COMMAND git describe --long --tags --dirty --always
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_VERSION_DESCRIPTION
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	execute_process(
		COMMAND git describe --always
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_VERSION
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	
	add_definitions("-DMAUDIO_GIT_BRANCH=\"${GIT_BRANCH}\"")
	add_definitions("-DMAUDIO_GIT_COMMIT=\"${GIT_COMMIT_HASH}\"")
	add_definitions("-DMAUDIO_GIT_DESCRIPTION=\"${GIT_VERSION_DESCRIPTION}\"")
	
	if(${GIT_VERSION} MATCHES "^v%d.%d.%d")
		add_definitions("-DMAUDIO_VERSION=\"${GIT_VERSION}\"")
	endif()
else()
	message(WARNING "Couldn't retrieve version information from git!")
endif()

set(MAUDIO_SOURCE_FILES
	${PROJECT_SOURCE_DIR}/src/maudio/store/MultiLevelStore.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/store/MultiStore.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/store/StoreWriter.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/store/KeyValueStore.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/store/StoreReader.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/store/ConfigManager.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/property/PropertyManager.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/property/SimpleProperty.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/property/SimpleKeyableProperty.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/action/ErrorAction.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/action/BaseAction.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/util/String.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/util/UniqueID.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/util/BaseObservable.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/util/Util.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/util/BaseObserver.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/util/TypeIdConverter.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/util/sptr.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/scene/Scene.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/scene/TypeManager.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/scene/Project.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/serializer/TXTSerializer.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/serializer/SerializerInfo.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/extended/TerminalPrinter.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/extended/SinusGenerator.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/audiodata/AudioQueue.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/audiodata/Sample.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/audiodata/AudioInfo.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/audiodata/AudioBuffer.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/pluginmanager/PluginManager.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/MaudioInfo.cpp
	${PROJECT_SOURCE_DIR}/src/maudio/MaudioPaths.cpp
)

set(MAUDIO_TEST_FILES
	${PROJECT_SOURCE_DIR}/test/maudio/audiodata/AudioQueueTest.cpp
	${PROJECT_SOURCE_DIR}/test/maudio/audiodata/SampleTest.cpp
	${PROJECT_SOURCE_DIR}/test/maudio/audiodata/AudioBufferTest.cpp
	${PROJECT_SOURCE_DIR}/test/MaudioTest.cpp
)

#maudio library
add_library(maudio SHARED ${MAUDIO_SOURCE_FILES})
target_link_libraries(maudio -ldl)
target_link_libraries(maudio -pthread)

#test binary
add_executable(maudio_test ${MAUDIO_TEST_FILES})
target_link_libraries(maudio_test maudio)
target_link_libraries(maudio_test -lgtest)
target_link_libraries(maudio_test -pthread)

#testing
enable_testing()
add_test(maudio_test maudio_test)

#install lib to prefix
if(PORTABLE EQUAL 1)
	install(TARGETS maudio DESTINATION "res/lib")
else()
	install(TARGETS maudio LIBRARY DESTINATION "lib")
	#install headers to prefix
	install(DIRECTORY "${MAUDIO_INCLUDE_DIR}/" DESTINATION "include")
endif()

#create packages
if(${MAUDIO_PARENT_PROJECT} EQUAL 0)
	if(${PORTABLE} EQUAL 1)
		message(STATUS "libmaudio: using zip package generator")
		set(CPACK_GENERATOR "ZIP")
	elseif(${DEBIAN} EQUAL 1)
		message(STATUS "libmaudio: using Debian package generator")
		set(CPACK_GENERATOR "DEB")
	endif()
	
	set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Martin Schwarz")
	set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MAudio")
	set(CPACK_PACKAGE_VENDOR "Martin Schwarz")
	set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.txt")
	set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.txt")
	set(CPACK_PACKAGE_VERSION_MAJOR "0")
	set(CPACK_PACKAGE_VERSION_MINOR "0")
	set(CPACK_PACKAGE_VERSION_PATCH "0")
	set(CPACK_OUTPUT_FILE_PREFIX "packages")
	INCLUDE(CPack)
endif()





