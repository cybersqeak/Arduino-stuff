#include "system.h"

void check_mode(t_sys *sys)
{
      sys->dis.mode = (t_mode)((sys->dis.mode + 1) % 3); 
}
