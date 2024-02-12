# cub3D



Check this out:
https://www.youtube.com/watch?v=X6AR2RMB5tE&ab_channel=ThePrimeagen


from ccatano: 
- fabs, stand for float abs, is a function we need from the math library
- parsing is difficult, yet similar to so_long
- 


ressources:

https://pikuma.com/courses/raycasting-engine-tutorial-algorithm-javascript
https://lodev.org/cgtutor/raycasting.html

Youtube raycasting video
https://www.youtube.com/watch?v=NbSee-XM7WA&ab_channel=javidx9


Library:
MLX 42 - https://github.com/codam-coding-college/MLX42
https://github.com/codam-coding-college/MLX42/wiki

.vscode/


categories for the future readme:
- maths and algo
- learning others than directly related to the project (makefile, issue trackin...g)
- 




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

https://github.com/lmangall/cub3D/assets/107299611/f83001c3-fcf2-4a82-b670-e54634979c40

________________________________________________________________________________________________________________________________________
________________________________________________________________________________________________________________________________________

________________________________________________________________________________________________________________________________________
________________________________________________________________________________________________________________________________________


# Collaboration Guide using Git and GitHub                  => add about _rebasing_ and explanation  on local/remote branches + command to set remote

## Overview

This guide outlines best practices for collaborative development using Git and GitHub. Effective collaboration involves clear communication, issue tracking, and a streamlined pull request (PR) process.

## Issues on GitHub

GitHub provides an "Issues" tab for effective project management. Here's how to make the most of it:

### Opening Issues

- **Frequent Issue Creation:** Open an issue for each small feature, bug, or task. 
      This helps in better tracking (collaborators know what is going on) and organization.
- **Tags:** Use relevant tags to categorize and label issues (e.g., `bug`, `feature`, `documentation`, etc.).
- **Assignees:** Assign issues to team members responsible for their resolution.
- **Conversation:** Use the conversation part of the issue to explain a problem, ask questions and stay up to date
      you can @people and #issue or #commit or #pullrequest 
- **Branch Naming:** We found practical to create the branch right from the issue tab in Github

## Pull Requests (PRs)

- **PR Opening:** Open a pull request once changes are ready for review. (the main repo page on Github will offer you the option after a "fresh push"
- **PR Review:** Collaborators review each other's code by commenting on the PR.

## Protection of Main Branch

- **Main Protection:** While we've decided not to protect the `main` branch, it is crucial to follow the rule of never pushing directly to it.

### Example Workflow

1. **Issue Creation:** Open an issue for a new task or bug.
2. **Branching:** Create a new branch for the issue - e.g., `feature/add-new-feature`.
3. **Commits:** Make frequent, small commits and reference the issue number in the commit message.
4. **Pull Request:** Open a pull request once the work is complete.
5. **Review:** Collaborators review the code, add comments, and suggest changes if necessary.
6. **Approval:** Once approved, the PR is merged into `main`,
7. the issue is closed and the branch deleted

Remember, effective communication is key to successful collaboration. Happy coding!



| Command                               | Description                                          |
|---------------------------------------|------------------------------------------------------|
| `git branch`                          | List, create, or delete branches.                    |
| `git fetch --all`                     | Fetch all branches from the remote repository.       |
| `git checkout my_branch`               | Switch to the specified branch.                      |
| `git stash`                           | Save changes that are not ready to be committed.    |
| `git stash pop`                       | Apply stashed changes and remove them from the stash.|
| `git log`                             | Display commit logs.                                 |
| `git log --oneline`                   | Display abbreviated commit hashes and messages.      |
| `git log --graph`                     | Display a text-based graph of the commit history.   |
| `git log -n 5`                        | Show the last 5 commits.                             |
| `git log -p`                          | Show changes introduced in each commit.              |

Note: Make sure to replace `my_branch` with the actual branch name you want to checkout. These commands are just a starting point, and there are many more Git commands and options available for various scenarios. Feel free to explore Git documentation for more details on each command.



________________________________________________________________________________________________________________________________________
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
