# Mrowr Purr's SKSE plugin template 😼

> _If you use this template, **please make your SKSE plugin Open Source**_ ✨

`<Insert YouTube Tutorial Video Here>`

# Overview

- [Dependencies](#dependencies)
- [Download or Use Project Template](#download-or-use-project-template)
- [Setup Plugin Name and Version](#setup-plugin-name-and-version)
- [Configure Open Source License](#configure-open-source-license)
- [Setup Project Folder](#setup-project-folder)
- [Setup Environment Variables](#setup-environment-variables)
- [Building the project (for different versions of Skyrim)](#building-the-project-for-different-versions-of-skyrim)
- [Upgrading to Newer Versions of CommonLibSSE and CommonLibVR](#upgrading-to-newer-versions-of-commonlibsse-and-commonlibvr)
- [Upgrading to Newer vcpkg Packages](#upgrading-to-newer-vcpkg-packages)
- [Working with Papyrus scripts](#working-with-papyrus-scripts)
- [Writing Unit Tests for C++](#writing-unit-tests-for-c--)
- [Example Project Features](#)
  - [Logging](#)
  - [Game Load Events](#)
  - [Papyrus Interfaces](#)
  - [Reading .ini Files](#)
  - [Form Querying](#)
  - [Script Reflection](#)

# Dependencies

- [git](https://git-scm.com/downloads)
- [CMake](https://cmake.org/download/)

# Download or Use Project Template

The easiest way to get started it by using the **`Use this template`** button on this GitHub repository.

That will create a copy of this repository of your own to get started with!

Alternatively, git clone the project:

```
git clone https://github.com/mrowrpurr/Mrowr-Purr-SKSE-Template.git
```

> _If you are new to `git`, I highly recommend using the [GitHub Desktop](https://desktop.github.com/) application. It works with GitHub, GitLab, or any hosted or local git._

# Setup Plugin Name and Version

Once you have the code downloaded, open `CMakeLists.txt` and configure your project name and version:

```cmake
# Set your SKSE plugin name and version.
project(
	ExampleProject
	VERSION 1.0.0
	LANGUAGES CXX
)
```

# Configure Open Source License

Please make your SKSE plugin publicly available on GitHub with one of these recommended Open Source Licenses:

- MIT
- Apache 2.0
- BSD

This project includes an MIT `LICENSE` file which you can edit.

I recommend MIT. CommonLibSSE is MIT. Many Skyrim projects use MIT.

Open `LICENSE` and simply add your name:

```
MIT License

Copyright (c) 2022 <Your Name Here>

Permission is hereby granted, free of charge, to any person obtaining a copy ...
```

> You can review the [differences of Open Source Licenses](https://www.kiuwan.com/comparison-popular-open-source-licenses/) if so desired.
>
> _Please only use GPL licenses is you fully understand open source licenses and the impact of releasing software under GPL licenses. Otherwise - don't._

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

The easiest way to get started is to set an environment variable which points to your MO2 or Nexus mods folder.

```
SKYRIM_MODS="C:\Path\To\Mods"
```

> To set this:
> 1. Hit the Start key
> 2. Start typing "_Edit the system environment variables_" and choose the option
> 3. Click `Environment Variables...`
> 4. Choose `New...` under _"User variables for [user]"
> 5. Set `Variable name:` to `SKYRIM_MODS`
> 6. Set `Variable value:` to the path to your mods folder

With this configured, whenever you build your project a directory will be created in your mods folder named `[Your Project Name] - [Skyrim Version]`:
- e.g. `MyProject - AE` or `CoolProject - VR`.

Different folders are created for different versions of Skyrim.

## Configure Specific Output Folders

A more advanced, but simple, option is to configure different paths for mods for different versions of Skyrim.

If you have different mod folder root paths for different versions of Skyrim
or would simply like to output the files in a different location, you can set these environment variables:

- `SKSE_SKYRIM_AE_DEV="C:\My Mods\My AE Development\"`
- `SKSE_SKYRIM_SE_DEV="C:\My Mods\My SE Development\"`
- `SKSE_SKYRIM_VR_DEV="C:\My Mods\My VR Development\"`

If you have these set, they will be used instead of the `SKYRIM_MODS` environment variable, if set.

## Default path: `output/`

If neither `SKYRIM_MODS` nor the respective `SKSE_SKYRIM_[version]_DEV` variable(s) are set,
then the plugin output will be put into the relative `./output/` folder here in the project.

# Building the project (for different versions of Skyrim)

To build the project for a certain version of Skyrim, you must "prepare" the project for that version.

To do so, run the PREPARE .bat file in the project folder for your version of Skyrim:

```
./PREPARE_AE.bat
```

This will run `cmake` and generate the contents of the `build/` folder, preparing it to compile and output your SKSE plugin.

Then, build the project!

```
./BUILD.bat
```

This compiles the project. Any compilation errors should be visible. If there are none, file should be output to your configured output location from the [Setup Environment Variables](#setup-environment-variables) step.

# Upgrading to Newer Versions of CommonLibSSE and CommonLibVR

CommonLibSSE and CommonLibVR are included in the project as git submodules.

The submodules are located here:

```
CommonLib/
  AE/ --> https://github.com/powerof3/CommonLibSSE
  SE/ --> https://github.com/powerof3/CommonLibSSE
  VR/ --> https://github.com/mrowrpurr/CommonLibVR
```

At the time of writing, the most frequently updated versions of CommonLib are:
- [`powerof3`](https://github.com/powerof3/CommonLibSSE/)'s **CommonLibSSE** repository with `dev` and `dev-ae` branches for SE and AE
- [`lfrazer`](https://github.com/lfrazer/CommonLibVR)'s **CommonLibVR** repository (_which I forked and made a lazy hack to make it compile which I'll cleanup later but it works_)

The way that git submodules work is:

- Each submodule is pinned to a certain commit for the repository

So if you want to update to the latest CommonLibSSE, here are the steps that I _currently_ recommend:

```
# Update AE to the latest dev-ae
cd CommonLib/AE
git checkout dev-ae
git pull origin dev-ae

# Update SE to the latest dev
cd ../SE
git checkout dev
git pull origin dev
```

At the time of writing, I have AE and SE pinned to specific commits because the latest `dev` and `dev-ae` didn't compile for me so I went back just a couple of commits.

For CommonLibVR, I will try to keep mrowrpurr/CommonLibVR up-to-date. Otherwise you may want to switch to a different person's CommonLibVR by [updating the submodule to point at a different remote repository](https://stackoverflow.com/a/914090).

# Upgrading to Newer vcpkg Packages

Just like `CommonLib` projects, `vcpkg` is included in this project as a submodule with separate versions for each version of Skyrim.

Why? Why not just have 1 `vcpkg` globally on the system? Or 1 `vcpkg` for the repository?

Sometimes CommonLibSSE/CommonLibVR don't work with the latest versions of public packages, so - to ensure this project tempalte **always compiles** - I have submodules for `vcpkg` for each version of Skyrim pinned to a specific version.

To update `vcpkg` for any version of Skyrim:

```
# Update AE (or SE or VR)
cd vcpkg/AE
git checkout master
git pull origin master
```

# Working with Papyrus scripts

One of the awesome features of Skyrim Script Extender (SKSE) is that it can **extend scripts**.

```cpp
SKSE::GetPapyrusInterface()->Register(PapyrusFunctions);
```

In addition to being configured as a C++ CMake project,
this project folder is also configured as a Papyrus Project.

... `TODO DOCUMENTATION` ...

# Writing Unit Tests for C++

... `TODO DOCUMENTATION` ...

# Example Project Features

... `TODO` ...

---

# TODO

- [ ] script to build all (AE, SE, and VR) and ideally stop on error
- [ ] .zip packaging!
- [ ] .ini reading
- [ ] add a few forms of Form querying/lookup
- [ ] add an example or two of Script reflection and function invocation
