#include <iostream>

#include "Arc.h"

Arc::Arc(int w)
{
	weight = w;
}
int Arc::getWeight() const//safe olsun diye weighte iþlem yapmýyo sadece döndürüyo.set olsa const konulmaz.
{
	return weight;
}
