-- set minimum xmake version
set_xmakever("2.8.2")

-- includes
includes("lib/commonlibsse-ng")

-- set project variables
local projectName = "Immersive Behaviors"
local projectLoc = "D:/GameUtils/Skyrim/MO2/instances/SSE/mods/" .. projectName .. "/SKSE/Plugins/"

-- set project
set_project(projectName)
set_version("0.0.1")
set_license("GPL-3.0")

-- set defaults
set_languages("c++23")
set_warnings("allextra")

-- set policies
set_policy("package.requires_lock", true)

-- add rules
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

-- targets
target(projectName)
    -- add dependencies to target
    add_deps("commonlibsse-ng")

    -- add commonlibsse-ng plugin
    add_rules("commonlibsse-ng.plugin", {
        name = projectName,
        author = "Sorre",
        description = "SKSE64 plugin"
    })

    -- add src files
    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    set_pcxxheader("src/pch.h")

    after_build(function (target)
        os.cp(target:targetdir() .. "/" .. projectName .. ".dll", projectLoc)
        os.cp(target:targetdir() .. "/" .. projectName .. ".pdb", projectLoc)
    end)
