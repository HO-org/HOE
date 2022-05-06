import sys
import os
import shutil

def try_copy_tree(source, target):
    try:
        shutil.copytree(source, target)
    except FileExistsError:
        req = input("Folder at '" + target + "' exists, do you want to override it? Y/n ")
        if req.startswith("y".lower()):
            pass
        else:
            quit()

def try_make_dir(path):
    try:
        os.mkdir(path)
    except FileExistsError:
        req = input("Folder at '" + path + "' exists, do you want to override it? Y/n ")
        if req.startswith("y".lower()):
            pass
        else:
            quit()

def main():
    project_name = ""
    project_dir = ""

    argv = sys.argv
    argc = len(argv)
    for i in range(argc):
        if i == 1:
            project_dir = argv[i]
        if i == 2:
            project_name = argv[i]

    if not project_dir:
        project_dir = input("Enter the absolute path for the project's parent directory with a '\\' or '/' at the end: ")

    f_proj_dir = open("game_dir.projdir", "w")
    f_proj_dir.write(project_dir)
    f_proj_dir.close()

    if not project_name:
        project_name = input("Enter the name for the project: ")

    f_proj_name = open("game_name.projname", "w")
    f_proj_name.write(project_name)
    f_proj_name.close()

    proj_path = project_dir + project_name

    try_make_dir(proj_path)

    dll_path = os.curdir + "/vendor/runtime"
    for dll in os.listdir(dll_path):
        shutil.copy(dll, proj_path)
    
    resource_path = os.curdir + "/resources"
    try_copy_tree(resource_path, proj_path + "/resources")
    
    try_make_dir(proj_path + "/src")
    shutil.copy(os.curdir + "/example_entry.cppexm", proj_path + "/src/entry_point.cpp")

    f_premake5 = open(proj_path + "/premake5.lua", "w")
    f_premake5.close()
    





if (__name__ == "__main__"):
    main()

