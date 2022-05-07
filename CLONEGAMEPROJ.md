# Cloning an existing game repo

For reference, we will use ```{PROJ_NAME}``` to refer to the repo name. You should replace this with the desired repository's name (without the ```{}```).

Clone the repository with a different name, example:

```git clone https://github.com/repo_owner/{PROJ_NAME} {PROJ_NAME}_temp```

[Clone the HOE engine and generate a project with the name as ```{PROJ_NAME}```](https://github.com/HO-org/HOE#readme)

**To build the game, the engine folder must remain intact.
It is also recommended to clone it with an appropriate name as the engine must be cloned into a different directory for every seperate game project**

Copy the created project's contents, except for the folders ```src, resources``` and the file ```premake5.lua``` into the cloned repository.
If asked do not overwrite files.

Delete the generated project and rename the repository folder to ```{PROJ_NAME}```

You can now compile the game using the [build script](https://github.com/HO-org/HOE/blob/master/README.md#the-build-script)!
