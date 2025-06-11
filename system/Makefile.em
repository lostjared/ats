all:
	em++ -std=c++20 -O2 *.cpp -o ats.js -I./include --bind -s WASM=1 -s MODULARIZE=1 -s EXPORT_NAME="ATS"

clean:
	rm -f *.o *.wasm *.data *.js

debug:
	em++ -std=c++20 -g4 *.cpp -o ats.js -I./include --bind -s WASM=1 -s MODULARIZE=1 -s EXPORT_NAME="ATS" -s ASSERTIONS=1
