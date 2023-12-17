# Mygstreamer
This is my "Hello world" program for GStream library in C. Program plays video from given URI.

Command line for compilation: 
```bash
gcc main.c -o main `pkg-config --cflags --libs gstreamer-1.0`
```

Dependencies: gstreamer-1.0