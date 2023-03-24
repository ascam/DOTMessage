#include "sdlgenerator.hpp"

using macsa::dot::SDLGenerator;

SDLGenerator::SDLGenerator() :
	BitmapGenerator()
{

}

bitmap SDLGenerator::GetBitmap() const
{
	return bitmap();
}

void SDLGenerator::Update(Document *doc, Context* context)
{

}

void SDLGenerator::UpdateVariableFields(Document *doc, Context* context)
{

}
