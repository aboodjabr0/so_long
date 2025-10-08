#ifndef SOUND_H
#define SOUND_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <time.h>
# include <string.h>
# include "so_long.h"


typedef struct s_slot
{
    const char *p;
    struct timespec t;
    int init;
} slot_t;

// Global state (defined in sound.c)
extern slot_t g_slots[8];
extern pid_t g_music_pid;
extern char  g_music_cmd[32];

void play_sound_async(const char *path);
void play_sound_blocking(const char *path);

// Background music control
void sound_start_music(const char *path); // loop until stopped
void sound_stop_music(void);             // stop looping music

#endif
