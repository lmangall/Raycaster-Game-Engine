# GIT

## Beginner Level Git Commands

### `git clone <repository> [directory]`

- **Description**: Clone a repository into a new directory.
- **Example**: `git clone https://github.com/example/repo.git custom-directory`
- **Explanation**: This command copies an existing Git repository to a new directory on your local machine. If you do not specify a directory name, Git uses the repository's name by default. The <repository> URL is required as Git needs to know the source repository to clone.

### `git add`

- **Commands**:
  - **`git add [file]`**: Add specific file contents to the index (staging area).
  - **`git add -A` or `git add --all`**: Add all changes in the entire repository to the staging area, including new files, deletions, and modifications.
  - **`git add *`**: This command adds changes in the current directory and subdirectories (following shell glob patterns), but might not include new files or deletions in directories outside of the current one.
- **Example**: `git add README.md`
- **Explanation**: `git add` stages changes for the next commit. Using `-A` or `--all` stages all changes in the repository, while `*` is influenced by the shell and might behave differently in terms of scope.

### `git commit`

- **Commands**:
  - **`git commit -m "[message]"`**: Commit your staged content as a new commit snapshot with a message.
  - **`git commit --amend`**: Amend the most recent commit. This allows you to modify the last commit message or combine the current staging area changes with the previous commit instead of creating a new one.
  - **`git commit -am "[message]"`**: Add all tracked files' changes to the staging area and commit them. This skips the `git add` step for modifications to already tracked files but does not add new files.
- **Example**: `git commit -m "Initial commit"`
- **Explanation**: `--amend` is used to correct mistakes in the last commit. The `-am` flag is a convenience feature that combines adding changes to tracked files and committing them in one step.

### `git push`

- **Commands**:
  - **`git push [remote] [branch]`**: Update remote refs along with associated objects.
  - **`git push --set-upstream [remote] [branch]`** or **`git push -u [remote] [branch]`**: Pushes your branch to the remote repository and sets it as the upstream for your local branch. This means future pushes and pulls for this branch can be done without specifying the remote and branch names.
- **Example**: `git push origin main`
- **Explanation**: An _upstream branch_ is a branch in a remote repository that is tracked by your local branch. Setting an upstream branch for your local branch allows Git to know where to push or pull changes when no specific remote or branch is specified in the command.

## Important Concepts for the Beginner Level

- **Repository (Repo)**: A Git repository encompasses both the `.git` directory, where Git keeps all of the metadata for the project's revisions (such as commits, branches, tags, etc.), and the working directory, where the current versions of your project files live. The `.git` directory is hidden and contains the internal data structure used by Git to track changes, while the working directory is where you edit, add, and delete the actual files. In everyday usage, when someone refers to a "repo," they usually mean the combination of the `.git` directory and the working directory — essentially, the entire project. A _local repository_ resides on your personal computer. It's a private workspace where you can make changes, commit them, and work on your project independently of others. The local repository includes all of your project's files and the history of changes stored in the `.git` directory. When we talk about a repo we refer normally to a local repo or the whole constellation of local repo(s) and remote repo(s) A _remote repository_ is hosted on the internet or a network. It allows multiple developers to collaborate on the same project by pushing changes to and pulling changes from the remote repository. The default remote repository is often referred to as `origin`. It acts as a central hub for the code, allowing team members to share their changes and keep their local repositories in sync. [^repo]

- **Remote**: A version of your repository hosted on a server, typically used for collaboration. The default remote is usually called `origin`.[^remote]

- **Branch**: A branch in Git is essentially a pointer to a particular commit. Branches represent divergent or parallel lines of development within the same repository. They allow you to isolate work on features, bug fixes, experiments, etc., without affecting the main or other branches of the project. Once the work on a branch is complete and tested, it can be merged back into the main branch or another target branch. This facilitates collaboration and parallel development by multiple contributors. The default branch in most Git repositories is called master or main.

- **Upstream Branch**: The term "upstream branch" refers to the branch on a remote repository from which you pulled changes into your local branch. It is considered "upstream" because it is the source of the changes that flow downstream to your local repository. Setting an upstream branch for a local branch establishes a tracking relationship, making it easier to fetch, pull, or push changes without specifying the remote name and branch each time.[^upstream_branch]

- **Working directory** This is the area where all the files and directories currently checked out from the repository's database (the .git directory) are available for you to use and modify. It's your workspace where you edit files, create new ones, and delete others. Git recognizes changes in this area by comparing the current state of files to the last snapshot stored in the repository (the last commit).

- **Staging Area**: The staging area, or "index", is a preparation zone for changes that are about to be committed. Changes added to the staging area are the ones included in the next commit. This allows developers to selectively add changes to the next commit, making it possible to split work into logical commits rather than committing all changes at once.

- **Commit**: A snapshot of your repository's files at a specific point in time. Commits include a message that describes the changes made.

[^repo]: A Git repository encompasses _both_ the `.git` directory, where Git keeps all of the metadata for the project's revisions (such as commits, branches, tags, etc.), and the working directory, where the current versions of your project files live. The `.git` directory is hidden and contains the internal data structure used by Git to track changes, while the working directory is where you edit, add, and delete the actual files. In everyday usage, when someone refers to a "repo," they usually mean the combination of the `.git` directory and the working directory — essentially, the entire project.
[^upstream_branch]: The term "upstream branch" refers to the branch on a remote repository from which you pulled changes into your local branch. It is considered "upstream" because it is the source of the changes that flow downstream to your local repository. Setting an upstream branch for a local branch establishes a tracking relationship, making it easier to fetch, pull, or push changes without specifying the remote name and branch each time. In the context of Git, "downstream" doesn't refer to a specific type of branch but rather describes the direction of changes flowing from the remote repository (upstream) to your local repository. However, in broader software development and open-source communities, a "downstream" project or repository might refer to a project that incorporates and relies on another project ("upstream"). Downstream changes could be contributions made back to the original project or modifications that remain within a fork or a derived project.
[^remote]: direct modifications to the remote repository (such as editing files, moving, or deleting them) are not done through standard Git commands. The remote repository is usually updated through operations like `git push` (to upload local branch changes), `git fetch` (to retrieve updates without merging), and `git pull` (to fetch and merge updates). Exceptions: Some hosting services for Git repositories, like GitHub, GitLab, or Bitbucket, offer web interfaces that allow you to perform certain direct actions on the remote repository, such as editing files, creating or merging pull requests, and managing issues and project documentation. These actions are reflected in the repository as if they were local changes that were pushed to the repository.
