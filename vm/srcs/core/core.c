#include "corewar.h"

t_core		*core_init()
{
	t_core	*core;

	core = ft_salloc(sizeof(t_core));
	ft_bzero(core, sizeof(t_core));
	vm_init(&(core->vm));
	return (core);
}

void		core_load_callback(t_core *core)
{
	core->vm.memUpdated = core->render.memUpdated;
	core->vm.processLoaded = core->render.processLoaded;
	core->vm.cycleUpdated = core->render.cycleUpdated;
	core->vm.processDie = core->render.processDie;
	core->vm.playerLive = core->render.playerLive;
	core->vm.playerDie = core->render.playerDie;
	core->vm.instLoaded = core->render.instLoaded;
	core->vm.pcUpdated = core->render.pcUpdated;
}
