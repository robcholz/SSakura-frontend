add_includedirs("third-party/fixed-containers/include")

target("ssakura-frontend")
if is_mode("debug") then
    set_kind("shared")
elseif is_mode("release") then
    set_kind("static")
end
add_includedirs("include")
add_headerfiles("include/**.hpp")
add_files("src/**.cpp")
add_packages("logging")
--add_packages("boost")
add_packages("magic_enum")
--add_packages("llvm")
target_end()