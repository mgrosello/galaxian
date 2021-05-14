cd build
git remote add origin https://github.com/mgrosello/mgrosello.github.io.git
git add *.data
git add *.js
git add *.wasm
git add *.html
git commit -m 'subir'
git push origin HEAD:main
cd ..
