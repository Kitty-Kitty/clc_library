/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-24

Description:

**************************************************************************/
#include "cp_css_std.h"


cp_int32_t	cp_std_convert_position(gmdt_rectpair_p_t *gmdt_rp, cp_play_position_t *pp)
{
	if (!gmdt_rp || !pp) {
		return -1;
	}

	pp->source.left = *gmdt_rp->x1;
	pp->source.top = *gmdt_rp->y1;
	pp->source.right = *gmdt_rp->x2;
	pp->source.bottom = *gmdt_rp->y2;

	pp->dest.left = *gmdt_rp->x3;
	pp->dest.top = *gmdt_rp->y3;
	pp->dest.right = *gmdt_rp->x4;
	pp->dest.bottom = *gmdt_rp->y4;
	return 0;
}