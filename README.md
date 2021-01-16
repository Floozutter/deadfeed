# camfx
add silly effects to a camera feed!

## build
```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## usage
to run with the default camera:
```
camfx 0
```
to run with droidcam:
```
camfx "http://0.0.0.0:4747/mjpegfeed"
```
to save the current frame on Windows, press Ctrl+C (clipboard) or Ctrl+S (file)
