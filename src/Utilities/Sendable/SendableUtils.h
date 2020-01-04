//
// Created by abiel on 12/31/19.
//

#ifndef BOTBUSTERSREBIRTH_SENDABLEUTILS_H
#define BOTBUSTERSREBIRTH_SENDABLEUTILS_H

#include "EctoSendable/EctoSendable.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"

class NTEctoSendableVisitor : public boost::static_visitor<> {
public:
	explicit NTEctoSendableVisitor(nt::NetworkTableEntry &entryIn);
	
	void operator()(double d);
	void operator()(bool b);
	void operator()(const std::string &s);
	
public:
	nt::NetworkTableEntry &entry;
};

//TODO Parse from NT (maybe)
namespace EctoSendableUtils {
	void sendToNT(const EctoSendableData &data, const std::string &baseKey);
	//void sendToNT(const EctoSendableValue &value, const std::string &entryName, std::shared_ptr<nt::NetworkTable> table);
	void sendToNT(std::shared_ptr<EctoSendable> sendable, const std::string &baseKey);
}

#endif //BOTBUSTERSREBIRTH_SENDABLEUTILS_H
