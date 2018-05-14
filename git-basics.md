_quoting / using "[Pro Git](https://git-scm.com/book/en/v2)", 2nd edition, by Scott Chacon and Ben Straub, Apress_

* create branch:
`git branch abcdef`

* show where you are:
`git log --oneline --decorate`
(include all branches, "graph":)
`git log --oneline --decorate --graph --all`

* show existing branches:
`git branch [-v]`

* switch to an existing branch:
`git checkout abcdef` (this also "reverts" the files to the state of this branch)

* create and switch to a branch in one step:
`git checkout -b iss53`

* merge a branch into another:
  1. go to the target branch: `git checkout master`
  2. merge the other branch: `git merge hotfix`

* show which branches are part of the current one:
`git branch --merged`

* delete a branch:
`git branch -d hotfix`

* support in resolving merge conflicts:
`git mergetool`

* show remote branches:
`git ls-remote [remote]`
`git remote show [remote]`

* push a branch to remote:
`git push <origin> <branchName>`

* tracking branches (this is kind of default for the initial origin/master...)
`git checkout --track origin/serverfix`
  * `git checkout serverfix` does exactly the same, if a) the branch does not exist locally, and b) the name matches exactly one branch on any remote.

* carefully synchronize with a server (remote):
`git fetch origin`
* branch serverfix set up to track remote branch serverfix from origin:
`git checkout -b serverfix origin/serverfix`
* now, merge your other local branches into this one

* delete remote branches:
`git push origin --delete serverfix`
