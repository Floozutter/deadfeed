# deadfeed
kill your camera feed!

## generate
```
mkdir build
cd build
cmake .. -D CMAKE_PREFIX_PATH="path/to/opencv"
```

## build
```
cmake --build . --config Release
```

## usage
```
deadfeed example.cfg
```

to quit, press `esc`

to reload config, press `r`

to save the current frame on Windows, press `Ctrl+C` (clipboard) or `Ctrl+S` (file)
