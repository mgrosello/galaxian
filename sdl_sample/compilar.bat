rem docker run --name emscripten -v %cd%:/src emscripten/emsdk:latest /bin/bash -c "emcc -c sdl_2_0_sample.c -o sdl_2_0_sample.o -s USE_SDL=2 && emcc sdl_2_0_sample.o -o sdl_2_0_sample.html -s USE_SDL=2"
docker start -i emscripten 
