//
// Created by Abiel on 8/22/19.
//
#include "EctoMotorConfig.h"
#include <boost/algorithm/string.hpp>

//TODO move this to a utility library.
bool compareIgnoringCase(const std::string &s, const std::string &s1) {
	return boost::algorithm::to_lower_copy(s) == boost::algorithm::to_lower_copy(s1);
}

void EctoMotorConfig::modifyProperty(const std::string &serializedProperty, const std::string &property) {
	if (compareIgnoringCase(property, EctoMotorConfigPropertyDict::name)) {
		this->name = serializedProperty;
	}
}