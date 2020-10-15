build_debug:
	g++ -g -std=c++11 -pthread -o raytracer_debug src/*/*.h src/*/*.cpp src/*.cpp

build_release:
	g++ -O3 -std=c++11 -pthread -o raytracer_final src/*/*.h src/*/*.cpp src/*.cpp
