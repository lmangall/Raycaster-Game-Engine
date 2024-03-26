
# Raycaster Game Engine

This is a Doom-like raycaster game engine, coded in C as a team work with  @552020. This project is designed to recreate the classic 3D effect found in early first-person shooters using raycasting technology. This engine offers a glimpse into the workings of a pioneering technology in the gaming industry.

________________________________________________________________________________________________________________________________________
# Collaboration Unlocked

**Many Readmes document the implementation of the code and the math behind, therefore we thought that if something has to be shared, it is comething else : This Readme document our workflow findings for team project and organizing your work. If you are starting out with git and github as a tool to work in a team, this is for you.**

https://github.com/lmangall/cub3D/assets/107299611/7a620d24-8317-4a4f-865b-7d5cbda8c5e0

________________________________________________________________________________________________________________________________________

## Learning Focus

This project is not just about the end product; it's also a journey of learning and collaboration. Throughout the development process, we enhanced our skills and knowledge in several key areas:

- **Version Control:** Learn how to use Git for effective version control, enabling collaborative development and tracking changes over time.
- **GitHub Workflow:** Explore GitHub as a platform for hosting repositories, managing issues, and collaborating on projects.
- **Issue Tracking:** Utilize GitHub Issues for project management, keeping track of tasks, enhancements, and bugs.
- **Assigning:** Learn how to assign tasks to team members, distributing responsibilities efficiently.
- **Milestones:** Organize work into milestones, setting achievable goals and deadlines for project phases.
- **Collaborative Coding:** Emphasize collaboration by reviewing and providing feedback on each other's code.
- **Branching Model:** Understand the importance of branching in collaborative development and choose an appropriate branching strategy.
- **Feature Branches:** Develop features and enhancements in isolated branches before merging into the main codebase.


## Git core: Local and remote branches:

Git branches enable developers to work on features or fixes in isolation. 

- **Local branches** are branches in your local Git repository. Work here before you're ready to share or merge changes.
    - Create a new branch: `git branch <branch-name>`
    - Switch to a branch: `git checkout <branch-name>`

- **Remote branches** are references to the state of branches in a remote repository. They track the shared work.
    - Track a remote branch: `git checkout --track origin/<branch-name>`
    - Push local branch to remote: `git push -u origin <branch-name>`

Local changes don't affect remote branches until pushed, facilitating isolated development and review.

*Tracking a remote means your local branch will keep up with changes in the remote repository, automatically syncing your work with the latest updates from others. This is crucial for collaboration and ensuring your changes are compatible with the project's current state.*


## Overview

This guide outlines best practices for collaborative development using Git and GitHub. Effective collaboration involves clear communication, issue tracking, and a streamlined pull request (PR) process.

<details>
  <summary><strong>1. Issue Creation:</strong> Open an issue for a new task or bug.</summary>
  <br/>
  Opening Issues<br/>
  Frequent Issue Creation: Open an issue for each small feature, bug, or task. This helps in better tracking (collaborators know what is going on) and organization.<br/>
  Tags: Use relevant tags to categorize and label issues (e.g., bug, feature, documentation, etc.).<br/>
  Assignees: Assign issues to team members responsible for their resolution.<br/>
  Conversation: Use the conversation part of the issue to explain a problem, ask questions and stay up to date you can @people and #issue or #commit or #pullrequest<br/>
  Branch Naming: We found practical to create the branch right from the issue tab in Github<br/>
</details>
<br/>
<details>
  <summary><strong>2. Branching:</strong> Create a new branch for the issue.</summary>
  <br/>
  - We found practical to create the branch right from the issue tab in Github
</details>
<br/>
<details>
  <summary><strong>Commits:</strong>3. Make frequent, small commits (you can reference the issue number in the commit message)</summary>
  <br/>
  - following the CI/CD principles
  - the code is easier to debug, there are less conflicts
  - it is a real collaboration, not just splitting the work, as each person is aware of update in its teammate code
</details>
<br/>
<details>
  <summary><strong>4. Pull Request:</strong> Open a pull request once the work is complete.</summary>
  <br/>
  A PR is when a developer pushes changes to a branch in a fork of a repository and then submits a request to the original repository to merge those changes to main
  PR Opening: Open a pull request once changes are ready for review. (the main repo page on Github will offer you the option after a "fresh push")<br/>
  PR Review: Collaborators can comment on the PR.<br/>
</details>
<br/>
<details>
  <summary><strong>Review:</strong>5. Collaborators review the code, add comments, and suggest changes if necessary.</summary>
  <br/>
  Content
