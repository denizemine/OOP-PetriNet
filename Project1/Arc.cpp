#include <iostream>

#include "Arc.h"

Arc::Arc(int w)
{
	weight = w;
}
int Arc::getWeight() const//safe olsun diye weighte i�lem yapm�yo sadece d�nd�r�yo.set olsa const konulmaz.
{
	return weight;
}
