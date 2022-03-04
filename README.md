# Mrowr Purr's SKSE plugin template 😼

> _If you use this template, **please make your SKSE plugin Open Source**_ ✨

- [Dependencies](#)
- [Setup Plugin Name and Version](#)
- [Configure Open Source License](#)
- [Setup Project Folder](#)
- [Setup Environment Variables](#)
- [Building the project for different versions of Skyrim](#)
- [Upgrading to Newer Versions of CommonLib](#)
- [Upgrading to Newer Packages via vcpkg](#)

# Dependencies

- [git](https://git-scm.com/downloads)
- [CMake](https://cmake.org/download/)

# Setup Plugin Name and Version

Open `CMakeLists.txt` and configure your project name and version:

```cmake
# Set your SKSE plugin name and version.
project(
	ExampleProject
	VERSION 1.0.0
	LANGUAGES CXX
)
```

# Setup Project Folder

This template uses git submodules to pull in recent versions  
of CommonLibSSE (_separate versions for AE vs SE_), CommonLibVR, 
and vcpkg (_separate versions for each version of Skyrim_).

You must run these commands to setup the git submodules:

```
git submodule init
git submodule update
```

# Setup Environment Variables

## Output directly to your MO2/Nexus Mods folder

If you set the environment variable `SKYRIM_MODS="C:\Path\To\Mods"`
building will find or create a `C:\Path\To\Mods\[Plugin Name] - [Skyrim Version]\`
folder containing your `SKSE\Plugins\` plugin `.dll` and `.pdb`
and any Papyrus scripts will also be copied over into `C:\Path\To\Mods\[Plugin Name] - [Skyrim Version]\`

Example: `C:\Path\To\Mods\MyMod - AE`

## Configure Specific Output Folders

If you have different mod folder root paths for different versions of Skyrim
or would simply like to output the files in a different location, you can set these environment variables:

- `SKSE_SKYRIM_AE_DEV="C:\My Mods\My AE Development\"`
- `SKSE_SKYRIM_SE_DEV="C:\My Mods\My SE Development\"`
- `SKSE_SKYRIM_VR_DEV="C:\My Mods\My VR Development\"`

If you have these set, they will be used instead of the `SKYRIM_MODS` environment variable, if set.

## Default output path: `output/`

If neither `SKYRIM_MODS` nor the respective `SKSE_SKYRIM_[version]_DEV` variable are set,
then the plugin output will be put into the relative `./output/` folder here in the project.

# Building the project for different versions of Skyrim

To setup the project to build for Anniversary Edition

---

# TODO

- [ ] script to build all (AE, SE, and VR) and ideally stop on error
- [ ] .zip packaging!