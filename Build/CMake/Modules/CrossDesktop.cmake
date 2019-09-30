set(CROSS_DESKTOP TRUE)

# Check whether the CEF submodule is available
if (NOT MINGW)
    if (NOT DEFINED CROSS_WEBVIEW)
        set (CROSS_WEBVIEW OFF)
    endif ()
    if (CROSS_WEBVIEW)
        initialize_submodule(Submodules/CEF CROSS_WEBVIEW)
        if (CROSS_WEBVIEW)
            add_definitions(-DCROSS_WEBVIEW)
        endif ()
    endif ()
endif ()
