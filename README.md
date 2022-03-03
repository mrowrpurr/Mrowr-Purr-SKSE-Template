# Mrowr Purr's SKSE plugin template



## Dependencies

- [git](https://git-scm.com/downloads)
- [CMake](https://cmake.org/download/)

## Setup Project Folder

This template uses git submodules to pull in recent versions  
of CommonLibSSE (_separate versions for AE vs SE_), CommonLibVR, 
and vcpkg (_separate versions for each version of Skyrim_).

You must run these commands to setup the git submodules:

```
git submodule init
git submodule update
```

## Setup Environment Variables

This template uses environment variables to specify where
compiled SKSE plugin .dlls and Papyrus files should be output.

- `SKSE_SKYRIM_AE_DEV="C:\My Mods\My AE Development\"`
- `SKSE_SKYRIM_SE_DEV="C:\My Mods\My SE Development\"`
- `SKSE_SKYRIM_VR_DEV="C:\My Mods\My VR Development\"`

> When the appropriate environment variable(s) is/are not set,  
> compiled plugins are output in the output/ directory. 

It is particularly useful to have separate mods for each version  
of Skyrim setup in your mod organizer, e.g. MO2.
