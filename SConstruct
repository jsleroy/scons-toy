import os

import SCons
from SCons.Script.SConscript import SConsEnvironment

def install(dest, perm, strip = None):
    def f(env, files, path = ""):
        obj = env.Install(env.Dir(os.path.join(env['PREFIX'], dest, path)), files)
        for o in obj:
            if strip is not None:
                env.AddPostAction(o, Action("strip %s %s" % (strip, str(o))))
            env.AddPostAction(o, env.Chmod(str(o), perm))
        return obj
    return f

variables = Variables()
variables.Add("PREFIX", "installation prefix", "usr")

env = Environment(
    variables = variables,
    tools = [ "default", ]
)

variables.Update(env)
Help(variables.GenerateHelpText(env))

env["PREFIX"] = os.path.abspath(env["PREFIX"])

SConsEnvironment.Chmod = SCons.Action.ActionFactory(os.chmod,
    lambda dest, mode: 'chmod %o "%s' % (mode, dest))

env.AddMethod(install("bin",     0o0755, "--strip-all"),      "InstallBin")
env.AddMethod(install("lib",     0o0644, "--strip-unneeded"), "InstallLib")
env.AddMethod(install("include", 0o0644),                     "InstallHeader")

Export("env")

folders = (
    "foo",
    "bar",
)

for folder in folders:
    script = os.path.join(folder, "SConscript")
    variant = os.path.join("build", folder)
    env.SConscript(script, variant_dir=variant)

# vim: set ft=python:
