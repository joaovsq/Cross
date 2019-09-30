set(JAVASCRIPT_BINDINGS_PLATFORM "WINDOWS")

message("CROSS WINDOWS CMAKE ------------------------------------------------------------")

include(CrossDesktop)

#set (CMAKE_DEBUG_POSTFIX _d)

set(D3DCOMPILER_47_DLL ${CROSS_SOURCE_DIR}/Build/Windows/Binaries/${CROSS_PROJECT_ARCH_SHORT}/D3DCompiler_47.dll)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# compile with static runtime
if (MSVC)
    if (CROSS_DYNAMIC_RUNTIME)
        set(CROSS_MSVC_RUNTIME /MD)
    else ()
        set(CROSS_MSVC_RUNTIME /MT)
    endif ()
    msvc_set_runtime(${CROSS_MSVC_RUNTIME})
else ()
    set (CROSS_WEBVIEW 0)
endif ()
