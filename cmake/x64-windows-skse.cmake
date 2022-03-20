set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)

if (${PORT} MATCHES "skse")
    set(VCPKG_LIBRARY_LINKAGE dynamic)
    set(VCPKG_CRT_LINKAGE static)
elseif (${PORT} MATCHES "fully-dynamic-game-engine|openvr")
    set(VCPKG_LIBRARY_LINKAGE dynamic)
else ()
    set(VCPKG_LIBRARY_LINKAGE static)
endif ()
