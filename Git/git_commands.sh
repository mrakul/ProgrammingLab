    ### Initializing ###
# Clone the remote repository
git clone <URL>

# Init the new one repository: it creates .git directory with the git-specific data
git init

    ### Output ###
# Show last 5 commits in the pretty mode
git log -5 --graph --decorate --pretty=oneline --abbrev-commit

# Show last commit or current commit
git show

# Show files in the index and the working tree (--cached by default)
git ls-files

# List the contents of a tree object (what is commited?)
git ls-tree HEAD

# Shows all remote repositories URLs
git remote -v

# Show remote repositories with the remote branches and linkage with with local
git remote show origin

# Shows all remote and local branches
git branch -a

    ### Commits, staging ###
# Staging
git add .

# Committing. With no -m option, VIM will be opened by default to enter the commit message:
git commit -m "[Description of changes made]"

# Change the last commit if forgot something or want to correct (better to do before pushing to remote):
git commit --amend

    ### Merging/fetching ###
# Merges the changes from one branch to the current:
git merge featureBranch

# Updates the local representation (origin/featureBranch) of the remote branch featureBranch
git fetch featureBranch
# After this, need to checkout to the local branch (featureBranch) and merge its remote representation:
git merge origin/featureBranch

# The steps of [fetch + merge] are equal to one command, that is merging is tries automatically:
git pull origin featureBranch

# Squash commit: (!) merge with squash only updates the working tree and the index to match a merged branch without actually creating a merge commit.
# It doesn't move the HEAD pointer and not write to .git/MERGE_HEAD
# Then need to use git commit to make the commit manually:
git merge --squash featureBranch

    ### Branching ###
# Creates a new branch and checkout to it. Note: this doesn't create remote representation, only after pushing it to the remote
git checkout -b <new branch>
#or (not checkout to it)
git branch <new branch>


    ### Move commits from one branch to another: merge, rebase, cherry-pick  ###
# Rebases <branch2> to <branch1> AND (!) checkout to <branch2> (interactively or not [-i])
git rebase -i <branch1> <branch2>

# Interactively rebase the current branch to the specified branch (pointer): includes manipulation with commits and move the pointer to the target branch
git rebase -i <branch, commit SHA>

# Note: git rebase -i HEAD~3, for example, may be used to squash several commits in one.
# For example:
> squash b5de45a Minor changes and random examples added
> pick 50ac314 Git commands examples complemented

# Cherry-pick
git cherry-pick <C1, C2 ... Cn>
# pick up the specified commits for the current branch and move the branch to the last specified commit, need to change "pick" to "squash" in VIM, those commits will be squashed in one:


    ### Moving HEAD and the branches pointers ###
# Move HEAD to the commit/branch. If a commit specified, then you're in the 'detached HEAD' state, meaning that HEAD is no attached to any branch.
# This changes the working tree and the staging area corresponding to the commit/branch specified.
# Note: might want to save the working tree and the staging area by the git stash push (desribed below)
git checkout <commit/branch>

# Move the HEAD for the 1-st or the second parent appropriately
git checkout HEAD^
git checkout HEAD^2
git checkout HEAD~^2~2  -> move for 1 commit down, for the second parent and for 2 commits down

# Move the specified branch to the current commit (where the HEAD now), (!) BUT not checkout to the branch
git branch -f <branch>

# Moves the HEAD pointer AND the current branch's pointer where HEAD points to to the commit specified:
git reset --hard <commit>   -- update all the trees with the commit's content
git reset --mixed <commit>  -- update staging area along with pointers HEAD and the branch, but no updating working tree content
git reset --soft <commit>   -- no update working tree and the index tree

# Save the current working tree and the index state:
git stash push              -- saves the current state
git stash pop               -- returns the state back


    ### Remotes ###
# Forcely push the changes to the main of remote origin
git push -f origin main

#  If the branch is created remotely:
git fetch origin
# will fetch the remote branch(es) and create its remote representation (but not local branch)
  >From https://github.com/mrakul/ProgrammingLab
  > * [new branch]      test2      -> origin/test2
  > git branch --remotes
  >  origin/HEAD -> origin/main
  >  origin/main
  >  origin/test2

# Then if try to checkout to the local, the branch is just created locally
git checkout test2
  > Switched to a new branch 'test2'
  > M       Git/git_commands.txt
  > Branch 'test2' set up to track remote branch 'test2' from 'origin'.
#Note: makes the same as
git checkout --track origin/test2

# Push the branch to the remote repository (origin), ('--set-upstream' == '-u'):
git push -u origin dev

# Remove the remote branch and its local reflection:
# (!) removes the remote branch (FROM THE REMOTE REPOSITORY) and its local reflection (origin/test)
# This command doesn't delete the local branch, need to delete the local branch branch separately
git push origin --delete test

# If remote branches are deleted, but local remotes representation still exist, this command "cuts"(prunes), that is removes their representation:
git remote prune origin
 > Pruning origin
 > URL: https://github.com/mrakul/ProgrammingLab.git
 > * [pruned] origin/test2
 > * [pruned] origin/test4

# Change the origin's URL
git remote set-url origin https://github.com/mrakul/ProgrammingLab.git  https://github.com/mrakul/CCpp-Projects-VS-Code.git

# Set upstream URL
git remote add upstream <URL>

# Tie local branch to remote ('--set-upstream' == '-u')
git branch --set-upstream-to=upstream/foo
#or
git branch --set-upstream-to=upstream/foo foo
# -> specify foo if it is not the current one



## Unsorted - TODO:
>===== Тегирование / tagging ======<
// Вывести все теги
git tag -v

// По коммитам
git log --all --decorate --oneline --simplify-by-decoration
(--all для всех веток)

git log --decorate --oneline --simplify-by-decoration

// По тегам:
// Первый найденный тег вниз по дереву
git describe

// Первый найденный по регулярному выражению
git describe --abbrev=0 --match "prefix-*"
# --abbrev=0 - не выводит количество коммитов до тега и SHA тега

// Вывод в виде графа
git log --graph --all --decorate --oneline --simplify-by-decoration

(?) --simplify-by-decoration - упрощает, больше ориентирован на теги и ветки, можно увидеть
структуру дерева

// Коммиты
git log 5c10ea2d -10 --oneline

// Проверка тегов удалённо
git ls-remote --tags origin

// (+) Лог между коммитами/tag'ами
git log --oneline older_commit..newer_commit

=> commits reachable from newer_commit but not from older_commit
(commits reachable from B but not from A)

Включить old_commit:
git log --oneline older_commit^..newer_commit

Note: ... has different meaning - "Include commits that are reachable from either a or b but exclude those that are reachable from both".
Like XOR?

git log A...B => symmetric difference
But:
git diff A...B => is not symmetric difference


// Clone только одной ветки и глубины 1, в одном коммите (shallow clone)
git clone --single-branch --branch=$CI_CRISTALE_BRANCH_NAME --depth=1 [repo] [

// Залить один тег
git push origin tag <tag_name>

// Найти коммит-отличие 
git merge-base release backup/dev

// git rebase --onto
git rebase --onto master server client

 “Take the client branch, figure out the patches since it diverged from the server
branch, and replay these patches in the client branch as if it was based directly off the master
branch instead.”


    ### Garbage collector ###
# Removes the orphaned nodes
git gc