target("anemos-interpreter")
if is_mode("debug") then
    set_kind("shared")
elseif is_mode("release") then
    set_kind("static")
end
add_includedirs("include")
add_headerfiles("include/**.hpp")
add_files("src/**.cpp")
add_deps("ssakura-frontend")
target_end()

--target("anemos-interpreter-test")
--set_kind("binary")
--add_files("test/*.cpp")
--add_includedirs("include")
--add_deps("anemos-interpreter")
--add_packages("catch")
--add_packages("logging")
--target_end()
