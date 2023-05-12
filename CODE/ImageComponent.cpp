#include "Components.h"

void ImageComponent::setImage(const char* i)
{
	switch (entityType)
	{
	case Character:
		image = pAM->getCharacterImage(i);
		break;
	case Background:
		image = pAM->getBackgroundImage(i);
		break;
	case World:
		image = pAM->getWorldImage(i);
		break;
	default:
		break;
	}
}

void ImageComponent::draw()
{
	if (isActive() == true)
	{
		if (image != -1 && image != NULL)
		{
			pDE->DrawAt(position, image, scale, angle, transparency);
		}
	}
}