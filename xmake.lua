set_project("SSakura-frontend")
add_rules("mode.debug","mode.release")
set_languages("cxx20")
set_targetdir("bin")


add_requires("conan::catch2/3.4.0",{alias="catch"})
add_requires("conan::spdlog/[>=1.4.1]",{alias="logging"})
add_requires("conan::boost/1.81.0",{alias = "boost",configs={math=true,system=true}})
add_requires("conan::magic_enum/0.9.5",{alias="magic_enum"})

--add_requires("conan::nlohmann_json/3.7.3",{alias = "json"})


target("SSakura-frontend")
    set_kind("shared")
    add_includedirs("$(projectdir)/include")
    add_headerfiles("$(projectdir)/include/**.hpp")
    add_files("$(projectdir)/src/**.cpp")
    add_packages("logging")
    add_packages("boost")
    add_packages("magic_enum")
target_end()

target("SSakura-Test")
    set_kind("binary")
    add_files("$(projectdir)/test/*.cpp")
    add_includedirs("$(projectdir)/include")
    add_deps("SSakura-frontend")
    add_packages("catch")
    add_packages("llvm")
    add_packages("logging")
target_end()



