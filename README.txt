
useful stuff:

reload soundserver:
pulseaudio -k && sudo alsa force-reload

find all source files:

find . \( -name "*.cpp" -o -name "*.hpp" \)
echo sources = [ > src.txt && find . \( -name "*.cpp" -o -name "*.hpp" \) | while read a; do echo \'$a\,' >> sources.txt; done && echo ] >> sources.txt