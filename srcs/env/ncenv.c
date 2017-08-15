#include "envNcurse.h"
#include <ncurses.h>

#define CTRL_WIN_WIDTH (40)
#define MAX_LIVE    LINES
#define CTRL_WIN_X  (COLS - CTRL_WIN_WIDTH)
#define MEM_WIN_WIDTH (COLS - CTRL_WIN_WIDTH)
#define BHEX "0123456789ABCDEF"

#define COLX(i) ((i) ? 5 : 0)
#define COLMEM(i) ((i > 0 && i < 5) ? i : COLX(i))

WINDOW *mem_win;
t_core  *core;

int            nc_colptr(t_vptr ptr)
{
    int         ci;
    t_process   *pc;

    ci = -1;
    while (++ci < core->vm.champ_count)
    {
        pc = core->vm.champs[ci].process;
        while (pc)
        {
            if (ABSPTR(pc->cc) == ptr)
            {
                attroff(A_DIM);
                attron(COLOR_PAIR(COLMEM(ci + 1) + 7));
                return (COLMEM(ci + 1) + 7);
            }
            pc = pc->next;
        }
    }
    return (7);
}

void            nc_dumpmem(t_memory *mem)
{
    t_vptr      ptr;
    int         y;
    int         x;
    int         col;
    ptr = 0;
    y = 0;
    while (ptr < MEM_SIZE)
    {
        x = -1;
        while (++x < (MEM_WIN_WIDTH) / 3 && ptr < MEM_SIZE)
        {
            move(y, x * 3); 
            attron(COLOR_PAIR(COLMEM(mem->trace[ptr])));
            col = nc_colptr(ptr);
            addch((char)BHEX[mem->mem[ptr] / 16]);
            addch((char)BHEX[mem->mem[ptr] % 16]);
            attroff(COLOR_PAIR(col) | A_UNDERLINE);
            attroff(COLOR_PAIR(COLMEM(mem->trace[ptr])));
            addch(' ');            
            ptr++;
        }
        y++;
    }
}

void            nc_initmemwin()
{
    nc_dumpmem(&core->vm.memory);
}

static void    cb_live_delta(int del)
{
    (void)del;
}

static void    cb_pc_die(t_champ *champ)
{
    (void)champ;
}

static void    cb_pc_loaded(t_champ *champ)
{
    (void)champ;
}

static void    cb_player_die(t_champ *champ)
{
    (void)champ;
}

static void    cb_memUpdated(t_memory *mem)
{
    (void)mem;
}

static void     cb_cycleUpdated()
{
    static int  cols = 0;
    static int  lines = 0;

    if (lines != LINES || cols != COLS)
    {
        cols = COLS;
        lines = LINES;
        clear();
    }
    nc_dumpmem(&core->vm.memory);
    refresh();
    usleep(DELLAY);
}

void            cb_playerlive(t_champ *ch, int call)
{
    static int  lindex = 0;
    char        buff[2048];

    if (lindex >= MAX_LIVE)
    {
        clear();
        lindex = 0;
    }
    move(lindex++, CTRL_WIN_X);
    sprintf(buff, "Player %d live(%d)", ch->number, call);
    printw(buff);
}

void           nce_init(t_core *c)
{
    core = c;
    core->render.livesDelta = (t_livesDelta)&cb_live_delta;
    core->render.processDie = (t_processDie)&cb_pc_die;
    core->render.playerDie = (t_playerDie)&cb_player_die;
    core->render.processLoaded = (t_processLoaded)&cb_pc_loaded;
    core->render.memUpdated = (t_memUpdated)&cb_memUpdated;
    core->render.cycleUpdated = (t_cycleUpdated)&cb_cycleUpdated;
    core->render.playerLive = (t_playerLive)&cb_playerlive;
    initscr();
    start_color();
    init_pair(0, COLOR_BLACK, 10);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, 6, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(120, COLOR_GREEN, COLOR_YELLOW);
    init_pair(7, COLOR_BLACK, 14);
    init_pair(8, COLOR_WHITE, COLOR_RED);
    init_pair(9, COLOR_WHITE, COLOR_BLUE);
    init_pair(10, COLOR_WHITE, 120);
    init_pair(11, COLOR_WHITE, COLOR_GREEN);


    nc_initmemwin();
}