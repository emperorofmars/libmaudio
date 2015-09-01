cmake_minimum_required(VERSION 2.8)
project(maudio)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/cmake-build")

SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "./res/lib")

set(MAUDIO_SOURCE_FILES
	./src/core/store/MultiLevelStore.cpp
	./src/core/store/MultiStore.cpp
	./src/core/store/KeyValueStore.cpp
	./src/core/store/ConfigManager.cpp
	./src/core/store/ConfigReader.cpp
	./src/core/property/PropertyManager.cpp
	./src/core/property/SimpleProperty.cpp
	./src/core/property/SimpleKeyableProperty.cpp
	./src/core/action/TerminalPrinter.cpp
	./src/core/action/SinusGenerator.cpp
	./src/core/action/BaseAction.cpp
	./src/core/util/String.cpp
	./src/core/util/UniqueID.cpp
	./src/core/util/BaseObservable.cpp
	./src/core/util/Util.cpp
	./src/core/util/BaseObserver.cpp
	./src/core/util/action_ptr.cpp
	./src/core/scene/Scene.cpp
	./src/core/serializer/TXTSerializer.cpp
	./src/core/audiodata/AudioQueue.cpp
	./src/core/audiodata/Sample.cpp
	./src/core/audiodata/AudioInfo.cpp
	./src/core/audiodata/AudioBuffer.cpp
	./src/core/pluginmanager/PluginManager.cpp
	./src/extended/util/AudioDevice.hpp
	./src/extended/util/AudioDevice.cpp
	./src/extended/audiosink/Player.cpp
	./src/extended/audiosink/FileWriter.cpp
	./src/extended/audiosource/BulkReader.cpp
	./src/extended/audiosource/StreamReader.cpp
	./include/core/store/MultiLevelStore.hpp
	./include/core/store/MultiStore.hpp
	./include/core/store/IMultiStore.hpp
	./include/core/store/ConfigManager.hpp
	./include/core/store/KeyValueStore.hpp
	./include/core/store/ConfigReader.hpp
	./include/core/store/IKeyValueStore.hpp
	./include/core/store/IMultiLevelStore.hpp
	./include/core/property/SimpleProperty.hpp
	./include/core/property/IPropertyManager.hpp
	./include/core/property/IProperty.hpp
	./include/core/property/IKeyableProperty.hpp
	./include/core/property/PropertyManager.hpp
	./include/core/property/SimpleKeyableProperty.hpp
	./include/core/action/SinusGenerator.hpp
	./include/core/action/BaseAction.hpp
	./include/core/action/TerminalPrinter.hpp
	./include/core/action/IAction.hpp
	./include/core/action/IControl.hpp
	./include/core/util/BaseObservable.hpp
	./include/core/util/simple_ptr.hpp
	./include/core/util/IObserver.hpp
	./include/core/util/String.hpp
	./include/core/util/AudioException.hpp
	./include/core/util/plugin_ptr.hpp
	./include/core/util/UniqueID.hpp
	./include/core/util/action_ptr.hpp
	./include/core/util/BaseObserver.hpp
	./include/core/util/IObservable.hpp
	./include/core/util/Util.hpp
	./include/core/scene/Scene.hpp
	./include/core/serializer/ISerializable.hpp
	./include/core/serializer/TXTSerializer.hpp
	./include/core/serializer/ISerializer.hpp
	./include/core/audiodata/AudioInfo.hpp
	./include/core/audiodata/IAudioInfo.hpp
	./include/core/audiodata/Sample.hpp
	./include/core/audiodata/IAudioBuffer.hpp
	./include/core/audiodata/FileInfo.hpp
	./include/core/audiodata/AudioQueue.hpp
	./include/core/audiodata/ISample.hpp
	./include/core/audiodata/AudioBuffer.hpp
	./include/core/pluginmanager/PluginManager.hpp
	./include/core/pluginmanager/PluginLoader.hpp
	./include/maudio.hpp
	./include/extended/audiosink/FileWriter.hpp
	./include/extended/audiosink/Player.hpp
	./include/extended/audiosource/BulkReader.hpp
	./include/extended/audiosource/StreamReader.hpp
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








