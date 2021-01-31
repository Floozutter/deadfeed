# deadfeed
kill your camera feed!

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
deadfeed 0
```
to run with droidcam:
```
deadfeed "http://0.0.0.0:4747/mjpegfeed"
```

to quit, press `Esc`

to save the current frame on Windows, press `Ctrl+C` (clipboard) or `Ctrl+S` (file)
