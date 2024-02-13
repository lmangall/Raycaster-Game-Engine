#include "animations.h"

static double deg_to_rad(int degrees) { return degrees * (M_PI / 180.0); }

static t_frame *new_frame(t_frame frame) {
  t_frame *f;

  f = (t_frame *)ft_calloc(sizeof(t_frame), 1);
  if (!f)
    return (NULL);
  *f = frame;
  return (f);
}

t_animation *orbit(int delay, int fps) {
  t_animation *a;
  int i;
  t_frame *fs[360];

  a = (t_animation *)ft_calloc(sizeof(t_animation), 1);
  if (!a)
    return (NULL);
  i = -1;
  while (++i < 360)
    fs[i] = new_frame((t_frame){cos(deg_to_rad(i)) * 130 + 135,
                                sin(deg_to_rad(i)) * 130 + 135, rand(), 15});
  *a = (t_animation){NULL, CIRCLE, *fs[0], delay, 0, 0, fps, 0, 0};
  i = -1;
  while (++i < 360)
    ft_lstadd_back(&a->frames, ft_lstnew(fs[i]));
  return (a);
}

t_animation *semaphore(int delay, int fps) {
  t_animation *a;
  int i;
  t_frame *fs[192];

  a = (t_animation *)ft_calloc(sizeof(t_animation), 1);
  if (!a)
    return (NULL);
  i = -1;
  while (++i < 50)
    fs[i] = new_frame((t_frame){20, 160, 0x00d4180b, 20});
  fs[i++] = new_frame((t_frame){20, 160, 0, 20});
  fs[i++] = new_frame((t_frame){20, 160, 0x00d4180b, 20});
  fs[i] = new_frame((t_frame){20, 160, 0, 20});
  while (++i < 103)
    fs[i] = new_frame((t_frame){20, 200, 0x00ff6803, 20});
  fs[i++] = new_frame((t_frame){20, 200, 0, 20});
  fs[i++] = new_frame((t_frame){20, 200, 0x00ff6803, 20});
  fs[i] = new_frame((t_frame){20, 200, 0, 20});
  fs[i++] = new_frame((t_frame){20, 200, 0, 20});
  fs[i++] = new_frame((t_frame){20, 200, 0x00ff6803, 20});
  fs[i] = new_frame((t_frame){20, 200, 0, 20});
  fs[i++] = new_frame((t_frame){20, 200, 0x00ff6803, 20});
  fs[i++] = new_frame((t_frame){20, 200, 0, 20});
  fs[i] = new_frame((t_frame){20, 200, 0x00ff6803, 20});
  while (++i < 192)
    fs[i] = new_frame((t_frame){20, 230, 0x0028e813, 20});
  *a = (t_animation){NULL, CIRCLE, *fs[0], delay, 0, 0, fps, 0, 0};
  i = -1;
  while (++i < 192)
    ft_lstadd_back(&a->frames, ft_lstnew(fs[i]));
  return (a);
}

t_animation *rect_animation(int delay, int fps) {
  t_animation *a;
  int i;
  t_frame *fs[100]; // Assuming 100 frames for the animation

  a = (t_animation *)ft_calloc(sizeof(t_animation), 1);
  if (!a)
    return (NULL);

  // Generate frames for the rectangle moving horizontally
  i = -1;
  while (++i < 100) {
    fs[i] = new_frame((t_frame){20 + i * 2, 100, 0x00FF0000, 20});
  }

  *a = (t_animation){NULL, RECT, *fs[0], delay, 0, 0, fps, 0, 0};

  i = -1;
  while (++i < 100) {
    ft_lstadd_back(&a->frames, ft_lstnew(fs[i]));
  }

  return a;
}

t_animation *ball_animation(int delay, int fps) {
  t_animation *a;
  int i;
  int bounceHeight = 50; // Height of the bounce
  int startY = 150;      // Starting Y position
  t_frame *fs[200];      // 200 frames for the up and down movement

  a = (t_animation *)ft_calloc(sizeof(t_animation), 1);
  if (!a)
    return (NULL);

  // Generate frames for the ball bouncing vertically
  for (i = 0; i < 200; ++i) {
    // Calculate the y position for a simple bounce using an absolute sine wave
    int yPos = (int)(startY + bounceHeight * fabs(sin(i * M_PI / 100)));
    fs[i] = new_frame((t_frame){100, yPos, 0x00FF0000,
                                15}); // x fixed at 100, size fixed at 15
  }

  *a = (t_animation){NULL, CIRCLE, *fs[0], delay, 0, 0, fps, 0, 0};

  for (i = 0; i < 200; ++i) {
    ft_lstadd_back(&a->frames, ft_lstnew(fs[i]));
  }

  return a;
}
