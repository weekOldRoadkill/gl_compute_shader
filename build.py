#!/usr/bin/env python




# -- Libraries --
import os
import platform
# ---------------




# -- Functions --
def run(*args):
	cmd = ""
	for arg in args:
		cmd += arg+' '

	print("\x1B[95m"+cmd+"\x1B[0m")

	if(os.system(cmd)):
		exit(0x01)

	print("\n")
# ---------------




# -- Checks --
if(platform.system() != "Linux"):
	print("OS not supported.")
	exit()

run("mkdir", "build")
run("clear")
# ------------




# -- Linux Arguments --
cc = "clang"


comp = [
	"-s",
	"-xc",
	"-flto",
	"-Ofast",
	"-std=c99",
	"-fuse-ld=lld",
	"-march=native",
	"-mtune=native",
	"--target=x86_64-pc-linux-gnu"
]


comp_path = [
	"-Lsrc/lodepng/lib",
	"-Isrc/lodepng/include"
]


comp_warn = [
	"-Wall",
	"-Werror",
	"-Wextra"
]


comp_src = [
	"src/*.c"
]


comp_lib = [
	"-lGLEW",
	"-lglfw",
	"-llodepng",
	"-lpthread"
]


out = "build/gl_compute_shader"
# ---------------




# -- Building --
run(cc, *comp, *comp_path, *comp_warn, "-o"+out, *comp_src, *comp_lib)

run("file", out)

run("ldd", out)
# --------------




# -- Testing --
run("cd", "build", "&&", "./"+out[0x06:])
# -------------