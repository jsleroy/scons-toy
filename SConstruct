import os

import SCons
from SCons.Script.SConscript import SConsEnvironment

def install(dest, perm, strip = None):
    def f(env, files, path = ""):
        obj = env.Install(env.Dir(os.path.join(env['PREFIX'], dest, path)), files)
        if strip is not None:
            env.AddPostAction(obj, Action("echo strip %s $TARGETS" % strip))
        env.AddPostAction(obj, Chmod(obj, perm))
        return obj
    return f

variables = Variables()
variables.Add("PREFIX", "installation prefix", "usr")

env = Environment(
    variables = variables,
)

variables.Update(env)
Help(variables.GenerateHelpText(env))

env["PREFIX"] = os.path.abspath(env["PREFIX"])

env.AddMethod(install("bin",     0o0755, "--strip-all"),      "InstallBin")
env.AddMethod(install("lib",     0o0644, "--strip-unneeded"), "InstallLib")
env.AddMethod(install("include", 0o0644),                     "InstallHeader")


folders = (
    "foo",
    "bar",
)

for folder in folders:
    script = os.path.join(folder, "SConscript")
    variant = os.path.join("build", folder)
    env.SConscript(script, variant_dir=variant, exports = 'env')

# vim: set ft=python:
