#pragma once
#include <iostream>
#include <string>
using namespace std;
class Excpetion {

};
class EmptyException :public Excpetion{
public:
	string what() {
		return "Empty input is invalid!\n";
	}
};
class TooLongException :public Excpetion {
public:
	string what() {
		return "The input is too long!\n";
	}
};
class NoIntegerException :public Excpetion {
public:
	string what() {
		return "Input must be positive integer!\n";
	}
};
class NoOperationException :public Excpetion {
public:
	string what() {
		return "No such kind of operation!\n";
	}
};
class CancelException :public Excpetion {
public:
	string what() {
		return "This operation has been cancel!\n";
	}
};
class InvaildEmailException :public Excpetion {
public:
	string what() {
		return "The Email address is invaild!\n";
	}
};
class InvaildPhoneException :public Excpetion {
public:
	string what() {
		return "The phone number is invaild!\n";
	}
};
class InvaildTitleException :public Excpetion {
public:
	string what() {
		return "The title is exist!\n";
	}
};
class InvaildParticipaterExistException :public Excpetion {
public:
	string what() {
		return "One of the participaters isn't exist!\n";
	}
};
class InvaildParticipaterRepeatedException :public Excpetion {
public:
	string what() {
		return "At least one of the participaters is repeated!\n";
	}
};
class InvaildFormatDateException :public Excpetion {
public:
	string what() {
		return "The format of the Date is invaild!\n";
	}
};
class InvaildOccupliedDateException :public Excpetion {
public:
	string what() {
		return "The time of the Date has been occupied!\n";
	}
};
class InvaildSelfisParticipaterException :public Excpetion {
public:
	string what() {
		return "The sponser can't be participater!\n";
	}
};
