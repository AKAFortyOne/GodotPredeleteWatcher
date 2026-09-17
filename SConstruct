import os

LIB_BASENAME = "FortyOne.GodotDeathWatcher"
OUTPUT_DIR = "project/bin"

env = SConscript("godot-cpp/SConstruct", {"api_version": "4.7", "use_static_cpp": "true"})

env.Append(CPPPATH=["src/"])

env.VariantDir("build", 'src', duplicate=0)

all_sources = set(Glob("build/*.cpp") + Glob("build/**/*.cpp"))
bak_sources = set(Glob("build/*.bak.cpp") + Glob("build/**/*.bak.cpp"))
sources = list(all_sources - bak_sources)

variant = env["target"].removeprefix("template_")

lib_filename = "{}_{}{}".format(
    LIB_BASENAME,
    variant,
    env.subst("$SHLIBSUFFIX"),
)

library = env.SharedLibrary(os.path.join(OUTPUT_DIR, lib_filename), source=sources)

Default(library)

env.Tool('compilation_db')
env.Alias('compiledb', env.CompilationDatabase('compile_commands.json'))