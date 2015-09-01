
useful stuff:

reload soundserver:
pulseaudio -k && sudo alsa force-reload

find all source files:

find ./src ./include \( -name "*.cpp" -o -name "*.hpp" \)
for cmake:
echo set\(MAUDIO_SOURCE_FILES > sources.txt && find ./src ./include \( -name "*.cpp" -o -name "*.hpp" \) | while read a; do echo -e '\t'$a >> sources.txt; done && echo \) >> sources.txt

for meson:
echo src = [ > sources.txt && find ./src ./include \( -name "*.cpp" -o -name "*.hpp" \) | while read a; do echo \'$a\', >> sources.txt; done && echo ] >> sources.txt

