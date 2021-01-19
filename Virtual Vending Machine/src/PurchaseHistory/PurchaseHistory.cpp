#include <sstream>
#include "PurchaseHistory.h"


PurchaseHistory::PurchaseHistory() {
	memberID = 0;
	time(&rawDate);
}

PurchaseHistory::PurchaseHistory(std::list<Order> orders, Member member) {
	memberID = member.getID();
	history = orders;
	time(&rawDate);
} 

PurchaseHistory::PurchaseHistory(std::list<Order> orders, int memberid) {
	memberID = memberid;
	history = orders;
	time(&rawDate);
}

PurchaseHistory::PurchaseHistory(std::list<Order> orders, Member member, time_t date) {
	memberID = member.getID();
	rawDate = date;
	history = orders;
} 

PurchaseHistory::PurchaseHistory(std::list<Order> orders, int memberid, time_t date) {
	memberID = memberid;
	rawDate = date;
	history = orders;
}

PurchaseHistory::~PurchaseHistory() {}

int PurchaseHistory::getMemberID() {
	return memberID;
}

time_t PurchaseHistory::getRawTime() {
	return rawDate;
}

std::string PurchaseHistory::getTime() {
	struct tm* timeInfo;
	timeInfo = localtime(&rawDate);
	// Converts cstring to std::string
	return std::string(asctime(timeInfo));
}

void PurchaseHistory::addOrder(Order order) {
	for(std::list<Order>::iterator i = history.begin(); i != history.end(); ++i) {
		if(order.getProduct() == i->getProduct()) {
			i->setQuantity(i->getQuantity() + order.getQuantity());
			i->changeTotalCost(i->getTotalCost() + order.getTotalCost());
			return;
		}
	}
	history.push_back(order);
}

void PurchaseHistory::removeOrder(Order order) {
	history.remove(order);
}

std::string PurchaseHistory::printHistory() {
	std::ostringstream output;
	for(std::list<Order>::iterator i = history.begin(); i != history.end(); ++i) {
		output << "Product: " << i->getProduct().getName() << ", Amount: " << (i->getQuantity()) << ", Total Cost: $" << (i->getTotalCost()) << "\n";
	}
	
	return output.str();
}

int PurchaseHistory::length() {
	return history.size();
}

bool PurchaseHistory::isEmpty() {
	return history.empty();
}

std::list<Order>::iterator PurchaseHistory::begin() {
	return history.begin();
}

std::list<Order>::iterator PurchaseHistory::end() {
	return history.end();
}

