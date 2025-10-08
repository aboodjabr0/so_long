#include "sound.h"

// man strcpy=> char *strcpy(char *dest, const char *src)

// local const-correct strcpy used here only
static char *ft_strcpy(char *s1, const char *s2)
{
    unsigned int i;
    
    i = 0;
    while (s2[i])
    {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = 0;
    return (s1);
}

// Globals defined here (declared extern in header)
slot_t g_slots[8];
pid_t g_music_pid;
char  g_music_cmd[32];

// Forward declarations for internal helpers used before definition
static int slot_check_and_update(slot_t *s, const char *path, const struct timespec *now);
static void consider_slot(int idx, const struct timespec *now,
                         long *oldest_age_ms, int *oldest_idx);
static void try_exec(const char *path);
static void mute_stdio(void);
static void run_music_loop(const char *path);

static int slot_check_and_update(slot_t *s, const char *path, const struct timespec *now)
{
    if (!s->init)
        return 0;
    if (s->p == path)
    {
        long dt_ms = (now->tv_sec - s->t.tv_sec) * 1000L +
                      (now->tv_nsec - s->t.tv_nsec) / 1000000L;
        if (dt_ms < 200)
            return 1;
        s->t = *now;
        return 2;
    }
    return 0;
}

static int should_throttle(const char *path)
{
    const int SLOT_COUNT = 8;
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    int empty = -1;
    long oldest_age_ms = -1;
    int oldest_idx = -1;
    int i = 0;
    while (i < SLOT_COUNT)
    {
        int res = slot_check_and_update(&g_slots[i], path, &now);
        if (res == 1)
            return 1;
        if (res == 2)
            return 0;
        if (!g_slots[i].init && empty == -1)
            empty = i;
        else
            consider_slot(i, &now, &oldest_age_ms, &oldest_idx);
        i++;
    }
    int idx = (empty != -1) ? empty : (oldest_idx != -1 ? oldest_idx : 0);
    g_slots[idx].p = path;
    g_slots[idx].t = now;
    g_slots[idx].init = 1;
    return 0;
}

static void consider_slot(int idx, const struct timespec *now,
                         long *oldest_age_ms, int *oldest_idx)
{
    if (!g_slots[idx].init)
        return;
    long age_ms = (now->tv_sec - g_slots[idx].t.tv_sec) * 1000L +
                  (now->tv_nsec - g_slots[idx].t.tv_nsec) / 1000000L;
    if (age_ms > *oldest_age_ms)
    {
        *oldest_age_ms = age_ms;
        *oldest_idx = idx;
    }
}

// Note: timespec_diff_ms was unused; removed to avoid -Werror unused warnings.

static void try_exec(const char *path)
{
    execlp("paplay", "paplay", path, (char*)NULL);
    execlp("aplay",  "aplay",  path, (char*)NULL);
    execlp("ffplay", "ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet",
           path, (char*)NULL);
}

static void mute_stdio(void)
{
    int dn = open("/dev/null", O_WRONLY);
    if (dn >= 0)
    {
        dup2(dn, STDOUT_FILENO);
        dup2(dn, STDERR_FILENO);
        if (dn > STDERR_FILENO)
            close(dn);
    }
}

void play_sound_async(const char *path)
{
    static int sig_ign_set;
    if (!sig_ign_set)
    {
        signal(SIGCHLD, SIG_IGN);
        sig_ign_set = 1;
    }
    if (!path || access(path, R_OK) != 0)
        return;
    if (should_throttle(path))
        return;
    pid_t pid = fork();
    if (pid == 0)
    {
        setsid();
        mute_stdio();
        try_exec(path);
        _exit(127);
    }
}

void sound_start_music(const char *path)
{
    if (!path || access(path, R_OK) != 0)
        return;
    if (g_music_pid > 0)
        return;
    pid_t pid = fork();
    if (pid == 0)
    {
        setsid();
        signal(SIGCHLD, SIG_DFL);
        mute_stdio();
        run_music_loop(path);
        _exit(0);
    }
    if (pid > 0)
    {
        g_music_pid = pid;
        ft_strcpy(g_music_cmd, "kill");
    }
}

/* This function runs inside the child process created by sound_start_music.
   It loops, forking a player subprocess and waiting for it to exit, then
   sleeping briefly before repeating. Kept as a separate function so
   sound_start_music stays small. */
static void run_music_loop(const char *path)
{
    while (1)
    {
        pid_t c = fork();
        if (c == 0)
        {
            mute_stdio();
            try_exec(path);
            _exit(127);
        }
        if (c > 0)
            waitpid(c, NULL, 0);
        usleep(100000);
    }
}

void sound_stop_music(void)
{
        if (g_music_pid > 0)
        {
            kill(-g_music_pid, SIGTERM);
            kill(g_music_pid, SIGTERM);
            int status;
            waitpid(g_music_pid, &status, WNOHANG);
            g_music_pid = 0;
            g_music_cmd[0] = '\0';
        }
}

void play_sound_blocking(const char *path)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        mute_stdio();
        if (!path || access(path, R_OK) != 0)
            _exit(0);
        try_exec(path);
        _exit(127);
    }
    if (pid > 0)
        waitpid(pid, NULL, 0);
}
