project "Example"
location "Example"
kind "ConsoleApp"
language "C++"
cppdialect "C++17"
staticruntime "off"
systemversion "latest"

pchheader "stdafx.h"
pchsource "%{prj.name}/stdafx.cpp"

targetdir("../Build/Bin/"..outputDir.."/%{prj.name}")
objdir("../Build/Bin-int/"..outputDir.."/%{prj.name}")

prebuildcommands 
{ 
	"{COPYFILE} %[%{wks.location}/Vendor/SFML-2.6.1/bin/**.dll] %[%{wks.location}/Build/Bin/"..outputDir.."/%{prj.name}]",
}

files
{
	"%{prj.name}/**.cpp",
	"%{prj.name}/**.h",
}

includedirs
{
	"%{prj.name}",
	"%{wks.location}/Vendor/SFML-2.6.1/include/",
}

libdirs
{
	"%{IncludeDir.SFML}/lib/%{cfg.buildcfg}/",
	"%{IncludeDir.SFML}/lib/",
}

links
{
	"flac.lib",
	"freetype.lib",
	"ogg.lib",
	"vorbis.lib",
	"vorbisenc.lib",
	"vorbisfile.lib",
	"openal32.lib",
	"sfml-audio.lib",
	"sfml-graphics.lib",
	"sfml-main.lib",
	"sfml-network.lib",
	"sfml-system.lib",
	"sfml-window.lib",
}

filter "system:Windows"
defines
{
	"DEF_PLATFORM_WINDOWS",
}

filter "configurations:Debug"
defines "DEF_DEBUG"
runtime "Debug"
symbols "On"

filter "configurations:Release"
defines "DEF_RELEASE"
runtime "Release"
optimize "On"
