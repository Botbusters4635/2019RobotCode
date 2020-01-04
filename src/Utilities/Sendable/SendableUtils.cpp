//
// Created by abiel on 12/31/19.
//

#include "SendableUtils.h"
#include "networktables/NetworkTableInstance.h"
#include <iostream>

NTEctoSendableVisitor::NTEctoSendableVisitor(nt::NetworkTableEntry &entryIn) : entry(entryIn) {
	;
}

void NTEctoSendableVisitor::operator()(double d) {
	entry.SetDouble(d);
}

void NTEctoSendableVisitor::operator()(bool b) {
	entry.SetBoolean(b);
}

void NTEctoSendableVisitor::operator()(const std::string &s) {
	entry.SetString(s);
}

void EctoSendableUtils::sendToNT(const EctoSendableData &data, const std::string &baseKey) {
	nt::NetworkTableInstance instance = nt::NetworkTableInstance::GetDefault();
	std::shared_ptr<nt::NetworkTable> table = instance.GetTable(baseKey);
	
	for(const auto value : data.getDataMap()){
		auto entry = table->GetEntry(value.first);
		
		NTEctoSendableVisitor visitor(entry);
		boost::apply_visitor(visitor, value.second);
	}
}

void EctoSendableUtils::sendToNT(std::shared_ptr<EctoSendable> sendable, const std::string &baseKey) {
	const EctoSendableData data = sendable->serializeData();
	sendToNT(data, baseKey);
}