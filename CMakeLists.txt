cmake_minimum_required(VERSION 2.8)
project(maudio)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/cmake-build")

SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "./res/lib")

set(MAUDIO_SOURCE_FILES
	${PROJECT_SOURCE_DIR}/src/core/store/MultiLevelStore.cpp
	${PROJECT_SOURCE_DIR}/src/core/store/MultiStore.cpp
	${PROJECT_SOURCE_DIR}/src/core/store/StoreWriter.cpp
	${PROJECT_SOURCE_DIR}/src/core/store/KeyValueStore.cpp
	${PROJECT_SOURCE_DIR}/src/core/store/StoreReader.cpp
	${PROJECT_SOURCE_DIR}/src/core/store/ConfigManager.cpp
	${PROJECT_SOURCE_DIR}/src/core/property/PropertyManager.cpp
	${PROJECT_SOURCE_DIR}/src/core/property/SimpleProperty.cpp
	${PROJECT_SOURCE_DIR}/src/core/property/SimpleKeyableProperty.cpp
	${PROJECT_SOURCE_DIR}/src/core/action/TerminalPrinter.cpp
	${PROJECT_SOURCE_DIR}/src/core/action/SinusGenerator.cpp
	${PROJECT_SOURCE_DIR}/src/core/action/BaseAction.cpp
	${PROJECT_SOURCE_DIR}/src/core/util/String.cpp
	${PROJECT_SOURCE_DIR}/src/core/util/UniqueID.cpp
	${PROJECT_SOURCE_DIR}/src/core/util/RecursiveSharedMutex.cpp
	${PROJECT_SOURCE_DIR}/src/core/util/BaseObservable.cpp
	${PROJECT_SOURCE_DIR}/src/core/util/Util.cpp
	${PROJECT_SOURCE_DIR}/src/core/util/BaseObserver.cpp
	${PROJECT_SOURCE_DIR}/src/core/util/TypeIdConverter.cpp
	${PROJECT_SOURCE_DIR}/src/core/util/SharedLockGuard.cpp
	${PROJECT_SOURCE_DIR}/src/core/util/sptr.cpp
	${PROJECT_SOURCE_DIR}/src/core/scene/Scene.cpp
	${PROJECT_SOURCE_DIR}/src/core/scene/TypeManager.cpp
	${PROJECT_SOURCE_DIR}/src/core/scene/Project.cpp
	${PROJECT_SOURCE_DIR}/src/core/serializer/TXTSerializer.cpp
	${PROJECT_SOURCE_DIR}/src/core/serializer/SerializerInfo.cpp
	${PROJECT_SOURCE_DIR}/src/core/audiodata/AudioQueue.cpp
	${PROJECT_SOURCE_DIR}/src/core/audiodata/Sample.cpp
	${PROJECT_SOURCE_DIR}/src/core/audiodata/AudioInfo.cpp
	${PROJECT_SOURCE_DIR}/src/core/audiodata/AudioBuffer.cpp
	${PROJECT_SOURCE_DIR}/src/core/pluginmanager/PluginManager.cpp
	${PROJECT_SOURCE_DIR}/src/extended/util/AudioDevice.cpp
	${PROJECT_SOURCE_DIR}/src/extended/audiosink/Player.cpp
	${PROJECT_SOURCE_DIR}/src/extended/audiosink/FileWriter.cpp
	${PROJECT_SOURCE_DIR}/src/extended/audiosource/BulkReader.cpp
	${PROJECT_SOURCE_DIR}/src/extended/audiosource/StreamReader.cpp
) 

