set_project("SSakura-frontend")
add_rules("mode.debug","mode.release")
set_languages("cxx20")
set_targetdir("bin")

add_requires("llvm 14.0.0",{alias="llvm"})
add_requires("conan::catch2/3.4.0",{alias="catch"})

--add_requires("conan::boost/1.81.0",{alias = "boost"})
--add_requires("conan::nlohmann_json/3.7.3",{alias = "json"})

target("SSakura-frontend")
    set_kind("shared")
    add_headerfiles("$(projectdir)/include/**.hpp")
    add_includedirs("$(projectdir)/include")
    add_files("$(projectdir)/src/**.cpp")

    add_includedirs("$(projectdir)/third-party/fixed-containers/include")

    add_packages("llvm")

target("SSakura-Test")
    set_kind("binary")
    add_files("$(projectdir)/test/*.cpp")

    add_includedirs("$(projectdir)/include")
    add_deps("SSakura-frontend")

    add_packages("catch")

