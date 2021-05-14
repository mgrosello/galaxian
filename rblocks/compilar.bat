docker run --rm --name emscripten -v %cd%:/src emscripten/emsdk:latest /bin/bash -c "make "
rem docker start -i emscripten 