set(MAUDIO_INCLUDE_FILES
	${PROJECT_SOURCE_DIR}/include/core/store/StoreWriter.hpp
	${PROJECT_SOURCE_DIR}/include/core/store/MultiLevelStore.hpp
	${PROJECT_SOURCE_DIR}/include/core/store/StoreReader.hpp
	${PROJECT_SOURCE_DIR}/include/core/store/MultiStore.hpp
	${PROJECT_SOURCE_DIR}/include/core/store/IMultiStore.hpp
	${PROJECT_SOURCE_DIR}/include/core/store/ConfigManager.hpp
	${PROJECT_SOURCE_DIR}/include/core/store/KeyValueStore.hpp
	${PROJECT_SOURCE_DIR}/include/core/store/IKeyValueStore.hpp
	${PROJECT_SOURCE_DIR}/include/core/store/IMultiLevelStore.hpp
	${PROJECT_SOURCE_DIR}/include/core/property/SimpleProperty.hpp
	${PROJECT_SOURCE_DIR}/include/core/property/IPropertyManager.hpp
	${PROJECT_SOURCE_DIR}/include/core/property/IProperty.hpp
	${PROJECT_SOURCE_DIR}/include/core/property/IKeyableProperty.hpp
	${PROJECT_SOURCE_DIR}/include/core/property/PropertyManager.hpp
	${PROJECT_SOURCE_DIR}/include/core/property/SimpleKeyableProperty.hpp
	${PROJECT_SOURCE_DIR}/include/core/action/SinusGenerator.hpp
	${PROJECT_SOURCE_DIR}/include/core/action/BaseAction.hpp
	${PROJECT_SOURCE_DIR}/include/core/action/TerminalPrinter.hpp
	${PROJECT_SOURCE_DIR}/include/core/action/IAction.hpp
	${PROJECT_SOURCE_DIR}/include/core/action/IControl.hpp
	${PROJECT_SOURCE_DIR}/include/core/util/BaseObservable.hpp
	${PROJECT_SOURCE_DIR}/include/core/util/SharedLockGuard.hpp
	${PROJECT_SOURCE_DIR}/include/core/util/IObserver.hpp
	${PROJECT_SOURCE_DIR}/include/core/util/String.hpp
	${PROJECT_SOURCE_DIR}/include/core/util/AudioException.hpp
	${PROJECT_SOURCE_DIR}/include/core/util/UniqueID.hpp
	${PROJECT_SOURCE_DIR}/include/core/util/BaseObserver.hpp
	${PROJECT_SOURCE_DIR}/include/core/util/IObservable.hpp
	${PROJECT_SOURCE_DIR}/include/core/util/Util.hpp
	${PROJECT_SOURCE_DIR}/include/core/util/sptr.hpp
	${PROJECT_SOURCE_DIR}/include/core/util/TypeIdConverter.hpp
	${PROJECT_SOURCE_DIR}/include/core/util/RecursiveSharedMutex.hpp
	${PROJECT_SOURCE_DIR}/include/core/scene/Scene.hpp
	${PROJECT_SOURCE_DIR}/include/core/scene/TypeManager.hpp
	${PROJECT_SOURCE_DIR}/include/core/scene/Project.hpp
	${PROJECT_SOURCE_DIR}/include/core/serializer/ISerializable.hpp
	${PROJECT_SOURCE_DIR}/include/core/serializer/TXTSerializer.hpp
	${PROJECT_SOURCE_DIR}/include/core/serializer/SerializerInfo.hpp
	${PROJECT_SOURCE_DIR}/include/core/serializer/ISerializer.hpp
	${PROJECT_SOURCE_DIR}/include/core/audiodata/AudioInfo.hpp
	${PROJECT_SOURCE_DIR}/include/core/audiodata/IAudioInfo.hpp
	${PROJECT_SOURCE_DIR}/include/core/audiodata/Sample.hpp
	${PROJECT_SOURCE_DIR}/include/core/audiodata/IAudioBuffer.hpp
	${PROJECT_SOURCE_DIR}/include/core/audiodata/FileInfo.hpp
	${PROJECT_SOURCE_DIR}/include/core/audiodata/AudioQueue.hpp
	${PROJECT_SOURCE_DIR}/include/core/audiodata/ISample.hpp
	${PROJECT_SOURCE_DIR}/include/core/audiodata/AudioBuffer.hpp
	${PROJECT_SOURCE_DIR}/include/core/pluginmanager/PluginManager.hpp
	${PROJECT_SOURCE_DIR}/include/core/pluginmanager/PluginLoader.hpp
	${PROJECT_SOURCE_DIR}/include/maudio.hpp
	${PROJECT_SOURCE_DIR}/include/extended/audiosink/FileWriter.hpp
	${PROJECT_SOURCE_DIR}/include/extended/audiosink/Player.hpp
	${PROJECT_SOURCE_DIR}/include/extended/audiosource/BulkReader.hpp
	${PROJECT_SOURCE_DIR}/include/extended/audiosource/StreamReader.hpp
)

set(TESTBIN_SOURCE_FILES
	./examples/test1.cpp
)

add_library(maudio SHARED ${MAUDIO_SOURCE_FILES})
target_link_libraries(maudio -ldl)
target_link_libraries(maudio -lportaudio)

install(TARGETS maudio DESTINATION "${CMAKE_SOURCE_DIR}/res/lib")

add_executable(maudio_test EXCLUDE_FROM_ALL ${TESTBIN_SOURCE_FILES})
target_link_libraries(maudio_test maudio)








