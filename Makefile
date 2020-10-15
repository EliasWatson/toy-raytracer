build_debug:
	g++ -g -o raytracer_debug src/*.cpp src/*.h

build_release:
	g++ -O3 -o raytracer_final src/*.cpp src/*.h
