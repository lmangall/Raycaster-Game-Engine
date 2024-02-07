# cub3D


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


__________________________________

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
