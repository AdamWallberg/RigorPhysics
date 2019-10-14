solution("RigidPhysics")
	language "C++"
	debugdir "$(OutDir)"
	objdir "build/"
	targetdir "$(SolutionDir)../app/"
	targetname "$(ProjectName)_$(Configuration)_$(Platform)"
	systemversion "10.0.17763.0" 
	
	configurations {
		"Debug",
		"Release",
	}
	
	platforms {
		"Win32",
		"x64",
	}
	
	configuration "Debug"
		symbols "On"
		defines {
			"DEBUG",
		}
		
	configuration "Release"
		optimize "On"
		defines {
			"RELEASE",
			"NDEBUG",
		}
	
	configuration {}
	
	
project("RigidPhysics")
	kind "StaticLib"
	
	includedirs {
		"code/",
	}
	
	files {
		"code/**.cpp",
		"code/**.h",
		"code/**.hpp",
	}