</details>
<br/>
<details>
  <summary><strong>Approval:</strong>6. Once approved, the PR is merged into `main`,</summary>
  <br/>
  Content
</details>
<br/>
<details>
  <summary>7. the issue is closed and the branch deleted</summary>
  <br/>
  Protection of Main Branch<br/>
  Main Protection: While we've decided not to protect the main branch, it is crucial to follow the rule of never pushing directly to it.<br/>
</details>


Remember, effective communication is key to successful collaboration. Happy coding!



| basic git commands                    | Description                                              |
|---------------------------------------|----------------------------------------------------------|
| `git branch`                          | List, create, or delete branches.                        |
| `git fetch --all`                     | Fetch all branches from the remote repository.           |
| `git checkout my_branch`              | Switch to the specified branch.                          |
| `git stash`                           | Save changes that are not ready to be committed.         |
| `git stash pop`                       | Apply stashed changes and remove them from the stash.    |
| `git log`                             | Display commit logs.                                     |
| `git branch <branch-name>`            | Create a new branch.                                     |
| `git push --set-upstream origin <branch-name>` | Push the branch to the remote repository and set it to track the remote branch. |



| Additionnal git log commands          | Description                                          |
|---------------------------------------|------------------------------------------------------|
| `git log --oneline`                   | Display abbreviated commit hashes and messages.      |
| `git log --graph`                     | Display a text-based graph of the commit history.   |
| `git log -n 5`                        | Show the last 5 commits.                             |
| `git log -p`                          | Show changes introduced in each commit.              |




________________________________________________________________________________________________________________________________________

# Generating a Valgrind Suppression File 

A Valgrind suppression file is a mechanism to filter out known and acceptable memory leaks or errors during the execution of a program. This guide outlines the process of creating a Valgrind suppression file, including both manual and automatic methods.

## Manual Suppression File Creation

1. **Identify Leaks:**
   - Run your program with Valgrind to detect memory leaks or errors.
     ```bash
     valgrind --leak-check=full ./your_program
     ```

2. **Extract Suppression Information:**
   - Review Valgrind's output and identify errors or leaks that you want to suppress.
   - Extract relevant information such as function names, library references, and leak types.

3. **Create Suppression File:**
**Suppression File Syntax:**

- Start with a pair of curly braces `{}` enclosing the suppression details.
- The first line inside the braces is a name for the suppression, chosen by you for easy identification.
- The second line specifies the type of Valgrind tool the suppression applies to, such as `Memcheck:Leak` for memory leaks.
- The third line, `match-leak-kinds`, is optional and specifies the kinds of leaks to match: definite, possible, indirect, still-reachable, etc.
- Subsequent lines use patterns like `fun:function_name` to match the function names in the call stack of the detected error or `obj:library_name` for matching specific libraries.
- The suppression entry ends when the closing brace `}` is reached.

**Example:**

```c
{
   ignore_lodepng_decode_leak
   Memcheck:Leak
   match-leak-kinds: possible
   fun:malloc
   fun:lodepng_decode
   fun:lodepng_decode_memory
   fun:lodepng_decode_file
   fun:mlx_load_png
   fun:load_textures
   fun:main
}

{
   ignore_mlx_leak_general
   Memcheck:Leak
   match-leak-kinds: possible
   fun:malloc
   ...
   obj:*libmlx42*
}

{
   ignore_glfw_leak_general
   Memcheck:Leak
   match-leak-kinds: possible
   fun:malloc
   ...
   obj:*glfw*
}
```


4. **Apply Suppression File:**
   - Run your program with the created suppression file.
     ```bash
     valgrind --leak-check=full --suppressions=your_suppressions.supp ./your_program
     ```

## Automatic Suppression File Generation

1. **Generate Valgrind Log:**
   - Run your program with Valgrind and generate a log file with suppression information.
     ```bash
     valgrind --leak-check=full --gen-suppressions=all --log-file=valgrind_log.txt ./your_program
     ```

2. **Use Suppressions Script:**
   - Utilize a script to parse the Valgrind log and create a suppression file automatically.
   - Example script: [Parse_valgrind_suppressions.sh](https://wiki.wxwidgets.org/Parse_valgrind_suppressions.sh)

3. **Refine Suppression File:**
   - Review the generated suppression file and refine it by removing unnecessary entries or adjusting patterns.
   - Focus on keeping suppressions relevant to your program's specific issues.

4. **Apply Suppression File:**
   - Run your program with the refined suppression file.
     ```bash
     valgrind --leak-check=full --suppressions=your_refined_suppressions.supp ./your_program
     ```



________________________________________________________________________________________________________________________________________
