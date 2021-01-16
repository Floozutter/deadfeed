# camfx
Add silly effects to a camera feed!

## Usage
To build with x64 Native Tools Command Prompt for VS 2019:
```
cl /EHsc -I"C:\opencv\build\include" src\main.cpp "C:\opencv\build\x64\vc15\lib\opencv_world440.lib" /Fo"src\\" /link /out:build\main.exe
```

To run with the default camera:
```
build\main 0
```

To run with DroidCam:
```
build\main "http://0.0.0.0:4747/mjpegfeed"
```

To save the current frame on Windows, press Ctrl+C (clipboard) or Ctrl+S (file).
