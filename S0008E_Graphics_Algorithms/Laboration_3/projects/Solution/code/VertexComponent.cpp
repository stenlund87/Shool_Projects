#include "VertexComponent.h"


VertexComponent::VertexComponent()
{

}

VertexComponent::VertexComponent(SemanticName sn, int index, Format form)
{
    this->semName = sn;
    this->semIndex = index;
    this->format = form;
}