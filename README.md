# beamsyncctl
Small application to toggle on and off Beam Sync with some extra kicks

Extra stuff:
1. Prints verbose info
2. CLI utility only depending on CoreGraphics Framework
3. CoreGraphics return codes and function prototypes are documented

This is mainly designed for people to understand how this works with CoreGraphics, since return codes are displayed and documented.

# Compilation
```clang -o beamsyncctl main.c -framework CoreGraphics```

# Output example
```
$ ./beamsyncctl -d
CGSGetDebugOptions(0x7fff55e14bc4) = 0
options = 0x0
CGSSetDebugOptions(0x8000000) = 0
CGSDeferredUpdates(0x0) = 0

$ ./beamsyncctl -e
CGSGetDebugOptions(0x7fff57198bc4) = 0
options = 0x8000000
CGSSetDebugOptions(0x0) = 0
CGSDeferredUpdates(0x2) = 0

$ ./beamsyncctl -p
CGSGetDebugOptions(0x7fff5c1abbc4) = 0
options = 0x0
```

Enjoy!
