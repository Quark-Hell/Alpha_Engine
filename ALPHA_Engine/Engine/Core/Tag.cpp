#include "Tag.h"

Tag::Tag() {
	if (Tag::_availableTags.size() != 0) {
		Tag::_tag = Tag::_availableTags.begin()->first;
		return;
	}
}

Tag::~Tag()
{

}

bool Tag::SetTag(std::string tag)
{
	for (const auto& el : _availableTags) {
		if (el.first == tag) {
			Tag::_tag = tag;
			return true;
		}
	}
	return false;
}

bool Tag::SetTag(unsigned int tagIndex)
{
	if (tagIndex > Tag::_availableTags.size())
		return false;

	auto el = Tag::_availableTags.begin();
	std::advance(el, tagIndex);

	Tag::_tag = el->first;
	return true;
}

std::string Tag::GetTag()
{
	return Tag::_tag;
}

std::vector<std::string> Tag::GetAvailablesTag()
{
	std::vector<std::string> tags;
	tags.reserve(Tag::_availableTags.size());
	for (const auto& el : _availableTags) {
		tags.push_back(el.first);
	}

	return tags;
}