set_project("SSakura-frontend")
add_rules("mode.debug", "mode.release")
set_languages("cxx23")
set_targetdir("bin")

add_requires("conan::catch2/3.4.0", { alias = "catch" })
add_requires("conan::spdlog/[>=1.4.1]", { alias = "logging" })
--add_requires("conan::boost/1.84.0",{alias = "boost",configs={math=true,system=true}})
add_requires("conan::magic_enum/0.9.5", { alias = "magic_enum" })
--add_requires("vcpkg::llvm 17.0.2",{alias="llvm"})

if is_mode("debug") then
    set_optimize("none")
elseif is_mode("release") then
    set_optimize("fastest")
end

-- treat all warnings as errors
set_warnings("all")
set_warnings("error")

includes("frontend/xmake.lua")
includes("backend/anemos/xmake.lua")
includes("ssakura_lang/xmake.lua")
