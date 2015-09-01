project('maudio', 'cpp')

add_global_arguments('-std=c++11', language : 'cpp')

dynlib = find_library('dl', required : true)
palib = find_library('portaudio', required : true)
maudiodep = [dynlib, palib]

headerdir = include_directories('include')
srcdir = include_directories('src')

src = [
'./src/core/store/MultiLevelStore.cpp',
'./src/core/store/MultiStore.cpp',
'./src/core/store/KeyValueStore.cpp',
'./src/core/store/ConfigManager.cpp',
'./src/core/store/ConfigReader.cpp',
'./src/core/property/PropertyManager.cpp',
'./src/core/property/SimpleProperty.cpp',
'./src/core/property/SimpleKeyableProperty.cpp',
'./src/core/action/TerminalPrinter.cpp',
'./src/core/action/SinusGenerator.cpp',
'./src/core/action/BaseAction.cpp',
'./src/core/util/String.cpp',
'./src/core/util/UniqueID.cpp',
'./src/core/util/BaseObservable.cpp',
'./src/core/util/Util.cpp',
'./src/core/util/BaseObserver.cpp',
'./src/core/util/sptr.cpp',
'./src/core/scene/Scene.cpp',
'./src/core/serializer/TXTSerializer.cpp',
'./src/core/audiodata/AudioQueue.cpp',
'./src/core/audiodata/Sample.cpp',
'./src/core/audiodata/AudioInfo.cpp',
'./src/core/audiodata/AudioBuffer.cpp',
'./src/core/pluginmanager/PluginManager.cpp',
'./src/extended/util/AudioDevice.hpp',
'./src/extended/util/AudioDevice.cpp',
'./src/extended/audiosink/Player.cpp',
'./src/extended/audiosink/FileWriter.cpp',
'./src/extended/audiosource/BulkReader.cpp',
'./src/extended/audiosource/StreamReader.cpp',
'./include/core/store/MultiLevelStore.hpp',
'./include/core/store/MultiStore.hpp',
'./include/core/store/IMultiStore.hpp',
'./include/core/store/ConfigManager.hpp',
'./include/core/store/KeyValueStore.hpp',
'./include/core/store/ConfigReader.hpp',
'./include/core/store/IKeyValueStore.hpp',
'./include/core/store/IMultiLevelStore.hpp',
'./include/core/property/SimpleProperty.hpp',
'./include/core/property/IPropertyManager.hpp',
'./include/core/property/IProperty.hpp',
'./include/core/property/IKeyableProperty.hpp',
'./include/core/property/PropertyManager.hpp',
'./include/core/property/SimpleKeyableProperty.hpp',
'./include/core/action/SinusGenerator.hpp',
'./include/core/action/BaseAction.hpp',
'./include/core/action/TerminalPrinter.hpp',
'./include/core/action/IAction.hpp',
'./include/core/action/IControl.hpp',
'./include/core/util/BaseObservable.hpp',
'./include/core/util/IObserver.hpp',
'./include/core/util/String.hpp',
'./include/core/util/AudioException.hpp',
'./include/core/util/UniqueID.hpp',
'./include/core/util/BaseObserver.hpp',
'./include/core/util/IObservable.hpp',
'./include/core/util/Util.hpp',
'./include/core/util/sptr.hpp',
'./include/core/scene/Scene.hpp',
'./include/core/serializer/ISerializable.hpp',
'./include/core/serializer/TXTSerializer.hpp',
'./include/core/serializer/ISerializer.hpp',
'./include/core/audiodata/AudioInfo.hpp',
'./include/core/audiodata/IAudioInfo.hpp',
'./include/core/audiodata/Sample.hpp',
'./include/core/audiodata/IAudioBuffer.hpp',
'./include/core/audiodata/FileInfo.hpp',
'./include/core/audiodata/AudioQueue.hpp',
'./include/core/audiodata/ISample.hpp',
'./include/core/audiodata/AudioBuffer.hpp',
'./include/core/pluginmanager/PluginManager.hpp',
'./include/core/pluginmanager/PluginLoader.hpp',
'./include/maudio.hpp',
'./include/extended/audiosink/FileWriter.hpp',
'./include/extended/audiosink/Player.hpp',
'./include/extended/audiosource/BulkReader.hpp',
'./include/extended/audiosource/StreamReader.hpp',
]

testsrc = [
'./examples/test1.cpp',
]

maudiolib = shared_library('maudio',
	sources: src,
	include_directories: [headerdir, srcdir],
	dependencies: maudiodep,
	install_dir: './res/lib',
	install: true)

static_library('maudio',
	sources: src,
	include_directories: [headerdir, srcdir],
	dependencies: maudiodep,
	install_dir: './res/lib',
	install: true)

executable('maudio_test',
	sources: testsrc,
	#sources:[src, testsrc],
	include_directories: [headerdir, srcdir],
	link_with: maudiolib,
	dependencies: maudiodep,
	install_rpath: './res/lib',
	install_dir: '.',
	install: true)








