
useful stuff:


reload soundserver:

pulseaudio -k && sudo alsa force-reload


find all source files:

find ./src -name "*.cpp"
find ./include -name "*.hpp"


for cmake:

echo set\(MAUDIO_SOURCE_FILES > sources.txt && \
find ./src -name "*.cpp" | \
while read a; do echo -e '\t'\$\{PROJECT_SOURCE_DIR\}/`echo $a | tail -c +3` >> sources.txt; done &&\
echo -e \) "\n" >> sources.txt &&\
\
echo set\(MAUDIO_INCLUDE_FILES >> sources.txt && \
find ./include -name "*.hpp" | \
while read a; do echo -e '\t'\$\{PROJECT_SOURCE_DIR\}/`echo $a | tail -c +3` >> sources.txt; done &&\
echo -e \) >> sources.txt;


for meson:

echo src = [ > sources.txt && find ./src ./include \( -name "*.cpp" -o -name "*.hpp" \) | while read a; do echo \'$a\', >> sources.txt; done && echo ] >> sources.txt


number of lines:

find . -name \*.cpp -or -name \*.hpp -exec cat {} \; | wc -l

