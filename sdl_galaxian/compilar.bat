rem docker run --name emscripten -v %cd%:/src emscripten/emsdk:latest /bin/bash -c "make"
docker start -i emscripten
