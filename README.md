# camfx
Add silly effects to a camera feed!

## Usage
To build:
```
$ cl /EHsc -I"C:\opencv\build\include" src\main.cpp "C:\opencv\build\x64\vc15\lib\opencv_world440.lib" /Fo"src\" /link /out:build\main.exe
```

To run with DroidCam:
```
$ build\main "http://0.0.0.0:4747/"
```
