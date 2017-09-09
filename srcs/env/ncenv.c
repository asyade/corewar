#include "envNcurse.h"
#include <ncurses.h>

#define CTRL_WIN_WIDTH (40)
#define CTRL_WIN_HEIGHT (16)
#define MAX_LIVE    LINES
#define CTRL_WIN_X  (COLS - CTRL_WIN_WIDTH)
#define MEM_WIN_WIDTH (COLS - CTRL_WIN_WIDTH)
#define BHEX "0123456789ABCDEF"

#define COLX(i) ((i) ? 5 : 0)
#define COLMEM(i) ((i > 0 && i < 5) ? i : COLX(i))

WINDOW *mem_win;
t_core  *core;
long int    cycle = 0;
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

static void     dump_cpu()
{
    char    buff[127];

    move(1, CTRL_WIN_X);
    sprintf(buff, "Cycle %4d CTD %4d Live %2d T %ld", core->vm.cycles, core->vm.cycles_to_die, core->vm.lives, cycle);
    printw(buff);
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
static void     dump_champs()
{
    char    buff[1024];
    int     i;
    int     y;

    y = 3;
    i = 0;
    while (i < core->vm.champ_count)
    {
        move(y, CTRL_WIN_X);
        attron(COLOR_PAIR(COLMEM(core->vm.champs[i].number)));
        sprintf(buff, "%s p%d", core->vm.champs[i].header.name, core->vm.champs[i].number);
        printw(buff);        
        attroff(COLOR_PAIR(COLMEM(core->vm.champs[i].number)));
        move((y += 1), CTRL_WIN_X);
        sprintf(buff, "Nbr process %6d, alive %s", core->vm.champs[i].nbr_process, (core->vm.champs[i].flags & PC_ALIVE ? "yes" : "no "));
        printw(buff);
        y += 2;
        i++;
    }
}


static void     cb_cycleUpdated()
{
    static int  cols = 0;
    static int  lines = 0;
    static int  dellay = 1;
    char        ch;

    cycle++;
    if (lines != LINES || cols != COLS)
    {
        cols = COLS;
        lines = LINES;
        clear();
    }
    nc_dumpmem(&core->vm.memory);

    attron(A_BOLD);

    dump_cpu();    
    dump_champs();
    move(LINES - 1, 0);
    char    buff[127];
    sprintf(buff, "Dellay %d", dellay);
    printw(buff);
    attroff(A_BOLD);
    refresh();
    ch = getch();
    if (ch == 'p')
    {
        while (getch() != 'p')
            ;
    }
    else if (ch == '+')
        dellay++;
    else if (ch == '-' && dellay > 0)
        dellay--;
    if (dellay)
        usleep(dellay * 100);
}

void            cb_playerlive(t_champ *ch, int call)
{
    static int  lindex = CTRL_WIN_HEIGHT;
    char        buff[2048];

    if (lindex >= MAX_LIVE)
    {
        clear();
        nc_dumpmem(&core->vm.memory);
        lindex = CTRL_WIN_HEIGHT;
    }
    move(lindex++, CTRL_WIN_X);
    sprintf(buff, "Player %d live(%d)", ch->number, call);
    attron(COLOR_PAIR(COLMEM(ch->number)));
    printw(buff);
    attroff(COLOR_PAIR(COLMEM(ch->number)));
    refresh();
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
    init_pair(260, COLOR_GREEN, COLOR_YELLOW);
    init_pair(7, COLOR_BLACK, 14);
    init_pair(8, COLOR_WHITE, COLOR_RED);
    init_pair(9, COLOR_WHITE, COLOR_BLUE);
    init_pair(10, COLOR_WHITE, 260);
    init_pair(11, COLOR_WHITE, COLOR_GREEN);

    nodelay (stdscr, TRUE);
    nc_initmemwin();
}