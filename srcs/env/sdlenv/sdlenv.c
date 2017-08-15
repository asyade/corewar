#include "sdlenv.h"

SDL_Window      *window;
SDL_Renderer    *render;

static void    cb_live_delta(int del)
{
    (void)del;
}

static void    cb_pc_die(t_champ *champ)
{
    plog("%s: sub process killed (%d)\n", champ->header.name, champ->nbr_process);
}

static void    cb_pc_loaded(t_champ *champ)
{
    (void)champ;
    plog("%s: proces loaded\n", champ->header.name);
}

static void    cb_player_die(t_champ *champ)
{
    plog("%s: Die\n", champ->header.name);
}


 void     cb_end()
{
    SDL_Quit();
}

void    sdle_init(t_core *core)
{
    core->render.livesDelta = (t_livesDelta)&cb_live_delta;
    core->render.processDie = (t_processDie)&cb_pc_die;
    core->render.playerDie = (t_playerDie)&cb_player_die;
    core->render.processLoaded = (t_processLoaded)&cb_pc_loaded;

    SDL_Init(SDL_INIT_VIDEO);
    if (!(window = SDL_CreateWindow("Corewar", 0, 0, 840, 548, SDL_WINDOW_SHOWN)))
        exit(0);
    (void)window;
}