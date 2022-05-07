from platform import platform
import sys
import os
import shutil
import platform


def try_copy_tree(source, target):
    if (os.path.isdir(target)):
        req = input("Folder at '" + target + "' exists, PROCEEDING WILL DELETE AND REPLACE IT! Y/n ")
        if req.lower().startswith("y"):
            shutil.rmtree(target)
        else:
            quit()
    
    try:
        shutil.copytree(source, target)
    except FileExistsError:
        print("Could not copy tree because the folder exists")
        quit()
    except PermissionError:
        req = input("A required file or folder is in use... retry? Y/n ")
        if req.lower().startswith("y"):
            try_copy_tree(source, target)


def try_make_dir(path):
    try:
        os.mkdir(path)
    except FileExistsError:
        req = input("Folder at '" + path + "' exists, do you want to override it? Y/n ")
        if req.lower().startswith("y"):
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

    f_engine_fold = open(os.curdir + "/game_proj_files/engine_folder.engname", "w")
    f_engine_fold.write(os.path.abspath(os.curdir))
    f_engine_fold.close()

    proj_path = project_dir + project_name

    base_build_bat = f"cd {os.path.abspath(os.curdir)}\n{os.path.abspath(os.curdir)}\\build.bat %*\ncd {proj_path}"
    base_build_bash = f'''#!/bin/bash
rm ./*.dll
cd {os.path.abspath(os.curdir)}
./build "$@"
cd {proj_path}'''

    f_build_batch = open(os.curdir + "/game_proj_files/build.bat", "w")
    f_build_batch.write(base_build_bat)
    f_build_batch.close()

    script_path = os.curdir + "/game_proj_files/build"

    f_build_bash = open(script_path, "w")
    f_build_bash.write(base_build_bash)
    f_build_bash.close()

    if platform.system() == "Linux":
        os.system(f"chmod +x {script_path}")

    try_copy_tree(os.curdir + "/game_proj_files", proj_path)


if (__name__ == "__main__"):
    main()


