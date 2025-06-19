local WWGM_HOME = os.getenv("UWGM_HOME")
local WWGMTK_HOME = os.getenv("UWGM_TK_HOME")

workspace "UWGMNeutralDataAttachPlugin"
    configurations { "Debug", "Release", "Distribution" }
    startproject "UWGMNeutralDataAttachPlugin"
	location "../.."

project "UWGMNeutralDataAttachPlugin"
    architecture "x86_64"
    location "../../UWGMNeutralDataAttachPlugin"
    kind "SharedLib"
    language "C++"
    cppdialect "C++14"
    staticruntime "off"

    targetdir ("%{prj.location}/bin/%{cfg.buildcfg}")
    objdir ("%{prj.location}/bin-int/%{cfg.buildcfg}")
	
	pchheader "pch.hpp"
    pchsource "%{prj.location}/src/pch.cpp"

    files {
        "%{prj.location}/src/**.cpp", "%{prj.location}/src/**.cxx", "%{prj.location}/src/**.c", "%{prj.location}/src/**.h", "%{prj.location}/src/**.hpp"
    }

    vpaths {
        ["Source Files"] = { "%{prj.location}/src/**.cpp" ,"%{prj.location}/src/**.c" },
        ["Header Files"] = { "%{prj.location}/src/**.hpp", "%{prj.location}/src/**.h" }
    }

    includedirs {
        "%{prj.location}/src",
        WWGMTK_HOME .. "/src/includes"
    }

    libdirs {
        WWGMTK_HOME .. "/lib/x86e_win64/obj"
    }

    links {
        "wwgmtkclienttop",
        "wwgmtkcc",
        "wwgmtkpdmactions",
        "genpdmintfmt",
        "genpdmintf_s_s11n.obj",
        "cipsoapmt",
        "cipbcpmt",
        "xmlutilmt",
        "xercescmt",
        "cipbase_s_s11n.obj",
        "cipstdmt",
        "ctoolsmt",
        "baselibmt",
        "i18nmt",
        "utfstrmt",
        "rtlcoremt",
        "kernel32",
        "user32",
        "wsock32",
        "advapi32",
        "ws2_32",
        "winspool",
        "netapi32",
        "mpr",
        "ole32",
        "gdi32",
        "shell32",
        "comdlg32",
        "psapi"
    }

    buildoptions {
        "/W3", "/EHsc", "/GR-", "/wd4430", "/fp:precise",
        "/GL-",
        "/Dfinite=_finite", "/Dhypot=_hypot",
        "/DMSB_LEFT", "/Dfar=ptc_far", "/Dhuge=p_huge", "/Dnear=p_near",
        "/DDAYTONA", "/DWIN32", "/D_WIN32_WINNT=0x0501",
        "/D_WIN32_IE=0x0600", "/DWINVER=0x0501",
        "/DPRO_MACHINE=36", "/DGRAPHICS=9", "/DOPER_SYS=4",
        "/DPLATFORM=36", "/DWINDOWS_PROTK_DEBUG",
        "/DPLPF_DEBUG", "/DLM_INTERNAL", "/DPLPF_LICSOURCE_DEBUG",
        "/DWIDECHARS", "/DKANJI", "/DTHREAD_SAFE_MODE"
    }

    linkoptions {
        "/nologo", "/subsystem:console", "/machine:amd64", "/dll", "/debug",
        "/EXPORT:wwgmtkGetCustomizer"
    }

    filter "configurations:Debug"
        defines { "DEBUG"}
        symbols "On"
        runtime "Release" -- force /MD swith even on debug
		buildoptions { "/GS-", "/Od", "/ZI", "/Wall" }

    filter "configurations:Release"
        defines { "NDEBUG", "RELEASE" }
        optimize "On"
        runtime "Release"
	
	filter "configurations:Distribution"
        defines { "NDEBUG", "DISTRIBUTION" }
        optimize "On"
        runtime "Release"