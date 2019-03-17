all: clean

clean: run
	@rm src/vpl_wexecution

run: build
	@./src/vpl_wexecution

build:
	@gcc `pkg-config --cflags gtk+-3.0 gtkmm-3.0` -o src/vpl_wexecution src/main.cpp `pkg-config --libs gtk+-3.0 gtkmm-3.0` -rdynamic -lstdc++ -std=c++11 -lm
