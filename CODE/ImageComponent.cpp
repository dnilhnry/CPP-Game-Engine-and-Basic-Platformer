#include "Components.h"

void ImageComponent::setImage(const char* i)
{
	switch (entityType)
	{
	case Character:
		image = pAM->GetCharacterImage(i);
		break;
	case Background:
		image = pAM->GetBackgroundImage(i);
		break;
	case World:
		image = pAM->GetWorldImage(i);
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