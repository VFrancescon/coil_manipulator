# A note on Submodules

Git submodules make it easier to include other version controlled repos into the project.

A record of the submodules used is stored in: .gitmodules


# Usage

To add a submodule, use (ideally in the /submodules directory):

`git submodule add <repolink>`

When cloning the main repo, the submodules will be left as a blank folder.

To clone them, use:

`git submodule init`

`git submodule update`

# Credits

All credits for the submodules go to their original authors