sudo cp library.h /usr/lib/gcc/x86_64-linux-gnu/11/include &&
	gcc -rdynamic -O3 -o libform.so library.c $(pkg-config --cflags gtk4) $( pkg-config --libs gtk4 ) -s -shared -D LIB_EXPORTS -g  &&
sudo cp libform.so /usr/lib/gcc/x86_64-linux-gnu/11 &&
sudo cp libform.so /usr/lib
