all: main

main: main.cpp myWindow.cpp myWindow.h drawer.cpp drawer.h
	g++ -std=c++11 -DBOOST_LOG_DYN_LINK drawer.cpp myWindow.cpp main.cpp -o main $$(pkg-config gtkmm-3.0 --cflags --libs) -lpthread -lboost_log -lboost_log_setup

test: main.cpp myWindow.cpp myWindow.h drawer.cpp drawer.h
	g++ -std=c++11 -DBOOST_LOG_DYN_LINK drawer.cpp myWindow.cpp main.cpp -o test $$(pkg-config gtkmm-3.0 --cflags --libs) -lpthread -lboost_log -lboost_log_setup

test-no-log: main.cpp myWindow.cpp myWindow.h drawer.cpp drawer.h
	g++ -std=c++11 drawer.cpp myWindow.cpp main.cpp -o test-no-log $$(pkg-config gtkmm-3.0 --cflags --libs) -lpthread

make clean:
	rm ./main
	rm *.o
