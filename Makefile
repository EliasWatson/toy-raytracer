build_debug:
	g++ -g -o raytracer_debug src/*.h src/*.cpp

build_release:
	g++ -O3 -o raytracer_final src/*.h src/*.cpp
