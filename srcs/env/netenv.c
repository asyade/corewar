#include "corewar.h"
#include "netenv.h"

static void    cb_live_delta(int del)
{
    (void)del;
}

static void    cb_pc_die(t_champ *champ)
{
    pwarn("%s: sub process killed (%d)\n", champ->header.name, champ->nbr_process);
}

static void    cb_pc_loaded(t_champ *champ)
{
    (void)champ;
    plog("%s: proces loaded\n", champ->header.name);
}

static void    cb_player_die(t_champ *champ)
{
    pwarn("%s: Die\n", champ->header.name);
}

static void    cb_memUpdated(t_memory *mem, int a, int b)
{
    (void)a;
    (void)b;
    (void)mem;
}

void    nte_init(t_core *core)
{
    core->render.livesDelta = (t_livesDelta)&cb_live_delta;
    core->render.processDie = (t_processDie)&cb_pc_die;
    core->render.playerDie = (t_playerDie)&cb_player_die;
    core->render.processLoaded = (t_processLoaded)&cb_pc_loaded;
    core->render.memUpdated = (t_memUpdated)&cb_memUpdated;

}